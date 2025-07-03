QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatPage.cpp \
    chatform.cpp \
    chatpopup.cpp \
    firstscreen.cpp \
    groupchatform.cpp \
    main.cpp \
    mainwindow.cpp \
    patient.cpp \
    patientaddform.cpp \
    patientdeleteform.cpp \
    patientmodifyform.cpp \
    patientsearchform.cpp \
    patientwindow.cpp

HEADERS += \
    chatPage.h \
    chatform.h \
    chatpopup.h \
    firstscreen.h \
    groupchatform.h \
    mainwindow.h \
    patient.h \
    patientaddform.h \
    patientdeleteform.h \
    patientmodifyform.h \
    patientsearchform.h \
    patientwindow.h

FORMS += \
    chatPage.ui \
    chatform.ui \
    chatpopup.ui \
    firstscreen.ui \
    groupchatform.ui \
    mainwindow.ui \
    patient.ui \
    patientaddform.ui \
    patientdeleteform.ui \
    patientmodifyform.ui \
    patientsearchform.ui \
    patientwindow.ui

TRANSLATIONS = dentix_ko.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
