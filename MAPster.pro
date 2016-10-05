#-------------------------------------------------
#
# Project created by QtCreator 2016-10-04T17:38:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MAPster
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

macx {
    DDIR = $$OUT_PWD/MAPster.app/Contents/MacOS/hisat2
    copydata.commands = $(COPY_DIR) $$PWD/hisat2/mac $$DDIR
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}
