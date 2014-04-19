@echo off
mkdir build
xcopy /E dynamicmap build
cd build
qmake
mingw32-make

cd dynamicmap_tests\release
dynamicmap_tests.exe
if errorlevel 1 (
	cd ..\..\..\
	echo Some of the unit tests failed!
	rmdir /s/q build
	exit /b %errorlevel%
)
cd ..\..\..\
copy build\dynamicmap_src\release\dynamicmap.exe
rmdir /s/q build
