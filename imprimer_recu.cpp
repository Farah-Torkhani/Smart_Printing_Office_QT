#include "imprimer_recu.h"
#include "ui_imprimer_recu.h"
#include "commandes.h"
#include <QDebug>
#include <QTimer>
#include <QPrinter>
#include <QTextDocument>
#include <QPrintDialog>
#include <QtSql/QSqlQueryModel>
#include <QPrintDialog>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDialog>
#include <QDebug>
#include <QTimer>
#include <qtranslator.h>
#include <QPrinter>
#include <QPrintDialog>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QSqlQuery>
QTimer *timer_imprimerRecu = new QTimer();
imprimer_recu::imprimer_recu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imprimer_recu)
{
    ui->setupUi(this);
    connect(timer_imprimerRecu, SIGNAL(timeout()), this, SLOT(setRecuInfo()));
        timer_imprimerRecu->start(100);
}

imprimer_recu::~imprimer_recu()
{
    delete ui;
}


void imprimer_recu::setRecuInfo()
{


    QString descreption="";
    int quantiteCouleur=0;
    QString quantiteSansCouleur="";
    int cinclient=0;
    QString date_Fin="";
    Commandes c(descreption,quantiteCouleur,quantiteSansCouleur,cinclient, date_Fin);


    QSqlQuery commandeInfo = c.afficherCommande(idComm);
    commandeInfo.next();

    ui->descreption->setPlainText(commandeInfo.value(1).toString());
    ui->descreption->setReadOnly(true);

    ui->date->setDate(commandeInfo.value(2).toDate());//.split("T")[0]
    ui->date->setReadOnly(true);

    int cinClient = commandeInfo.value(6).toInt();
    QString cin = commandeInfo.value(6).toString();

    QSqlQuery query;
    query.prepare("select nomclient,prenomClient from clients where CINCLIENT=:cinClient ");
    query.bindValue(":cinClient",cinClient);
    query.exec();
    query.next();

    QString nomClient = query.value(0).toString();
    QString prenomClient = query.value(1).toString();

    //qDebug()<<"idComm=" << idComm;


    ui->nomclient->setText(nomClient);
     ui->nomclient->setReadOnly(true);

    ui->prenomclient->setText(prenomClient);
     ui->prenomclient->setReadOnly(true);

     ui->cinclient->setReadOnly(true);
    ui->cinclient->setText(cin);
    ui->cinclient->setReadOnly(true);

    timer_imprimerRecu->stop();

}

void imprimer_recu::on_valider_clicked()
{
    QPrinter printer;
        QTextDocument doc;
        QString TE = ui->descreption->toPlainText();
        QString Date = ui->date->text();
QString nomc=    ui->nomclient->text();
QString prenomc=ui->prenomclient->text();

        QString strStream;
                       QTextStream out(&strStream);

                       QString TT = QDateTime::currentDateTime().toString();
                       out <<"<html>\n"
                                       "<head>\n"
                                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                          << "<title>ERP - Commande recu<title>\n "
                            << "</head>\n"
      "<body bgcolor=#ffffff link=#5000A0>\n"
                               "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                                                      "<h1 style=\"text-align: center;\"><strong> ******Recu  commandes ****** </strong></h1>";
                                         out << QString("<font size=\"+2\" color=\"red\"> Descreption\n</font>").arg((QString("<font size=\"+5\"&TE;</font>")));
                                         out <<TE;
                                         out << QString("<br><font size=\"+2\" color=\"red\">Date de commande</font>\n").arg((QString("<font size=\"+10\"&Date;</font>")));
                                         out <<Date;
                                           out << QString("<br><font size=\"+2\" color=\"red\">Nom du client</font>\n").arg((QString("<font size=\"+10\"&nomc;</font>")));
                                         out <<nomc;
                                         out << QString("<br><font size=\"+2\" color=\"red\">prenom du client</font>\n").arg((QString("<font size=\"+10\"&prenomc;</font>")));

                                         out <<prenomc;



                                 out <<  "</table>\n"
                                   "</body>\n"
                                       "</html>\n";

                      doc.setHtml(strStream);

         QPrintDialog *dialog = new QPrintDialog(&printer, this);
         dialog->setWindowTitle(tr("Print Document"));

        // if (ui->descreption->textCursor().hasSelection())
             dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);

         if (dialog->exec() == QDialog::Accepted)
             doc.print(&printer);
             return;
}
