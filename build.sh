#!/bin/bash

cp -r dynamicmap/ui/ build/
cd build
qmake
make
cd ..
cp build/dynamicmap dmap
rm -rf build/

