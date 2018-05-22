#include "simulador.h"
#include "ui_simulador.h"

Simulador::Simulador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Simulador)
{
    ui->setupUi(this);
}

Simulador::~Simulador()
{
    delete ui;
}
