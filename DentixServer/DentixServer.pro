QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/server.cpp \
    core/requestdispatcher.cpp \
    model/user.cpp \
    io/jsonfileio.cpp \
    forms/serverinfoform.cpp \
    forms/serverwindow.cpp \
    forms/chatlogform.cpp \
    forms/patientinfoform.cpp \
    main.cpp

HEADERS += \
    core/server.h \
    core/requestdispatcher.h \
    model/user.h \
    io/jsonfileio.h \
    forms/serverinfoform.h \
    forms/serverwindow.h \
    forms/chatlogform.h \
    forms/patientinfoform.h

FORMS += \
    forms/serverinfoform.ui \
    forms/serverwindow.ui \
    forms/chatlogform.ui \
    forms/patientinfoform.ui

TRANSLATIONS += \
    DentixServer_ko_KR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
