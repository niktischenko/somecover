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

unix {
  #VARIABLES
  isEmpty(PREFIX) {
    PREFIX = /usr
  }
  BINDIR = $$PREFIX/bin
  DATADIR =$$PREFIX/share

  DEFINES += DATADIR=\\\"$$DATADIR\\\" PKGDATADIR=\\\"$$PKGDATADIR\\\"

  #MAKE INSTALL

  INSTALLS += target desktop service iconxpm icon26 icon48 icon64

  target.path =$$BINDIR

  desktop.path = $$DATADIR/applications/hildon
  desktop.files += resources/*.desktop

  service.path = $$DATADIR/dbus-1/services
  service.files += $${TARGET}.service

  icon64.path = $$DATADIR/icons/hicolor/64x64/apps
  icon64.files += resources/*.png
}

