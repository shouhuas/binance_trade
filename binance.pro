#-------------------------------------------------
#
# Project created by QtCreator 2014-08-14T18:44:11
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
lessThan(QT_MAJOR_VERSION, 5): CONFIG += static
QMAKE_CXXFLAGS = -fpermissive

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
}

INCLUDEPATH += D:\lib\openssl-OpenSSL_1_0_1g\inc32
LIBS += -LD:\usr\local\web\lib -lssleay32 -llibeay32
LIBS += -LC:\Qt\5.2.1-mingw32-rel-static\lib

TARGET = binance_api
TEMPLATE = app


HEADERS += \
    src/qbizmanager.h \
    src/qhttpmanager.h

SOURCES += \
    src/main.cpp \
    src/qbizmanager.cpp \
    src/qhttpmanager.cpp





