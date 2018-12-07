#-------------------------------------------------
#
# Project created by QtCreator 2018-11-21T00:05:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mixologist
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    controller.cpp \
    qsfmlcanvas.cpp \
    customdrinkimporter.cpp \
    gamearea.cpp \
    drink.cpp \
    spritesheet.cpp \
    xmldrinkparser.cpp \
    ingredientsmap.cpp \
    step.cpp \
    customizemenu.cpp \
    recordtracker.cpp \
    liquidphysics.cpp \
    helpmenu.cpp

HEADERS += \
        mainwindow.h \
    controller.h \
    qsfmlcanvas.h \
    ingredients.h \
    customdrinkimporter.h \
    gamearea.h \
    drink.h \
    ingredientsprite.h \
    spritesheet.h \
    xmldrinkparser.h \
    ingredientsmap.h \
    step.h \
    customizemenu.h \
    recordtracker.h \
    liquidphysics.h \
    helpmenu.h

FORMS += \
        mainwindow.ui \
    customdrinkimporter.ui \
    customizemenu.ui \
    helpmenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system


RESOURCES += \
    images.qrc


unix:!macx: LIBS += -L$$PWD/Box2D/Build/bin/x86_64/Debug/ -lBox2D

INCLUDEPATH += $$PWD/Box2D/Build/bin/x86_64/Debug
DEPENDPATH += $$PWD/Box2D/Build/bin/x86_64/Debug

//unix:!macx: PRE_TARGETDEPS += $$PWD/Box2D/Build/bin/x86_64/Debug/libBox2D.a
