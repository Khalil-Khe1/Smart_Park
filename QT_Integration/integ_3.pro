QT += network
QT       += core gui sql printsupport multimedia
QT += widgets multimedia

#QT       += core gui sql multimedia multimediawidgets printsupport charts serialport
#QT += core gui charts

TARGET = QTcpSocket
CONFIG   += console
CONFIG   -= app_bundle


TARGET = Atelier_Connexion
TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QRcode.cpp \
    client.cpp \
    connection.cpp \
    jeux.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    place.cpp \
    popup.cpp \
    qcustomplot.cpp \
    serverworker.cpp \
    smtp.cpp \
    smtpYahya.cpp \
    staff.cpp

HEADERS += \
    QRcode.h \
    client.h \
    connection.h \
    jeux.h \
    mainwindow.h \
    menu.h \
    place.h \
    popup.h \
    qcustomplot.h \
    serverworker.h \
    smtp.h \
    smtpYahya.h \
    staff.h

FORMS += \
    mainwindow.ui \
    popup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
