#include "circuitovalido.h"
#include "ui_circuitovalido.h"

circuitovalido::circuitovalido(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::circuitovalido)
{
    ui->setupUi(this);
}

circuitovalido::~circuitovalido()
{
    delete ui;
}

void circuitovalido::on_buttonBox_accepted()
{

}
