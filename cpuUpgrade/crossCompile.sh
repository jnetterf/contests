#!/bin/sh
echo "Requires ARCH packages mingw32-* and AUR packages mingw32-portaudio, and the binary version of jack (install yourself and copy to /usr/i486-mingw32/..."
qmake -spec win32-x-g++ && make
