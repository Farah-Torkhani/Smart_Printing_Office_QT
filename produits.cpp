#include "produits.h"
#include "fonctionproduits.h"
#include "ui_produits.h"
#include <stdlib.h>
#include "row_table_produits.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QScrollArea>
#include "qrcode.h"
#include <QtSvg/QSvgRenderer>
#include <fstream>

QVBoxLayout *layoutt = new QVBoxLayout();
QTimer *timer = new QTimer();
QTimer *timer2 = new QTimer();
QTimer *timer3 = new QTimer();
int id=0,idd=0;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;
produits::produits(QWidget *parent)  :
      QMainWindow(parent),
      ui(new Ui::produits)

{
    ui->setupUi(this);
    ui->edit_prix->setValidator(new QIntValidator (0,99999999,ui->edit_prix));
    ui->edit_qu->setValidator(new QIntValidator (0,99999999,ui->edit_qu));
    Produits p;

    ui->tab_produits->setModel(p.affichertr());
    ui->scrollArea->setWidget( ui->scrollAreaContents );

    ui->scrollAreaContents ->setLayout( layoutt );

    qDebug()<< "aaaaaaaaaa";

    QSqlQuery pro_liste = p.afficherAll();

    while (pro_liste.next()) {
        row_table_produits *row = new row_table_produits(ui->scrollArea,pro_liste.value(0).toString(),pro_liste.value(1).toString(),pro_liste.value(2).toString(),pro_liste.value(3).toString(),pro_liste.value(4).toString());
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
        qDebug()<< "tttttttttttttt";
    }

    connect(timer, SIGNAL(timeout()), this, SLOT(setFormulaire()));
    //timer->start(500);

    connect(timer2, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked()));
    timer2->start(200);

    connect(timer3, SIGNAL(timeout()), this, SLOT(setQR()));
    //timer->start(500);


    QBarSet *set0 = new QBarSet("Quantité des produits a consommés");
int a=p.statistiquesProduits("MAR");
    *set0 << a << p.statistiquesProduits("MAR") << p.statistiquesProduits("MAR") << p.statistiquesProduits("MAR") << p.statistiquesProduits("MAR") << p.statistiquesProduits("MAR") << p.statistiquesProduits("MAR") << p.statistiquesProduits("MAR") << p.statistiquesProduits("MAR") << p.statistiquesProduits("MAR") <<p.statistiquesProduits("MAR") << p.statistiquesProduits("MAR");


    QColor color(0x6568F3);
    set0->setColor(color);

    QBarSeries *series = new QBarSeries();
    series->append(set0);




    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundVisible(false);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jui" << "Aou" << "Sep" << "Oct" << "Nov" << "Dec";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    QChartView *chartView = new QChartView(chart);

    chartView->setMaximumWidth(631);
    chartView->setMaximumHeight(300);
    chartView->setParent(ui->horizontalFrame);
    chart->legend()->setAlignment(Qt::AlignBottom);
Produits c;
    QPieSeries *series1 = new QPieSeries();
    series1->append("Feuilles A4", .40);
    series1->append("Encres", .100);
    series1->append("Agrafeuse", .30);
    series1->append("Spirals", .12);
    series1->append("Feuilles A3", .75);

    QPieSlice *slice0 = series1->slices().at(0);
    slice0->setLabelVisible();

    QPieSlice *slice1 = series1->slices().at(1);
   // slice1->setExploded();
    slice1->setLabelVisible();
   // slice1->setPen(QPen(Qt::color1, 0));
   // slice1->setBrush(Qt::color1);

    QPieSlice *slice2 = series1->slices().at(2);
    slice2->setLabelVisible();

    QPieSlice *slice3 = series1->slices().at(3);
    slice3->setLabelVisible();

    QPieSlice *slice4 = series1->slices().at(4);
    slice4->setLabelVisible();

    QColor color0(0x6568F3);
    slice0->setColor(color);

    QColor color1(0x341763);
    slice1->setColor(color1);

    QColor color2(0xFF7244);
    slice2->setColor(color2);

    QColor color3(0x585856);
    slice3->setColor(color3);

    QColor color4(0x6568F3);
    slice4->setColor(color4);


    QChart *chart1 = new QChart();
    chart1->addSeries(series1);
    chart1->setTitle("Quantité des produits en stock");
    chart1->legend()->hide();
    chart1->setBackgroundVisible(false);


    QChartView *chartView1 = new QChartView(chart1);

    chartView1->setMaximumWidth(500);
    chartView1->setMaximumHeight(260);
    chartView1->setParent(ui->circleFrame);







    popUp = new PopUp();


}
/*
void produits::on_pushButton_clicked()
{

    popUp->setPopupText("ui->edit_nom->toPlainText()");

    popUp->show();
}
*/
produits::~produits()
{

    delete ui;
}


