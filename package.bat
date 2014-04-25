@echo off

SET qtpath="C:\Qt\5.2.1\mingw48_32"

call build.bat
if errorlevel 1 (
	exit /b %errorlevel%
)

mkdir package
mkdir package\plugins
move dynamicmap.exe package

copy "%qtpath%\bin\icudt51.dll" package
copy "%qtpath%\bin\icuin51.dll" package
copy "%qtpath%\bin\icuuc51.dll" package
copy "%qtpath%\bin\libgcc_s_dw2-1.dll" package
copy "%qtpath%\bin\libstdc++-6.dll" package
copy "%qtpath%\bin\libwinpthread-1.dll" package
copy "%qtpath%\bin\Qt5Core.dll" package
copy "%qtpath%\bin\Qt5Gui.dll" package
copy "%qtpath%\bin\Qt5Multimedia.dll" package
copy "%qtpath%\bin\Qt5MultimediaWidgets.dll" package
copy "%qtpath%\bin\Qt5Network.dll" package
copy "%qtpath%\bin\Qt5OpenGL.dll" package
copy "%qtpath%\bin\Qt5Positioning.dll" package
copy "%qtpath%\bin\Qt5PrintSupport.dll" package
copy "%qtpath%\bin\Qt5Qml.dll" package
copy "%qtpath%\bin\Qt5Quick.dll" package
copy "%qtpath%\bin\Qt5Sensors.dll" package
copy "%qtpath%\bin\Qt5Sql.dll" package
copy "%qtpath%\bin\Qt5WebKit.dll" package
copy "%qtpath%\bin\Qt5WebKitWidgets.dll" package
copy "%qtpath%\bin\Qt5Widgets.dll" package

copy "%qtpath%\plugins\platforms\qwindows.dll" package\plugins