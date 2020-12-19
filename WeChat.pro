#-------------------------------------------------
#
# Project created by QtCreator 2020-12-07T08:03:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeChat
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


SOURCES += \
        main.cpp \
        widget.cpp \
    frontserve.cpp \
    backcontrol.cpp \
    sortwin.cpp \
    search_class_win.cpp \
    cover_win.cpp \
    search_user_win.cpp \
    manage.cpp \
    login.cpp \
    search_dis_win.cpp

HEADERS += \
        widget.h \
    frontserve.h \
    backcontrol.h \
    sortwin.h \
    search_class_win.h \
    cover_win.h \
    data.h \
    hash.h \
    group.h \
    search_user_win.h \
    manage.h \
    login.h \
    search_dis_win.h

FORMS += \
        widget.ui

RESOURCES += \
    resource.qrc
#OTHER_FILES += myapp.rc

RC_FILE += myappico.rc
