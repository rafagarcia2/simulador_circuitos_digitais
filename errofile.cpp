#include "errofile.h"
#include "ui_errofile.h"

errofile::errofile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::errofile)
{
    ui->setupUi(this);
}

errofile::~errofile()
{
    delete ui;
}

void errofile::on_buttonBox_accepted()
{

}
