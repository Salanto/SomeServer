TEMPLATE = subdirs

SUBDIRS += \
    core \
    someserver \
    netcode

core.subdir = project/core
core.depends = netcode
someserver.subdir = project/someserver
someserver.depends = core netcode
netcode.subdir = project/netcode
