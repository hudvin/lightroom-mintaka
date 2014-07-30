set QTDIR=C:\dev\Qt5.3.1
set QMAKESPEC=C:\dev\Qt5.3.1\5.3\msvc2013_64_opengl\mkspecs\win32-msvc2013
set PATH=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\x86_amd64\;%PATH%
call     "vcvarsx86_amd64.bat"

C:\dev\Qt5.3.1\5.3\msvc2013_64_opengl\bin\qmake.exe ..\lr-qt\untitled\untitled.pro -r -spec win32-msvc2013 "CONFIG+=debug"

C:\dev\Qt5.3.1\Tools\QtCreator\bin\jom.exe -f C:\dev\projects\lr-plugin\build\Makefile.Debug clean
C:\dev\Qt5.3.1\Tools\QtCreator\bin\jom.exe -f C:\dev\projects\lr-plugin\build\Makefile.Release clean

C:\dev\Qt5.3.1\Tools\QtCreator\bin\jom.exe -f C:\dev\projects\lr-plugin\build\Makefile.Debug
C:\dev\Qt5.3.1\Tools\QtCreator\bin\jom.exe -f C:\dev\projects\lr-plugin\build\Makefile.Release


set PATH=C:\dev\Qt5.3.1\5.3\msvc2013_64_opengl\bin\;C:\dev\MinGW\bin\;%PATH%
windeployqt.exe  release\mintaka.exe
windeployqt.exe  debug\mintaka.exe

rm relese/*.obj
rm debug/*.obj

upx release/*.dll
upx release/*.exe

upx debug/*.dll
upx debug/*.exe
