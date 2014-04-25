#!/bin/bash

qmake_cmd="$HOME/Qt5.2.1/5.2.1/gcc_64/bin/qmake"
make_cmd="make"
build_dir=".build"

cp -r dynamicmap/ $build_dir/
cd $build_dir/

# generating Makefiles
$qmake_cmd
result=$?
if [[ $result != 0 ]] ; then
	echo -e "\nqmake failed!" 1>&2;
	cd ..
	rm -rf $build_dir/
    exit $result
fi

# making
$make_cmd
result=$?
if [[ $result != 0 ]] ; then
	echo -e "\nmake failed!" 1>&2;
	cd ..
	rm -rf $build_dir/
    exit $result
fi

# executing unit-tests
cd dynamicmap_tests/
./dynamicmap_tests
result=$?
cd ../../
if [[ $result != 0 ]] ; then
	echo -e "\nSome of the unit tests failed!" 1>&2;
	rm -rf $build_dir/
    exit $result
fi
echo -e "\nAll the unit tests complete!" 1>&2;

# copying binary file and removing trash
mv $build_dir/dynamicmap_src/dynamicmap dmap
rm -rf $build_dir/