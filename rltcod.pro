QT += core
QT -= gui

TARGET = rltcod
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++14

TEMPLATE = app

SOURCES += main.cpp \
    intergalacticcloud.cpp \
    galacticcluster.cpp \
    inputcontrols.cpp

HEADERS += \
    include/bresenham.h \
    include/bresenham.hpp \
    include/bsp.h \
    include/bsp.hpp \
    include/color.h \
    include/color.hpp \
    include/console_types.h \
    include/console.h \
    include/console.hpp \
    include/fov_types.h \
    include/fov.h \
    include/fov.hpp \
    include/heightmap.h \
    include/heightmap.hpp \
    include/image.h \
    include/image.hpp \
    include/lex.h \
    include/lex.hpp \
    include/libtcod_int.h \
    include/libtcod.h \
    include/libtcod.hpp \
    include/list.h \
    include/list.hpp \
    include/mersenne_types.h \
    include/mersenne.h \
    include/mersenne.hpp \
    include/mouse_types.h \
    include/mouse.h \
    include/mouse.hpp \
    include/namegen.h \
    include/namegen.hpp \
    include/noise_defaults.h \
    include/noise.h \
    include/noise.hpp \
    include/parser.h \
    include/parser.hpp \
    include/path.h \
    include/path.hpp \
    include/sys.h \
    include/sys.hpp \
    include/tree.h \
    include/tree.hpp \
    include/txtfield.h \
    include/txtfield.hpp \
    include/wrappers.h \
    include/zip.h \
    include/zip.hpp \
    intergalacticcloud.h \
    galacticcluster.h \
    inputcontrols.h

DISTFILES += \
    terminal.png \

DEPENDPATH += "/home/anon/src/rltcod/include"
DEPENDPATH += "/home/anon/src/rltcod/lib"

INCLUDEPATH += "/home/anon/src/rltcod/include"
INCLUDEPATH += "/home/anon/src/rltcod/lib"

LIBS += -L"/home/anon/src/rltcod/lib" -ltcod
LIBS += -L"/home/anon/src/rltcod/lib" -ltcodxx
LIBS += -L"/home/anon/src/rltcod/lib" -ltcodgui
#LIBS += -L"/home/anon/src/rltcod/lib" -ltcod_debug
#LIBS += -L"/home/anon/src/rltcod/lib" -ltcodxx_debug

