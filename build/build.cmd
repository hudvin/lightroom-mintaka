@echo off

set UPXDIR=C:\dev\upx391w
set QTDIR=C:\dev\Qt5.3.1
set QMAKESPEC=%QTDIR%\msvc2013_64_opengl\mkspecs\win32-msvc2013
set PATH=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\x86_amd64\;%QTDIR%\5.3\msvc2013_64_opengl\bin\;%UPXDIR%;%PATH%
set JOM_CMD=%QTDIR%\Tools\QtCreator\bin\jom.exe
call "vcvarsx86_amd64.bat"

%QTDIR%\5.3\msvc2013_64_opengl\bin\qmake.exe ..\lr-qt\untitled\untitled.pro -r -spec win32-msvc2013 "CONFIG+=debug"

%JOM_CMD% -f Makefile.Debug clean
%JOM_CMD% -f Makefile.Release clean

%JOM_CMD% -f Makefile.Debug
%JOM_CMD% -f Makefile.Release

call :cleanAndPack "debug"
call :cleanAndPack "release"

goto :eof

:cleanAndPack
echo "******BUILD NAME******"
echo %~1
windeployqt.exe %~1
FOR /f %%f in ('dir %~1 /a-d   /s /b  ^| findstr  ".dll .exe"') DO upx %%f
FOR /f %%f in ('dir %1 /a-d   /s /b  ^| findstr  ".obj .cpp"') DO del %%f
goto:eof