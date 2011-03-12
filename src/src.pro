#-------------------------------------------------
#
# Project created by QtCreator 2011-03-12T17:17:45
#
#-------------------------------------------------

QT       += core gui network

TARGET = somecover
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    trackerbackend.cpp \
    downloader.cpp \
    entry.cpp

HEADERS  += mainwindow.h \
    trackerbackend.h \
    downloader.h \
    entry.h

FORMS    += mainwindow.ui \
    mainwindow.ui

CONFIG += mobility
MOBILITY = 

symbian {
    TARGET.UID3 = 0xecbd6faf
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

RESOURCES += \
    resources/resources.qrc
