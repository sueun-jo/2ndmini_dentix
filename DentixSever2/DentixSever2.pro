QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatlog.cpp \
    jsonhandler.cpp \
    main.cpp \
    patientinfoform.cpp \
    server.cpp \
    serverinfoform.cpp \
    serverwindow.cpp

HEADERS += \
    chatlog.h \
    jsonhandler.h \
    patientinfoform.h \
    server.h \
    serverinfoform.h \
    serverwindow.h

FORMS += \
    chatlog.ui \
    patientinfoform.ui \
    serverinfoform.ui \
    serverwindow.ui

TRANSLATIONS += \
    DentixSever2_ko_KR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
