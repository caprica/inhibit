# Simple build script to build the native shared library.
#
# At some point I might try and integrate this into a Maven build somehow.
#
# Consequently the shared object is not (yet) included in the project distribution package and must
# therefore be manually built and installed.
#
# For now this will do, and it's pretty simple...
gcc                                \
 -std=c99                          \
 -fpic                             \
 -shared                           \
 `pkg-config --cflags dbus-glib-1` \
 `pkg-config --cflags dbus-1`      \
 `pkg-config --cflags glib-2.0`    \
 inhibit.c                         \
 `pkg-config --libs dbus-glib-1`   \
 `pkg-config --libs dbus-1`        \
 `pkg-config --libs glib-2.0`      \
 -o libinhibit.so
