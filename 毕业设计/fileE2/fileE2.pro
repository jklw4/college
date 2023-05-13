#-------------------------------------------------
#
# Project created by QtCreator 2023-04-01T18:47:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fileE2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    key_change.cpp \
    sm4_crypto.cpp \
    sm2_key_manage.cpp \
    sm3_sign.cpp \
    sm3_veri.cpp \
    filesigner.cpp \
    tool.cpp \
    keyexchange.cpp \
    filecrypt.cpp \
    customlineedit.cpp

HEADERS += \
        mainwindow.h \
    key_change.h \
    sm4_crypto.h \
    sm2_key_manage.h \
    sm3_sign.h \
    sm3_veri.h \
    filesigner.h \
    tool.h \
    keyexchange.h \
    filecrypt.h \
    customlineedit.h

FORMS += \
        mainwindow.ui \
    key_change.ui \
    sm4_crypto.ui \
    sm3_sign.ui \
    sm3_veri.ui

INCLUDEPATH += "C:\Users\jklw4\MinGw64\mingw32\opt\include"
LIBS += -L"C:\Users\jklw4\MinGw64\mingw32\opt\lib" -lcrypto -lssl

#INCLUDEPATH += $$quote(C:/Program Files/OpenSSL-Win64/include)
#LIBS += -L$$quote(C:/Program Files/OpenSSL-Win64/lib) -lcrypto -lssl

RESOURCES += \
    resources.qrc

