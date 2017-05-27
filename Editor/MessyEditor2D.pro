#-------------------------------------------------
#
# Project created by QtCreator 2017-04-06T16:09:42
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MessyEditor2D
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
    main.cpp \
    src/editorHierarchy.cpp \
    src/messyCommandReceiver.cpp \
    src/messyConsole.cpp \
    src/editorInspector.cpp

HEADERS  += \
    headers/editorHierarchy.hpp \
    headers/messyCommandReceiver.hpp \
    headers/messyConsole.hpp \
    headers/editorInspector.hpp

INCLUDEPATH += $$PWD/../libs/ecs  \
               $$PWD/../libs/json \
               $$PWD/headers      \
               $$PWD/../Core/headers \
DEPENDPATH += $$PWD/../libs/ecs   \
              $$PWD/../libs/json  \

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bin/core/release/ -lMessyCode2D.1.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bin/core/debug/ -lMessyCode2D.1.0.0
else:unix: LIBS += -L$$PWD/../bin/core/ -lMessyCode2D.1.0.0

release: DESTDIR = $$PWD/../bin/editor
debug:   DESTDIR = $$PWD/../bin/editor

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
