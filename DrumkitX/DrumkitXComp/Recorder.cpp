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

#include "pch.h"
#include "Recorder.h"

namespace DrumkitXComp
{

/**
 * @class Recorder
 * @brief This class is responsible of drum recording and playback.
 *        Stores tap coordinates along with their timestamps when recording is
 *        active, and plays them back by directly calling Tap on the renderer.
 */

Recorder::Recorder(ITappable^ tappable) :
	m_recording(false),
	m_playing(false),
	m_recordingStartTime(0),
	m_tappable(tappable)
{
}

void Recorder::Play()
{
	m_nextEvent = m_events.begin();
	m_playbackPosition = 0;
	m_playing = true;
}

void Recorder::Record(float starttime)
{
	m_events.clear();
	m_recordingStartTime = starttime;
	m_recording = true;
}

void Recorder::Stop()
{
	m_recording = false;
	m_playing = false;
}

bool Recorder::IsRecording()
{
	return m_recording;
}

bool Recorder::IsPlaying()
{
	return m_playing;
}

void Recorder::Tap(float x, float y, float time)
{
	if (m_recording)
	{
		m_events.push_back(TapEvent(time - m_recordingStartTime, x, y));
	}
}

void Recorder::AdvancePlayback(float total, float delta)
{
	m_playbackPosition += delta;

	if (m_nextEvent != m_events.end())
	{
		if (m_playbackPosition >= m_nextEvent->Time)
		{
			float x = m_nextEvent->X;
			float y = m_nextEvent->Y;
			m_nextEvent++;
			m_tappable->Tap(x, y);
		}
	}
	else
	{
		m_playing = false;
	}
}

}