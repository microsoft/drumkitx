DrumkitX
========

DrumkitX is a Windows Phone 8 port of the Drumkit XNA example using Direct3D and XAudio for fast graphics and low latency sample playback. This demo app lets you play percussion sounds by tapping the screen. You can record your beats, play them back later and also play drums on top of your latest recording.

This example application is hosted in GitHub:
https://github.com/nokia-developer/drumkitx

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

    Copyright © 2013 Nokia Corporation. All rights reserved.
    
    Nokia, Nokia Developer, and HERE are trademarks and/or registered trademarks of
    Nokia Corporation. Other product and company names mentioned herein may be
    trademarks or trade names of their respective owners.
    
    License
    Subject to the conditions below, you may use, copy, modify and/or merge copies
    of this software and associated content and documentation files (the “Software”)
    to test, develop, publish, distribute, sub-license and/or sell new software
    derived from or incorporating the Software, solely in connection with Nokia
    devices. Some of the documentation, content and/or software maybe licensed under
    open source software or other licenses. To the extent such documentation,
    content and/or software are included, licenses and/or other terms and conditions
    shall apply in addition and/or instead of this notice. The exact terms of the
    licenses, disclaimers, acknowledgements and notices are reproduced in the
    materials provided, or in other obvious locations. No other license to any other
    intellectual property rights is granted herein.
    
    This file, unmodified, shall be included with all copies or substantial portions
    of the Software that are distributed in source code form.
    
    The Software cannot constitute the primary value of any new software derived
    from or incorporating the Software.
    
    Any person dealing with the Software shall not misrepresent the source of the
    Software.
    
    Disclaimer
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
    FOR A PARTICULAR PURPOSE, QUALITY AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES (INCLUDING,
    WITHOUT LIMITATION, DIRECT, SPECIAL, INDIRECT, PUNITIVE, CONSEQUENTIAL,
    EXEMPLARY AND/ OR INCIDENTAL DAMAGES) OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
    Nokia Corporation retains the right to make changes to this document at any
    time, without notice.
  
Due to partly relying on the XAudio2 audio file playback sample, the application is also subject to the terms of MS-LPL license (included in the source code). The license file is also available online at http://projects.developer.nokia.com/drumkitx/browser/MS-LPL.txt

    MICROSOFT LIMITED PUBLIC LICENSE version 1.1
    This license governs use of code marked as “sample” or “example” available on this web site without a license agreement, as provided under the section above titled “NOTICE SPECIFIC TO SOFTWARE AVAILABLE ON THIS WEB SITE.” If you use such code (the “software”), you accept this license. If you do not accept the license, do not use the software.
    
    1. Definitions
    The terms “reproduce,” “reproduction,” “derivative works,” and “distribution” have the same meaning here as under U.S. copyright law.
    A “contribution” is the original software, or any additions or changes to the software.
    A “contributor” is any person that distributes its contribution under this license.
    “Licensed patents” are a contributor’s patent claims that read directly on its contribution.
    
    2. Grant of Rights
    (A) Copyright Grant - Subject to the terms of this license, including the license conditions and limitations in section 3, each contributor grants you a non-exclusive, worldwide, royalty-free copyright license to reproduce its contribution, prepare derivative works of its contribution, and distribute its contribution or any derivative works that you create.
    (B) Patent Grant - Subject to the terms of this license, including the license conditions and limitations in section 3, each contributor grants you a non-exclusive, worldwide, royalty-free license under its licensed patents to make, have made, use, sell, offer for sale, import, and/or otherwise dispose of its contribution in the software or derivative works of the contribution in the software.
    
    3. Conditions and Limitations
    (A) No Trademark License- This license does not grant you rights to use any contributors’ name, logo, or trademarks.
    (B) If you bring a patent claim against any contributor over patents that you claim are infringed by the software, your patent license from such contributor to the software ends automatically.
    (C) If you distribute any portion of the software, you must retain all copyright, patent, trademark, and attribution notices that are present in the software.
    (D) If you distribute any portion of the software in source code form, you may do so only under this license by including a complete copy of this license with your distribution. If you distribute any portion of the software in compiled or object code form, you may only do so under a license that complies with this license.
    (E) The software is licensed “as-is.” You bear the risk of using it. The contributors give no express warranties, guarantees or conditions. You may have additional consumer rights under your local laws which this license cannot change. To the extent permitted under your local laws, the contributors exclude the implied warranties of merchantability, fitness for a particular purpose and non-infringement.
    (F) Platform Limitation - The licenses granted in sections 2(A) and 2(B) extend only to the software or derivative works that you create that run directly on a Microsoft Windows operating system product, Microsoft run-time technology (such as the .NET Framework or Silverlight), or Microsoft application platform (such as Microsoft Office or Microsoft Dynamics).

Version history
---------------

 * 1.1 Support for 720p resolution.
 * 1.0 Application tiles and icons. Removed unnecessary capabilities.
 * 0.6 Code cleaning, copyrighting and commenting. Button graphics added.
 * 0.5 First public beta version   
