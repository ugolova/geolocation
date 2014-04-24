#!/bin/bash

PACKAGE_NAME="dynamicmap"
VERSION="1.0"

./build.sh

if [[ $? != 0 ]] ; then
	exit 1
fi

FILESIZE=$(stat -c%s "dmap")

# making control file
mkdir -p package/$PACKAGE_NAME/DEBIAN
echo "Package: dynamicmap
Version: $VERSION
Architecture: all
Maintainer: Kirill Fertikov <kirill.fertikov@gmail.com>
Installed-Size: $FILESIZE
Depends: qt5-default, libqt5webkit5-dev, qtquick1-5-dev, qtlocation5-dev, qtsensors5-dev, qtdeclarative5-dev, libsqlite3-dev
Section: extras
Priority: optional
Homepage: https://github.com/threadend/geolocation
Description: Dynamic Map of St Petersburg Railway and Subway" > package/$PACKAGE_NAME/DEBIAN/control

# copying binary file
mkdir -p package/$PACKAGE_NAME/usr/bin/
mv ./dmap package/$PACKAGE_NAME/usr/bin/

# making .dep-package
cd package/
dpkg-deb -z8 -Zgzip --build $PACKAGE_NAME
cd ..
mv package/$PACKAGE_NAME.deb ./
rm -rf package/