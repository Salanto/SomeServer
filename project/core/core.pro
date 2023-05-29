QT += network websockets core

TEMPLATE = lib

# Apparently we need to define a static library to get a dynamic file.
# Whatever.
unix: CONFIG += shared static c++17
win32: CONFIG+= shared static c++17

win32: LIBS += -L$$PWD/../../bin/ -lnetcode
else:unix: LIBS += -L$$PWD/../../bin/ -lnetcode

INCLUDEPATH += $$PWD/src $$PWD/../netcode/src

# Needed so that Windows doesn't do `release/` and `debug/` subfolders
# in the output directory.
CONFIG -=         copy_dir_files
#        debug_and_release \
#        debug_and_release_target

DESTDIR = $$PWD/../../bin
OBJECTS_DIR = $$PWD/build
MOC_DIR = $$PWD/build

HEADERS += \
    src/advertiser/masterserver_client.hpp \
    src/advertiser/masterserver_client_p.hpp \
    src/area/area.hpp \
    src/area/area_manager.hpp \
    src/area/area_manager_p.hpp \
    src/area/hub_manager.hpp \
    src/area/hub_manager_p.hpp \
    src/client/client.hpp \
    src/client/client_manager.hpp \
    src/client/client_manager_p.hpp \
    src/client/client_p.hpp \
    src/client/client_packet_handler.hpp \
    src/configuration/config_manager.hpp \
    src/configuration/config_manager_p.hpp \
    src/packets/custom_packet.hpp \
    src/packets/decryptor_packet.hpp \
    src/packets/hi_packet.hpp \
    src/packets/id_packet.hpp \
    src/packets/le_packet.h \
    src/server.hpp

SOURCES += \
    src/advertiser/masterserver_client.cpp \
    src/area/area.cpp \
    src/area/area_manager.cpp \
    src/area/hub_manager.cpp \
    src/client/client_packet_handler.cpp \
    src/packets/custom_packet.cpp \
    src/packets/decryptor_packet.cpp \
    src/packets/hi_packet.cpp \
    src/packets/id_packet.cpp \
    src/packets/le_packet.cpp \
    src/server.cpp \
    src/config_manager.cpp \
    src/client/client_manager.cpp \
    src/client/client.cpp
