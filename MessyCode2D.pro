#-------------------------------------------------
#
# Project created by QtCreator 2017-04-06T16:09:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MessyCode2D
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/components/transform.cpp \
    src/messyCode2D.cpp \
    main.cpp \
    src/modules/editor/editorHierarchy.cpp \
    src/modules/hierarchy.cpp \
    src/messyEntity.cpp

HEADERS  += \
    headers/components/transform.hpp\
    headers/messyCode2D.hpp \
    headers/modules/messyCode2DConfig.hpp \
    headers/modules/messyModule.hpp \
    headers/components/messyComponent.hpp \
    headers/messyEntity.hpp \
    headers/modules/hierarchy.hpp \
    headers/modules/editor/editorHierarchy.hpp


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/ecs/release/ -lecs
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/ecs/debug/ -lecs
else:unix: LIBS += -L$$PWD/libs/ecs/ -lecs

INCLUDEPATH += \
    $$PWD/libs/ecs\
    headers/components\
    headers\
    headers/modules\
    headers/modules/editor/\
DEPENDPATH += $$PWD/libs/ecs

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/ecs/release/libecs.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/ecs/debug/libecs.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/ecs/release/ecs.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/ecs/debug/ecs.lib
else:unix: PRE_TARGETDEPS += $$PWD/libs/ecs/libecs.a
