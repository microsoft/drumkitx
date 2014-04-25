/**
 * Copyright (c) 2013-2014 Microsoft Mobile. All rights reserved.
 *
 * Nokia, Nokia Connecting People, Nokia Developer, and HERE are trademarks
 * and/or registered trademarks of Nokia Corporation. Other product and company
 * names mentioned herein may be trademarks or trade names of their respective
 * owners.
 *
 * See the license text file delivered with this project for more information.
 */

using DrumkitXComp;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using System.Windows.Media.Imaging;
using System.Windows.Threading;

namespace DrumkitX
{
    /// <summary>
    /// Main page for the application containing the drum set
    /// and buttons for recording and playback.
    /// </summary>
    public partial class MainPage : PhoneApplicationPage
    {
        // Bridge to the DirectX side of the implementation
        private Direct3DInterop m_d3dInterop = new Direct3DInterop();
        private object m_contentProvider = null;

        // Helper flags to handle button states correctly
        private Boolean m_isRecording = false;
        private Boolean m_isPlaying = false;

        // Members related to the recording/playback time
        private DispatcherTimer m_soundTimer = null;
        private TimeSpan m_recordingTime;
        private DateTime m_recordingStartTime;
        private DateTime m_playingStartTime;

        /// <summary>
        /// Constructor.
        /// </summary>
        public MainPage()
        {
            InitializeComponent();
            PhoneApplicationService.Current.Launching += AppLaunching;
            PhoneApplicationService.Current.Activated += AppActivated;
            PhoneApplicationService.Current.Deactivated += AppDeactivated;
            PhoneApplicationService.Current.Closing += AppClosing;
        }

        /// <summary>
        /// Stops audio engine when application is closed.
        /// </summary>
        /// <param name="sender">PhoneApplicationService</param>
        /// <param name="e">Event arguments</param>
        void AppClosing(object sender, ClosingEventArgs e)
        {
            m_d3dInterop.StopAudioEngine();
        }

        /// <summary>
        /// Stops audio engine when application is deactivated.
        /// </summary>
        /// <param name="sender">PhoneApplicationService</param>
        /// <param name="e">Event arguments</param>
        void AppDeactivated(object sender, DeactivatedEventArgs e)
        {
            m_d3dInterop.StopAudioEngine();
        }

        /// <summary>
        /// Starts audio engine when application is activated.
        /// </summary>
        /// <param name="sender">PhoneApplicationService</param>
        /// <param name="e">Event arguments</param>
        void AppActivated(object sender, ActivatedEventArgs e)
        {
            m_d3dInterop.StartAudioEngine();
        }

        /// <summary>
        /// Starts audio engine when application is launched.
        /// </summary>
        /// <param name="sender">PhoneApplicationService</param>
        /// <param name="e">Event arguments</param>
        void AppLaunching(object sender, LaunchingEventArgs e)
        {
            m_d3dInterop.StartAudioEngine();
        }

        /// <summary>
        /// Initializes drawing surface.
        /// </summary>
        /// <param name="sender">DrawingSurface</param>
        /// <param name="e">Event arguments</param>
        private void DrawingSurface_Loaded(object sender, RoutedEventArgs e)
        {
            // Set window bounds in dips.
            m_d3dInterop.WindowBounds = new Windows.Foundation.Size(
                (float)DrawingSurface.ActualWidth,
                (float)DrawingSurface.ActualHeight
                );

            // Set native resolution in pixels.
            m_d3dInterop.NativeResolution = new Windows.Foundation.Size(
                (float)Math.Floor(DrawingSurface.ActualWidth * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f),
                (float)Math.Floor(DrawingSurface.ActualHeight * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f)
                );

            // Set render resolution to the full native resolution.
            m_d3dInterop.RenderResolution = m_d3dInterop.NativeResolution;

            // Hook-up native component to DrawingSurface.
            if (m_contentProvider == null)
            {
                m_contentProvider = m_d3dInterop.CreateContentProvider();
            }

            DrawingSurface.SetContentProvider(m_contentProvider);
            DrawingSurface.SetManipulationHandler(m_d3dInterop);
        }

        /// <summary>
        /// Navigates to About Page.
        /// </summary>
        /// <param name="sender">AboutImage</param>
        /// <param name="e">Event arguments</param>
        private void About_Tap(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new Uri("/AboutPage.xaml", UriKind.Relative));
        }

