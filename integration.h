#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QMainWindow>

namespace Ui {
class Integration;
}

class Integration : public QMainWindow
{
    Q_OBJECT

public:
    explicit Integration(QWidget *parent = nullptr);
    ~Integration();

private:
    Ui::Integration *ui;
};

#endif // INTEGRATION_H
