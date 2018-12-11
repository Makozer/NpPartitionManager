#-------------------------------------------------
#
# Project created by QtCreator 2018-08-27T14:11:44
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = NpPartitionManager
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
    BackEnd/coin.cpp \
    BackEnd/liststash.cpp \
    BackEnd/memento.cpp \
    BackEnd/morphlarva.cpp \
    BackEnd/rngesus.cpp \
    BackEnd/vectorstash.cpp \
    GUI/custombutton.cpp \
    GUI/customonlynumberslineedit.cpp \
    GUI/customtextedit.cpp \
    GUI/exportdialog.cpp \
    GUI/importdialog.cpp \
    GUI/mainwindow.cpp \
    main.cpp \
    BackEnd/coin.cpp \
    BackEnd/liststash.cpp \
    BackEnd/memento.cpp \
    BackEnd/morphlarva.cpp \
    BackEnd/rngesus.cpp \
    BackEnd/vectorstash.cpp \
    BackEnd/seacher/searchJinJang.cpp \
    BackEnd/coin.cpp \
    BackEnd/liststash.cpp \
    BackEnd/memento.cpp \
    BackEnd/morphlarva.cpp \
    BackEnd/rngesus.cpp \
    BackEnd/vectorstash.cpp \
    BackEnd/seacher/searcher.cpp

HEADERS += \
    BackEnd/coin.h \
    BackEnd/liststash.h \
    BackEnd/memento.h \
    BackEnd/morphlarva.h \
    BackEnd/rngesus.h \
    BackEnd/vectorstash.h \
    GUI/custombutton.h \
    GUI/customonlynumberslineedit.h \
    GUI/customtextedit.h \
    GUI/exportdialog.h \
    GUI/importdialog.h \
    GUI/mainwindow.h \
    BackEnd/coin.h \
    BackEnd/liststash.h \
    BackEnd/memento.h \
    BackEnd/morphlarva.h \
    BackEnd/rngesus.h \
    BackEnd/vectorstash.h \
    BackEnd/seacher/searchJinJang.h \
    BackEnd/coin.h \
    BackEnd/liststash.h \
    BackEnd/memento.h \
    BackEnd/morphlarva.h \
    BackEnd/rngesus.h \
    BackEnd/vectorstash.h \
    BackEnd/seacher/searcher.h

FORMS += \
    GUI/exportdialog.ui \
    GUI/importdialog.ui \
    GUI/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    facultyresearch.txt \
    icon/uniIcon.ico \
    icon/icon.rc \
    icon/icon.rc.bin

RC_FILE = icon/icon.rc
