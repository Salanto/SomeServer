QT += network websockets

TEMPLATE = lib

# Apparently we need to define a static library to get a dynamic file.
# Whatever.
unix: CONFIG += shared static c++17
win32: CONFIG+= shared static c++17

# Needed so that Windows doesn't do `release/` and `debug/` subfolders
# in the output directory.
CONFIG -= \
        copy_dir_files
#        debug_and_release \
#        debug_and_release_target

DESTDIR = $$PWD/../../bin
OBJECTS_DIR = $$PWD/build
MOC_DIR = $$PWD/build

HEADERS += \
  src/aotcpsocket.hpp \
  src/aowebsocket.hpp \
  src/connection_handler.hpp \
  src/connection_handler_p.hpp \
  src/interfaces/network_socket_i.hpp \
  src/packet.hpp \
  src/packet_factory.hpp \
  src/packet_handler.hpp \
  src/packet_info.hpp

SOURCES += \
  src/aotcpsocket.cpp \
  src/aowebsocket.cpp \
  src/connection_handler.cpp \
  src/packet.cpp \
  src/packet_factory.cpp \
  src/packet_handler.cpp
