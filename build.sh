#!/bin/bash

QMAKE="$HOME/Qt5.2.1/5.2.1/gcc_64/bin/qmake"

cp -r dynamicmap/ build/
cd build
$QMAKE
make
cd ..
cp build/dynamicmap dmap
rm -rf build/

