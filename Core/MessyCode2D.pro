#-------------------------------------------------
#
# Project created by QtCreator 2017-05-01T16:13:44
#
#-------------------------------------------------
QT       -= gui
CONFIG   += c++11

TARGET = MessyCode2D
TEMPLATE = lib

DEFINES += MESSYCODE2D_LIBRARY \
           DIRECT_INCLUDE

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=\
    src/hierarchy.cpp\
    src/messyEntity.cpp \
    src/transform.cpp \
    src/messyCode2d.cpp \
    src/componentLoader.cpp

HEADERS +=\
    headers/messyComponent.hpp\
    headers/messyEntity.hpp\
    headers/messyModule.hpp\
    headers/hierarchy.hpp \
    headers/messySerializer.hpp \
    headers/transform.hpp \
    headers/messyCode2d.hpp \
    headers/messyConfig.hpp \
    headers/componentLoader.hpp


unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix|win32: LIBS += -L$$PWD/../libs/ecs/ -lecs

INCLUDEPATH += $$PWD/../libs/ecs  \
               $$PWD/../libs/json \
               $$PWD/headers      \
DEPENDPATH += $$PWD/../libs/ecs   \
              $$PWD/../libs/json  \

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../libs/ecs/ecs.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../libs/ecs/libecs.a

release: DESTDIR = $$PWD/../bin/core
debug:   DESTDIR = $$PWD/../bin/core

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
