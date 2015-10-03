@rem Copyright (c) MediaArea.net SARL. All Rights Reserved.
@rem
@rem Use of this source code is governed by a BSD-style license that can
@rem be found in the License.html file in the root of the source tree.
@rem

@rem echo off

@rem --- Clean up ---
del   MediaConch_GUI_Windows_i386.exe
del   MediaConch_GUI_Windows_i386_WithoutInstaller.7z
rmdir MediaConch_GUI_Windows_i386 /S /Q
mkdir MediaConch_GUI_Windows_i386


@rem --- Copying : Exe ---
copy  ..\Project\MSVC2013\GUI\Win32\Release\MediaConch_GUI.exe MediaConch_GUI_Windows_i386\MediaConch.exe
copy  ..\Project\MSVC2013\GUI\Win32\Release\icudt54.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\icuin54.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\icuuc54.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\LIBCURL.DLL MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt53DCore.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt53DInput.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt53DQuick.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt53DQuickRenderer.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt53DRenderer.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Bluetooth.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5CLucene.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Concurrent.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Core.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5DBus.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Declarative.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Designer.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5DesignerComponents.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Gui.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Help.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Location.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Multimedia.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5MultimediaQuick_p.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5MultimediaWidgets.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Network.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Nfc.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5OpenGL.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Positioning.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5PrintSupport.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Qml.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Quick.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5QuickParticles.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5QuickTest.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5QuickWidgets.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Script.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5ScriptTools.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Sensors.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5SerialPort.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Sql.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Svg.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Test.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5WebChannel.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5WebEngine.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5WebEngineCore.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5WebEngineWidgets.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5WebKit.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5WebKitWidgets.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5WebSockets.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Widgets.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5WinExtras.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5Xml.dll MediaConch_GUI_Windows_i386\
copy  ..\Project\MSVC2013\GUI\Win32\Release\Qt5XmlPatterns.dll MediaConch_GUI_Windows_i386\
copy  "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x86\Microsoft.VC120.CRT\msvcp120.dll" MediaConch_GUI_Windows_i386\
copy  "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x86\Microsoft.VC120.CRT\msvcr120.dll" MediaConch_GUI_Windows_i386\
copy  "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x86\Microsoft.VC120.CRT\vccorlib120.dll" MediaConch_GUI_Windows_i386\
mkdir MediaConch_GUI_Windows_i386\platforms
copy  ..\Project\MSVC2013\GUI\Win32\Release\qwindows.dll MediaConch_GUI_Windows_i386\platforms\

@rem --- Copying : Information files ---
copy ..\License.html MediaConch_GUI_Windows_i386\
copy ..\History_GUI.txt MediaConch_GUI_Windows_i386\History.txt
copy ReadMe_GUI_Windows.txt MediaConch_GUI_Windows_i386\ReadMe.txt


rem --- Compressing Archive ---
cd MediaConch_GUI_Windows_i386\
..\..\..\Shared\Binary\Windows_i386\7-Zip\7z a -r -t7z -mx9 ..\MediaConch_GUI_Windows_i386_WithoutInstaller.7z *
cd ..

rem --- Installer ---
copy ..\Project\BCB\GUI\Release_Build\MediaConch_GUI.exe BCB\GUI\MediaConch.exe
..\..\Shared\Binary\Windows_i386\NSIS\makensis ..\Source\Install\MediaConch_GUI_Windows_i386.nsi

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir MediaConch_GUI_Windows_i386\ /S /Q
:SkipCleanUp