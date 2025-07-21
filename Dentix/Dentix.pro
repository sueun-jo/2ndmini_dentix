QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appcontroller.cpp \
    chatbasicform.cpp \
    chatgroupform.cpp \
    chatinvitedform.cpp \
    chatmanager.cpp \
    chatwindow.cpp \
    client.cpp \
    datadispatcher.cpp \
    firstscreen.cpp \
    loginmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    patient.cpp \
    patientaddform.cpp \
    patientdeleteform.cpp \
    patientmanager.cpp \
    patientmodifyform.cpp \
    patientsearchform.cpp \
    patientwindow.cpp

HEADERS += \
    appcontroller.h \
    chatbasicform.h \
    chatgroupform.h \
    chatinvitedform.h \
    chatmanager.h \
    chatwindow.h \
    client.h \
    datadispatcher.h \
    firstscreen.h \
    loginmanager.h \
    mainwindow.h \
    patient.h \
    patientaddform.h \
    patientdeleteform.h \
    patientmanager.h \
    patientmodifyform.h \
    patientsearchfilter.h \
    patientsearchform.h \
    patientwindow.h

FORMS += \
    chatbasicform.ui \
    chatgroupform.ui \
    chatinvitedform.ui \
    chatwindow.ui \
    firstscreen.ui \
    mainwindow.ui \
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