void produits::on_valider_b_clicked()
{

        QString nomProduits=ui->edit_nom->text();
        QString quantite=ui->edit_qu->text();
        QString type=ui->edit_type->text();
        QString prixunitaire=ui->edit_prix->text();


        Produits P(nomProduits,quantite,type,prixunitaire);

        bool test=P.ajouter();

       if(test)
        {
           QMessageBox::information(nullptr,QObject::tr("ok"),
                                  QObject::tr(" effectue\n"
                                              "click cancel to exit."),QMessageBox::Cancel);
       }
       else  QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                      QObject::tr("non effectue\n"
                                                "click cancel to exit."),QMessageBox::Cancel);

       while(!layoutt->isEmpty()){
       QLayoutItem* item = layoutt->itemAt(0);
       layoutt->removeItem(item);
       QWidget* widgett = item->widget();
       if(widgett)
           {
               delete widgett;
           }
       }


       QSqlQuery pro_liste = P.afficherAll();
       while (pro_liste.next()) {
           row_table_produits *row = new row_table_produits(ui->scrollArea,pro_liste.value(0).toString(),pro_liste.value(1).toString(),pro_liste.value(2).toString(),pro_liste.value(3).toString(),pro_liste.value(4).toString());
           row->setMinimumHeight(34);
           layoutt->addWidget( row );
       }
       popUp->setPopupText(nomProduits+" est bien ajouter");

       popUp->show();
}

void row_table_produits::deleteBtn_clicked()
{

    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int id = buttonSender->whatsThis().toInt();

    Produits p;
    p.supprimer(id);

    while(!layoutt->isEmpty()){
    QLayoutItem* item = layoutt->itemAt(0);
    layoutt->removeItem(item);
    QWidget* widgett = item->widget();
    if(widgett)
        {
            delete widgett;
        }
    }



}
void row_table_produits::editBtn_clicked()
{

    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    id = buttonSender->whatsThis().toInt();
    timer->start(500);
}
void row_table_produits::qrGBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    idd = buttonSender->whatsThis().toInt();
    timer3->start(500);
}
void produits::setQR()
{
    int reference=idd;
    const QrCode qr = QrCode::encodeText(std::to_string(reference).c_str(), QrCode::Ecc::LOW);
    std::ofstream myfile;
    myfile.open ("qrcode.svg") ;
    myfile << qr.toSvgString(1);
    myfile.close();
    QSvgRenderer svgRenderer(QString("qrcode.svg"));
    QPixmap pix( QSize(120, 120) );
    QPainter pixPainter( &pix );
    svgRenderer.render( &pixPainter );
    ui->QRCODE_3->setPixmap(pix);
    bool inputsFocus = ui->QRCODE_3->hasFocus();
    if(inputsFocus){
        timer3->stop();

    }
}

