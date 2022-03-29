QT       += core gui serialport

QT       += core gui sql
QT       += core gui multimedia multimediawidgets
QT       +=widgets
QT +=svg
QT       += core gui sql charts
QT +=charts
QT +=printsupport

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
    connection.cpp \
    fonctionproduits.cpp \
    main.cpp \
    mainwindow.cpp \
    popup.cpp \
    produits.cpp \
    qrcode.cpp \
    qrcodegeneratordemo.cpp \
    qrcodegeneratorworker.cpp \
    qrwidget.cpp \
    row_table_produits.cpp

HEADERS += \
    connection.h \
    fonctionproduits.h \
    mainwindow.h \
    popup.h \
    produits.h \
    qrcode.h \
    qrwidget.h \
    row_table_produits.h

FORMS += \
    mainwindow.ui \
    produits.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc \
    produits_res.qrc \
    res.qrc

RC_ICONS = myappico.ico
QMAKE_CXXFLAGS += -std=gnu++14
