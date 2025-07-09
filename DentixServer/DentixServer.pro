QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatting.cpp \
    patient.cpp \
    patientinfocontroller.cpp \
    patientmanager.cpp \
    patientrepository.cpp \
    responsefactory.cpp \
    server.cpp \
    requestdispatcher.cpp \
    user.cpp \
    jsonfileio.cpp \
    serverinfoform.cpp \
    serverwindow.cpp \
    chatlogform.cpp \
    patientinfoform.cpp \
    userrepository.cpp \
    main.cpp \
    usermanager.cpp

HEADERS += \
    chatting.h \
    logutil.h \
    patient.h \
    patientinfocontroller.h \
    patientmanager.h \
    patientrepository.h \
    patientsearchfilter.h \
    responsefactory.h \
    server.h \
    requestdispatcher.h \
    user.h \
    jsonfileio.h \
    serverinfoform.h \
    serverwindow.h \
    chatlogform.h \
    patientinfoform.h \
    userrepository.h \
    usermanager.h

FORMS += \
    serverinfoform.ui \
    serverwindow.ui \
    chatlogform.ui \
    patientinfoform.ui

TRANSLATIONS += \
    DentixServer_ko_KR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
