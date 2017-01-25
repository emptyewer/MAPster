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

FORMS    += mainwindow.ui \
    about.ui \
    preferences.ui

DISTFILES += \
    images/done.png \
    images/running.png \
    images/waiting.png

RESOURCES += \
    images.qrc \
    icon.qrc

# Mac Specific Code
macx {
    DDIR = $$OUT_PWD/MAPster.app/Contents/MacOS/hisat2
    copydata.commands = $(COPY_DIR) $$PWD/hisat2/mac $$DDIR
    CDIR = $$OUT_PWD/MAPster.app/Contents/MacOS/configs
    copyconfigs.commands = $(COPY_DIR) $$PWD/configs/ $$CDIR
    IFILE = $$OUT_PWD/MAPster.app/Contents/Info.plist
    copyinfo.commands = $(COPY_FILE) $$PWD/Info.plist $$IFILE

    first.depends = $(first) copydata copyconfigs copyinfo
    export(first.depends)
    export(copydata.commands)
    export(copyconfigs.commands)
    export(copyinfo.commands)

    QMAKE_EXTRA_TARGETS += first copydata copyconfigs copyinfo

    ICON = Icon.icns

    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.10

    INCLUDEPATH += /usr/local/include
    DEPENDPATH += /usr/local/include

    LIBS += -L/usr/local/lib/ -larchive
    PRE_TARGETDEPS += /usr/local/lib/libarchive.a

    LIBS += -L/usr/local/lib/ -lxerces-c
    PRE_TARGETDEPS += /usr/local/lib/libxerces-c.a

    #QMAKE_POST_LINK += "bash /Users/Venky/Work/Softwares/HISAT2/MAPster/post_compile.sh"
    #QMAKE_POST_LINK += "/Users/piperlab/Softwares/Qt5/5.7/clang_64/bin/macdeployqt MAPster.app -dmg -no-strip"
}


