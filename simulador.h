#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <QMainWindow>

namespace Ui {
class Simulador;
}

class Simulador : public QMainWindow
{
    Q_OBJECT

public:
    explicit Simulador(QWidget *parent = 0);
    ~Simulador();

private:
    Ui::Simulador *ui;
};

#endif // SIMULADOR_H
