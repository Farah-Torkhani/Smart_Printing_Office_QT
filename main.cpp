
#include <QApplication>
#include "gestcommandes.h"
#include "connection.h"
#include <QMessageBox>
#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
QTranslator T;



    Connection c;
    bool test=c.createconnect();

    if(test)
    {//w.show();
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    QStringList languages;
      languages <<"English"<<"French";
      const QString lang=QInputDialog::getItem(NULL,"Select language ","Language",languages);

    {
         T.load(":/anglais1.qm");
    }
    if (lang !="French")
    {
        a.installTranslator(&T);
    }

    Gestcommandes w;

    w.show();
    return a.exec();
}
