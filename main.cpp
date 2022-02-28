#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "connection.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //specific declaration
    //specific declaration

    Connection c;
    bool test=c.createconnect();

    if(!test)
    {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }else {
        //specific declaration
        //specific declaration
        QSplashScreen *splash = new QSplashScreen;
        splash->setPixmap(QPixmap(":/resource/img/splash.jpg"));
        splash->show();
        QTimer::singleShot(1500,splash,&QWidget::close);
        QTimer::singleShot(1500,&w,SLOT(show()));
    }


    return a.exec();
}