        /// <summary>
        /// Starts recording.
        /// </summary>
        /// <param name="sender">RecordImage</param>
        /// <param name="e">Event arguments</param>
        private void Record_Tap(object sender, RoutedEventArgs e)
        {
            if (m_isRecording)
            {
                RecordImage.Source = new BitmapImage(new Uri("/Assets/record.png", UriKind.Relative));
                m_d3dInterop.StopRecordingOrPlayback();
                m_recordingTime = DateTime.Now - m_recordingStartTime;
            }
            else
            {
                RecordImage.Source = new BitmapImage(new Uri("/Assets/record_active.png", UriKind.Relative));
                m_recordingStartTime = DateTime.Now;
                m_d3dInterop.StartRecording();
            }

            PlayImage.IsHitTestVisible = m_isRecording;
            PlayImage.Opacity = m_isRecording ? 1.0 : 0.5;
            m_isRecording = !m_isRecording;
        }

        /// <summary>
        /// Starts playback.
        /// </summary>
        /// <param name="sender">PlayImage</param>
        /// <param name="e">Event arguments</param>
        private void Play_Tap(object sender, RoutedEventArgs e)
        {
            if (m_isPlaying)
            {
                m_soundTimer.Stop();
                PlayImage.Source = new BitmapImage(new Uri("/Assets/play.png", UriKind.Relative));
                m_d3dInterop.StopRecordingOrPlayback();
            }
            else
            {
                PlayImage.Source = new BitmapImage(new Uri("/Assets/stop.png", UriKind.Relative));

                if (m_soundTimer == null)
                {
                    m_soundTimer = new DispatcherTimer();
                    m_soundTimer.Tick += RecordingTimer_Tick;
                    m_soundTimer.Interval = TimeSpan.FromSeconds(0.1);
                }

                m_playingStartTime = DateTime.Now;
                m_soundTimer.Start();
                m_d3dInterop.StartPlayback();
            }

            RecordImage.IsHitTestVisible = m_isPlaying;
            RecordImage.Opacity = m_isPlaying ? 1.0 : 0.5;
            m_isPlaying = !m_isPlaying;
        }

        /// <summary>
        /// Handles for a MouseLeave event on images representing buttons.
        /// </summary>
        /// <param name="sender">Image representing a button</param>
        /// <param name="e">Event arguments</param>
        private void Image_MouseEnter(object sender, RoutedEventArgs e)
        {
            if (sender == AboutImage)
            {
                AboutImage.Source = new BitmapImage(new Uri("/Assets/info_pressed.png", UriKind.Relative));
            }
            else if (sender == PlayImage)
            {
                PlayImage.Source = m_isPlaying 
                    ? new BitmapImage(new Uri("/Assets/stop_pressed.png", UriKind.Relative))
                    : new BitmapImage(new Uri("/Assets/play_pressed.png", UriKind.Relative));
            }
            else
            {
                RecordImage.Source = new BitmapImage(new Uri("/Assets/record_pressed.png", UriKind.Relative));
            }
        }

        /// <summary>
        /// Handler for a MouseLeave event on images representing buttons.
        /// </summary>
        /// <param name="sender">PlayImage</param>
        /// <param name="e">Event arguments</param>
        private void Image_MouseLeave(object sender, RoutedEventArgs e)
        {
            if (sender == AboutImage)
            {
                AboutImage.Source = new BitmapImage(new Uri("/Assets/info.png", UriKind.Relative));
            }
            else if (sender == PlayImage)
            {
                PlayImage.Source = m_isPlaying
                    ? new BitmapImage(new Uri("/Assets/stop.png", UriKind.Relative))
                    : new BitmapImage(new Uri("/Assets/play.png", UriKind.Relative));
            }
            else
            {
                RecordImage.Source = m_isRecording
                    ? new BitmapImage(new Uri("/Assets/record_active.png", UriKind.Relative))
                    : new BitmapImage(new Uri("/Assets/record.png", UriKind.Relative));
            }
        }

        /// <summary>
        /// Stops playback after a recording has been played.
        /// This needs to be done with Timer since there is no other way 
        /// of finding out when recording has reached the end.
        /// </summary>
        /// <param name="sender">PlayImage</param>
        /// <param name="e">Event arguments</param>
        private void RecordingTimer_Tick(object sender, EventArgs e)
        {
            if (DateTime.Now - m_playingStartTime > m_recordingTime)
            {
                m_soundTimer.Stop();
                PlayImage.Source = new BitmapImage(new Uri("/Assets/play.png", UriKind.Relative));
                m_isPlaying = false;
                m_d3dInterop.StopRecordingOrPlayback();

                RecordImage.Opacity = 1;
                RecordImage.IsHitTestVisible = true;
            }
        }
    }
}