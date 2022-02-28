#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/resource/img/splash.jpg"));
    splash->show();
    QTimer::singleShot(1500,splash,&QWidget::close);
    QTimer::singleShot(1500,&w,SLOT(show()));


    return a.exec();
}
