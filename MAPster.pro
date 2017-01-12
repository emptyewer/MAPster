#-------------------------------------------------
#
# Project created by QtCreator 2016-10-04T17:38:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network xml

DEFINES  += QT_NO_SSL

TARGET = MAPster
TEMPLATE = app

ICON = Icon.icns

SOURCES += main.cpp\
        mainwindow.cpp \
    xml/XMLDomDocument.cpp \
    download/downloadmanager.cpp \
    download/downloadmanagerFTP.cpp \
    download/downloadmanagerHTTP.cpp \
    helpers/files.cpp \
    customui/vlistwidget.cpp \
    helpers/runqueue.cpp \
    customui/uielements.cpp \
    helpers/error.cpp

HEADERS  += mainwindow.h \
    xml/XMLDomDocument.h \
    download/downloadmanager.h \
    download/downloadmanagerFTP.h \
    download/downloadmanagerHTTP.h \
    helpers/files.h \
    helpers/keys.h \
    helpers/mystructs.h \
    customui/vlistwidget.h \
    helpers/includes.h \
    helpers/runqueue.h \
    customui/uielements.h \
    helpers/error.h

FORMS    += mainwindow.ui

DISTFILES += \
    images/done.png \
    images/running.png \
    images/waiting.png

RESOURCES += \
    images.qrc

# Mac Specific Code
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

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.10

#QMAKE_POST_LINK += "bash /Users/Venky/Work/Softwares/HISAT2/MAPster/post_compile.sh"

macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lboost_container

INCLUDEPATH += $$PWD/../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../usr/local/include

macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libboost_container.a


macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -larchive

INCLUDEPATH += $$PWD/../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../usr/local/include

macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libarchive.a

macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lxerces-c

INCLUDEPATH += $$PWD/../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../usr/local/include

macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libxerces-c.a
