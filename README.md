inhibit
=======

Small library to inhibit the desktop screensaver on Linux.

This library is in two parts...

The first is a small native library that encapsulates calls via the DBus to inhibit/uninhibit the desktop screen-saver.

At the present time a pre-built native library is not included in the distribution - you must make and install this yourself.

Making the native library is easy on any typical Linux distribution - you need to make sure you have the libdbus and libdus-glib development packages installed, and then you can simply use the supplied `build.sh` shell script to create the native library. You can then copy this wherever you want.

The second is a small Java library that encapsulated calls via JNA to the native library.

