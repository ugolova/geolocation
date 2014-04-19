#!/bin/bash

QMAKE="$HOME/Qt5.2.1/5.2.1/gcc_64/bin/qmake"

cp -r dynamicmap/ build/
cd build
$QMAKE
make
cd dynamicmap_tests
./dynamicmap_tests
UNIT_TESTS_RESULT=$?
if [[ $UNIT_TESTS_RESULT != 0 ]] ; then
	cd ../../
	echo -e "\nSome of the unit tests failed!" 1>&2;
	rm -rf build/
    exit $UNIT_TESTS_RESULT
else
	cd ../../
	echo -e "\nAll the unit tests complete!" 1>&2;
	cp build/dynamicmap_src/dynamicmap dmap
	rm -rf build/
fi