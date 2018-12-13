#-------------------------------------------------
#
# Project created by QtCreator 2018-11-10T10:32:33
#
#-------------------------------------------------

QT       += core gui widgets \
            multimedia

TARGET = SpaceOdissey3
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
    jugador.cpp \
    proyectil.cpp \
    controles.cpp \
    usuario.cpp \
    registro.cpp \
    inicio.cpp \
    unodos.cpp \
    menupausa.cpp \
    canon.cpp

HEADERS += \
        mainwindow.h \
    jugador.h \
    proyectil.h \
    controles.h \
    usuario.h \
    registro.h \
    inicio.h \
    unodos.h \
    menupausa.h \
    canon.h

FORMS += \
        mainwindow.ui \
    registro.ui \
    inicio.ui \
    unodos.ui \
    menupausa.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc

DISTFILES += \
    ../SpaceOdissey2/14489_1460037270.mp3 \
    ../SpaceOdissey2/14490_1460037271.mp3 \
    ../SpaceOdissey2/audio.mp3
