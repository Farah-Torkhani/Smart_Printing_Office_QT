QT       += core gui charts sql  printsupport serialport

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
    commandes.cpp \
    commandes_row_table.cpp \
    connection.cpp \
    date_fin.cpp \
    descreption_commande.cpp \
    gestcommandes.cpp \
    imprimer_recu.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    commandes.h \
    commandes_row_table.h \
    connection.h \
    date_fin.h \
    descreption_commande.h \
    gestcommandes.h \
    imprimer_recu.h \
    mainwindow.h

FORMS += \
    date_fin.ui \
    descreption_commande.ui \
    gestcommandes.ui \
    imprimer_recu.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    imgCommande/Logo.png \
    imgCommande/bg.png \
    imgCommande/clock.png \
    imgCommande/edit-icon.png \
    imgCommande/eng.png \
    imgCommande/eraser.png \
    imgCommande/eye.png \
    imgCommande/fr.png \
    imgCommande/imprimante.png \
    imgCommande/lang_icon.png \
    imgCommande/mute.png \
    imgCommande/refresh-button.png \
    imgCommande/refresh.png \
    imgCommande/search.png \
    imgCommande/sort.png \
    imgCommande/trash-icon.png \
    imgCommande/volume.png
