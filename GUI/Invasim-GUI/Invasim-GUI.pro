#-------------------------------------------------
#
# Project created by QtCreator 2019-05-05T13:38:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Invasim-GUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += NDEBUG

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        IletsView.cpp \
        Processor.cpp \
        ProcessorInfo.cpp \
        ProcessorsView.cpp \
        SimulationDialog.cpp \
        SimulationWindow.cpp \
        main.cpp \
        StartView.cpp \
        ../../src/* \
        MemoryView.cpp

HEADERS += \
        IletsView.h \
        Processor.h \
        ProcessorInfo.h \
        ProcessorView.h \
        SimulationDialog.h \
        SimulationWindow.h \
        StartView.h \
        ../../include/* \
        MemoryView.h

FORMS += \
        IletsView.ui \
        ProcessorInfo.ui \
        SimulationDialog.ui \
        SimulationWindow.ui \
        StartView.ui \
        MemoryView.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    processoricon.qrc

