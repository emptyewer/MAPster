#-------------------------------------------------
#
# Project created by QtCreator 2016-10-04T17:38:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = MAPster
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    vlistwidget.cpp \
    XMLDomDocument.cpp

HEADERS  += mainwindow.h \
    vlistwidget.h \
    XMLDomDocument.h \
    mystructs.h

FORMS    += mainwindow.ui

macx {
    DDIR = $$OUT_PWD/MAPster.app/Contents/MacOS/hisat2
    copydata.commands = $(COPY_DIR) $$PWD/hisat2/mac $$DDIR
    CDIR = $$OUT_PWD/MAPster.app/Contents/MacOS/configs
    copyconfigs.commands = $(COPY_DIR) $$PWD/configs/ $$CDIR

    first.depends = $(first) copydata copyconfigs
    export(first.depends)
    export(copydata.commands)
    export(copyconfigs.commands)

    QMAKE_EXTRA_TARGETS += first copydata copyconfigs
}

macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/curl/7.50.1/lib/ -lcurl

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/curl/7.50.1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/curl/7.50.1/include

macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/Cellar/curl/7.50.1/lib/libcurl.a

macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/xerces-c/3.1.4/lib/ -lxerces-c

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/xerces-c/3.1.4/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/xerces-c/3.1.4/include

macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/Cellar/xerces-c/3.1.4/lib/libxerces-c.a

macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/boost/1.61.0/lib/ -lboost_container

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.61.0/include/
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.61.0/include/

macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/Cellar/boost/1.61.0/lib/libboost_container.a
