set QTDIR=C:\dev\Qt5.3.1
set QMAKESPEC=%QTDIR%\msvc2013_64_opengl\mkspecs\win32-msvc2013
set PATH=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\x86_amd64\;%QTDIR%\5.3\msvc2013_64_opengl\bin\;%PATH%
call "vcvarsx86_amd64.bat"

%QTDIR%\5.3\msvc2013_64_opengl\bin\qmake.exe ..\lr-qt\untitled\untitled.pro -r -spec win32-msvc2013 "CONFIG+=debug"

%QTDIR%\Tools\QtCreator\bin\jom.exe -f Makefile.Debug clean
%QTDIR%\Tools\QtCreator\bin\jom.exe -f Makefile.Release clean

%QTDIR%\Tools\QtCreator\bin\jom.exe -f Makefile.Debug
%QTDIR%\Tools\QtCreator\bin\jom.exe -f Makefile.Release

windeployqt.exe  release\mintaka.exe
windeployqt.exe  debug\mintaka.exe