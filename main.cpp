#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "connection.h"
#include <QMessageBox>
#include "login.h"
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTranslator T;

    //specific declaration
    Login l;
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
        QStringList languages;
              languages <<"French"<<"English";
              const QString lang=QInputDialog::getItem(NULL,"Select language ","Language",languages);

            {
                 T.load(":/resource/img/anglais.qm");
            }
            if (lang !="French")
            {
                a.installTranslator(&T);
            }


        splash->show();
        QTimer::singleShot(500,splash,&QWidget::close);
        QTimer::singleShot(500,&l,SLOT(show()));
    }


    return a.exec();
}
