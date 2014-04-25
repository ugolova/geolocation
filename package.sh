#!/bin/bash

package_name="dynamicmap"
binary_name="dmap"
package_dir=".package"
version="1.0.1"
qt_lib_dir="$HOME/Qt5.2.1/5.2.1/gcc_64/lib"
ubuntu_version="trusty"

# building
./build.sh
result=$?
if [[ $result != 0 ]] ; then
	exit $result
fi

# making control file
mkdir -p $package_dir/$package_name/DEBIAN
echo "Package: $package_name
Version: $version
Architecture: all
Maintainer: Kirill Fertikov <kirill.fertikov@gmail.com>
Installed-Size: $(stat -c%s $binary_name)
Depends: qt5-default, libqt5webkit5-dev, qtquick1-5-dev, qtlocation5-dev, qtsensors5-dev, qtdeclarative5-dev, libsqlite3-dev
Section: extras
Priority: optional
Homepage: https://github.com/threadend/geolocation
Description: Dynamic Map of St Petersburg Railway and Subway" > $package_dir/$package_name/DEBIAN/control

# copying binary file
mkdir -p $package_dir/$package_name/usr/bin/
mv ./$binary_name $package_dir/$package_name/usr/bin/$package_name

# making .dep-package
cd $package_dir/
dpkg-deb -z8 -Zgzip --build $package_name
cd ..
mv $package_dir/$package_name.deb $package_name"-"$version"-"$ubuntu_version.deb
rm -rf $package_dir/