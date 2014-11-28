DrumkitX
========

DrumkitX is a Windows Phone 8 port of the Drumkit XNA example using Direct3D and XAudio for fast graphics and low latency sample playback. This demo app lets you play percussion sounds by tapping the screen. You can record your beats, play them back later and also play drums on top of your latest recording.

This example application is hosted in GitHub:
https://github.com/Microsoft/drumkitx

Developed with Microsoft Visual Studio Express for Windows Phone 2012.

Compatible with:

 * Windows Phone 8

Tested to work on:

 * Nokia Lumia 520
 * Nokia Lumia 820
 * Nokia Lumia 920
 

Instructions
------------

Make sure you have the following installed:

 * Windows 8
 * Windows Phone SDK 8.0

To build and run the sample:

 * Open the SLN file
   * File > Open Project, select the file DrumkitX.sln
 * Select the target, for example 'Emulator WVGA 512MB'.
 * Press F5 to build the project and run it on the Windows Phone Emulator.

To deploy the sample on Windows Phone 8 device:
 * See the official documentation for deploying and testing applications on Windows Phone devices at http://msdn.microsoft.com/en-us/library/windowsphone/develop/ff402565(v=vs.105).aspx

  
About the implementation
------------------------

Important folders:

| Folder | Description |
| ------ | ----------- |
| / | Contains the project file, the license information and this file (README.md) |
| DrumkitX | Root folder for the implementation files.  |
| DrumkitX/DirectXTK | DirectX ToolKit. |
| DrumkitX/DrumkitX | DrumkitX Windows Phone managed application implementation. |
| DrumkitX/DrumkitX/Assets | Application assets, tiles for example. |
| DrumkitX/DrumkitX/Properties | Application property files. |
| DrumkitX/DrumkitX/Resources | Application resources. |
| DrumkitX/DrumkitXComp | Native components for DrumkitX application. |
| DrumkitX/DrumkitXComp/images | DirectDraw surface files for drumkit graphics. |
| DrumkitX/DrumkitXComp/sounds | Audio files for drum sounds.  |

Important files:

| File | Description |
| ---- | ----------- |
| MainPage.xaml  | The main page of the application with a drawing surface for DirectX graphics. |
| MainPage.xaml.cs | The code-behind file of the main page bridging managed side with native side. |

Important classes:

| Class | Description |
| ----- | ----------- |
| Direct3DInterop | Acts as a bridge between the managed and native worlds. |
| DrumkitRenderer | Responsible of rendering the drumkit and playing the drum sounds. |
| Recorder.cs | Records the drum strokes. |

You can read more about Direct3D for Windows Phone 8 from http://msdn.microsoft.com/en-us/library/windowsphone/develop/jj207062(v=vs.105).aspx

Another Nokia Developer example on creating DirectX application on Windows Phone is available at http://www.developer.nokia.com/Community/Wiki/DirectX_on_Windows_Phone:_2D_Game_Example_using_DirectX_Toolkit

More information on XAudio2 can be found from http://msdn.microsoft.com/en-us/library/windows/apps/Hh405049 and from an example application http://code.msdn.microsoft.com/windowsapps/Basic-Audio-Sample-9a5bb0b7 demonstrating the use of XAudio2 in an app.

Known issues
------------

No known issues.


License
-------

See the license file delivered with this project.
The license is also available online at
https://github.com/Microsoft/drumkitx/blob/master/License.txt


Version history
---------------

 * 1.1 Support for 720p resolution.
 * 1.0 Application tiles and icons. Removed unnecessary capabilities.
 * 0.6 Code cleaning, copyrighting and commenting. Button graphics added.
 * 0.5 First public beta version   
