#ifndef CIRCUITOVALIDO_H
#define CIRCUITOVALIDO_H

#include <QDialog>

namespace Ui {
class circuitovalido;
}

class circuitovalido : public QDialog
{
    Q_OBJECT

public:
    explicit circuitovalido(QWidget *parent = 0);
    ~circuitovalido();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::circuitovalido *ui;
};

#endif // CIRCUITOVALIDO_H
