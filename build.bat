mkdir build
xcopy /E dynamicmap\ui build
cd build
qmake
mingw32-make
cd ..
copy build\release\dynamicmap.exe
rmdir /s/q build
