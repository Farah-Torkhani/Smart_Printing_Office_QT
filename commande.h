#ifndef COMMANDE_H
#define COMMANDE_H



namespace Ui {
class commande;
}

class commande : public QDialog
{
    Q_OBJECT
public:
    explicit commande(QWidget *parent = nullptr);
    ~commande();


private:
    Ui::commande *ui;

};

#endif // COMMANDE_H
