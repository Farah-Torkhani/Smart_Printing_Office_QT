#include "commande.h"
#include "ui_commande.h"

commande::commande(QWidget *parent);
QDialog(parent),
    ui(new Ui::commande)
{

    ui->setupUi(this);

    QBarSet *set0 = new QBarSet("Youssef");
                QBarSet *set1 = new QBarSet("Nombre de clients par mois");
                QBarSet *set2 = new QBarSet("Farah");
                *set1 << 20 << 10 << 40 << 15 << 20 << 30 << 100 << 40 << 10 << 77 << 91 << 13;

                *set2 << 20 << 10 << 40 << 15 << 20 << 30 << 10 << 40 << 10 << 17 << 11 << 13;
                *set0 << 20 << 10 << 40 << 15 << 20 << 30 << 10 << 40 << 10 << 17 << 11 << 13;

                QBarSeries *series = new QBarSeries();

                                series->append(set1);
                                QColor color(0x6568F3);
                                set1->setColor(color);


                                QChart *chart = new QChart();
                                    chart->addSeries(series);
                                    chart->setTitle("");
                                    chart->setAnimationOptions(QChart::SeriesAnimations);
                                    chart->setBackgroundVisible(false);

                                    QStringList categories;
                                                       categories << "Jan" << "Fiv" << "Mar" << "Avr" << "Mai" << "Juin" << "Jui" <<"Aou" << "sep" << "Oct" << "Nov" << "Dec" ;
                                                       QBarCategoryAxis *axis = new QBarCategoryAxis();
                                                       axis->append(categories);
                                                       chart->createDefaultAxes();
                                                       chart->setAxisX(axis, series);

                                                       chart->setVisible(true);
                                                                           chart->legend()->setAlignment(Qt::AlignBottom);




                                                                           QChartView *chartView = new QChartView(chart);

                                                                           chartView->setRenderHint(QPainter::Antialiasing);
                                                                           QPalette pal = qApp->palette();
                                                                           pal.setColor(QPalette::WindowText, QRgb(0x6568F3));
                                                                           pal.setColor(QPalette::Window, QRgb(0x6568F3));
                                                                           qApp->setPalette(pal);

                                                                           chartView->setMaximumWidth(550);
                                                                           chartView->setMaximumHeight(290);


                                                                           chartView->setParent(ui->horizontalFrame);

}

commande::~commande()
{
    delete ui;
}

