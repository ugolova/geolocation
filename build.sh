#!/bin/bash

QMAKE="$HOME/Qt/5.2.1/gcc_64/bin/qmake"

cp -r dynamicmap/ui/ build/
cd build
$QMAKE
make
cd ..
cp build/dynamicmap dmap
rm -rf build/

