#-------------------------------------------------
#
# Project created by QtCreator 2017-05-23T14:52:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VASIC_Qt_GUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

QT += serialport

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
target.path = $$[QT_INSTALL_EXAMPLES]/serialport/enumerator

SOURCES += main.cpp\
        mainwindow.cpp \
    calibrationwindow.cpp \
    taredialog.cpp \
    settingsdialog.cpp \
    avgtimeselection.cpp

HEADERS  += mainwindow.h \
    calibrationwindow.h \
    taredialog.h \
    settingsdialog.h \
    avgtimeselection.h

FORMS    += mainwindow.ui \
    calibrationwindow.ui \
    taredialog.ui \
    settingsdialog.ui \
    avgtimeselection.ui
