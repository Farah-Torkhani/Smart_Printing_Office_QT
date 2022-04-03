#include "imprimer_recu.h"
#include "ui_imprimer_recu.h"
#include "commandes.h"
#include <QDebug>
#include <QTimer>
#include <QPrinter>
#include <QTextDocument>
#include <QPrintDialog>
QTimer *timer_email = new QTimer();
imprimer_recu::imprimer_recu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imprimer_recu)
{
    ui->setupUi(this);
    connect(timer_email, SIGNAL(timeout()), this, SLOT(setRecuInfo()));
        timer_email->start(100);
}

imprimer_recu::~imprimer_recu()
{
    delete ui;
}


void imprimer_recu::setRecuInfo()
{


      QString descreption="";
    QString etat="";
    int quantiteCouleur=0;
    QString quantiteSansCouleur="";
    int cinemp=0;
    int cinclient=0;

    Commandes c(descreption,etat,quantiteCouleur,quantiteSansCouleur,cinemp,cinclient);


    QSqlQuery commandeInfo = c.afficherCommande(idComm);





    commandeInfo.next();
    ui->descreption->setText(commandeInfo.value(1).toString());
    qDebug()<<"idComm=" << idComm;


    ui->descreption->setReadOnly(true);
    ui->date->setText(commandeInfo.value(2).toString().split("T")[0]);
    ui->date->setReadOnly(true);
   // ui->nomclient->setText(commandeInfo.value(2).toString());
  //  ui->prix->setReadOnly(true);


}

void imprimer_recu::on_valider_clicked()
{
    QPrinter printer;
        QTextDocument doc;
        QString TE = ui->descreption->text();
        QString Date = ui->date->text();


        QString strStream;
                       QTextStream out(&strStream);

                       QString TT = QDateTime::currentDateTime().toString();
                       out <<"<html>\n"
                                       "<head>\n"
                                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                          << "<title>ERP - COMmANDE recu<title>\n "
                            << "</head>\n"
      "<body bgcolor=#ffffff link=#5000A0>\n"
                               "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                                                      "<h1 style=\"text-align: center;\"><strong> ******Recu  commandes ****** </strong></h1>";
                                         out << QString("Descreption\n").arg((QString("&TE;")));
                                         out <<TE;
                                         out << QString("Date de commande\n").arg((QString("&Date;")));
                                         out <<Date;


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