void produits::setFormulaire()
{
    if(id != -999999999){
        Produits p;
        QSqlQuery emp = p.afficherPr(id);
        emp.next();
        ui->edit_nom->setText(emp.value(1).toString());
        ui->edit_type->setText(emp.value(3).toString());
        ui->edit_prix->setText(emp.value(4).toString()); //tel 3
        ui->edit_qu->setText(emp.value(2).toString()); //salaire 4

        bool inputsFocus = ui->edit_nom->hasFocus() || ui->edit_type->hasFocus() || ui->edit_prix->hasFocus() || ui->edit_qu->hasFocus();
        int reference=id;
        const QrCode qr = QrCode::encodeText(std::to_string(reference).c_str(), QrCode::Ecc::LOW);
        std::ofstream myfile;
        myfile.open ("qrcode.svg") ;
        myfile << qr.toSvgString(1);
        myfile.close();
        QSvgRenderer svgRenderer(QString("qrcode.svg"));
        QPixmap pix( QSize(120, 120) );
        QPainter pixPainter( &pix );
        svgRenderer.render( &pixPainter );
        ui->QRCODE_3->setPixmap(pix);

        if(inputsFocus){
            timer->stop();

        }
    }
}
void produits::on_refreshBtn_clicked()
{
    while(!layoutt->isEmpty()){
        QLayoutItem* item = layoutt->itemAt(0);
        layoutt->removeItem(item);
        QWidget* widgett = item->widget();
        if(widgett)
            {
                delete widgett;
            }
    }


    Produits P;
    QSqlQuery pro_liste = P.afficherAll();
    while (pro_liste.next()) {
        row_table_produits *row = new row_table_produits(ui->scrollArea,pro_liste.value(0).toString(),pro_liste.value(1).toString(),pro_liste.value(2).toString(),pro_liste.value(3).toString(),pro_liste.value(4).toString());
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }


}



void produits::on_modifier_b_clicked()
{
    QString nomproduit = ui->edit_nom->text();
    QString type = ui->edit_type->text();
    QString quantite = ui->edit_qu->text();
    QString prix = ui->edit_prix->text();

    Produits P(nomproduit,quantite,type,prix);
    bool test = P.modifier(id);

    if(test){
        QMessageBox::information(nullptr, QObject::tr("update status"),QObject::tr("produit updated.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("produit not updated.\nClick Cancel to exit."), QMessageBox::Cancel);
    }


}

void produits::on_b_searsh_clicked()
{
    QString chaine_r=ui->edit_r->text();


    while(!layoutt->isEmpty()){
    QLayoutItem* item = layoutt->itemAt(0);
    layoutt->removeItem(item);
    QWidget* widgett = item->widget();
    if(widgett)
        {
            delete widgett;
        }
    }

Produits P;
    QSqlQuery pro_liste = P.rechercher(chaine_r);
    while (pro_liste.next()) {
        row_table_produits *r = new row_table_produits(ui->scrollArea,pro_liste.value(0).toString(),pro_liste.value(1).toString(),pro_liste.value(2).toString(),pro_liste.value(3).toString(),pro_liste.value(4).toString());
        r->setMinimumHeight(34);
        layoutt->addWidget( r );
    }
    connect(timer, SIGNAL(timeout()), this, SLOT(setFormulaire()));
    //timer->start(500);

    connect(timer2, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked()));
    timer2->start(5000);

}
void produits::on_edit_r_textChanged(const QString &arg1)
{
    on_b_searsh_clicked();
}

void produits::on_excel_clicked()
{


    QString nomMachine="";
    QString machineImg="";
    int etatMachine=0;
    int prixMachine=0;


    Produits m;

    QTableView *table=new QTableView;
    table->setModel(m.afficherProduitForExcel());



               QString filters("CSV files (*.csv);;All files (.*)");
               QString defaultFilter("CSV files (*.csv)");//
               QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                  filters, &defaultFilter);//d:fenetre d'enrgtr
               QFile file(fileName);

               QAbstractItemModel *model =  table->model();
               if (file.open(QFile::WriteOnly | QFile::Truncate)) {//tc:type de fch
                   QTextStream data(&file);
                   QStringList strList;//separation des chaines


                   for (int i = 0; i < model->columnCount(); i++)
                   {
                       if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                           strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                       else
                           strList.append("");
                   }

                   data << strList.join(";") << "\n";


                   for (int i = 0; i < model->rowCount(); i++)
                   {
                       strList.clear();
                       for (int j = 0; j < model->columnCount(); j++)
                       {

                           if (model->data(model->index(i, j)).toString().length() > 0)
                               strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                           else
                               strList.append("");
                       }
                   data << strList.join(";") + "\n";
                   }
                   file.close();
                   QMessageBox::information(nullptr, QObject::tr("Export excel"),
                                             QObject::tr("Export avec succes .\n"
                                                         "Click OK to exit."), QMessageBox::Ok);
               }
}




