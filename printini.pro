QT       += core gui sql charts serialport network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    arduino_client.cpp \
    arduino_machine.cpp \
    arduino_sms_row_table.cpp \
    callard.cpp \
    chat.cpp \
    chatservice.cpp \
    client_fonction.cpp \
    client_row_table.cpp \
    commandes.cpp \
    commandes_row_table.cpp \
    connection.cpp \
    date_fin.cpp \
    descreption_commande.cpp \
    duscene.cpp \
    email.cpp \
    employees.cpp \
    gifanimation.cpp \
    historiques_machine.cpp \
    imprimer_recu.cpp \
    integration.cpp \
    login.cpp \
    machine_fonction.cpp \
    machine_row_table.cpp \
    main.cpp \
    mainwindow.cpp \
    row_table.cpp \
    sms.cpp \
    smtp.cpp

HEADERS += \
    arduino.h \
    arduino_client.h \
    arduino_machine.h \
    arduino_sms_row_table.h \
    callard.h \
    chat.h \
    chatservice.h \
    client_fonction.h \
    client_row_table.h \
    commandes.h \
    commandes_row_table.h \
    connection.h \
    date_fin.h \
    descreption_commande.h \
    duscene.h \
    email.h \
    employees.h \
    gifanimation.h \
    historiques_machine.h \
    imprimer_recu.h \
    integration.h \
    login.h \
    machine_fonction.h \
    machine_row_table.h \
    mainwindow.h \
    row_table.h \
    sms.h \
    smtp.h

FORMS += \
    arduino_client.ui \
    arduino_machine.ui \
    callard.ui \
    chat.ui \
    date_fin.ui \
    descreption_commande.ui \
    email.ui \
    historiques_machine.ui \
    imprimer_recu.ui \
    integration.ui \
    login.ui \
    mainwindow.ui \
    sms.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc \
    Resources.qrc \
    resource.qrc
