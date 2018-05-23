#include "newcircuito.h"
#include "ui_newcircuito.h"
#include "maincircuito.h"
#include "circuito_STL.h"
#include <QMessageBox>


NewCircuito::NewCircuito(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCircuito)
{
    ui->setupUi(this);
}

NewCircuito::~NewCircuito()
{
    delete ui;
}

// Cria um novo circuito com as dimensoes especificadas pelo usuario
// Deve chamar a funcao apropriada da classe Circuito
void NewCircuito::on_NewCircuito_accepted()
{
    // Cria um novo circuito com os parametros digitados
    int numInputs, numOutputs, numPortas;
    numInputs = ui->spinNumIn->value();
    numOutputs = ui->spinNumOut->value();
    numPortas = ui->spinNumPortas->value();

    // O circuito deve ser criado usando a funcao apropriada da classe Circuito

    // Provisoriamente, estamos apenas exibindo uma msg
    C.newCircuito(numInputs,numOutputs,numPortas);
    // Depois do novo circuito criado, as tabelas devem ser redimensionadas
    ((MainCircuito*)parentWidget())->redimensiona_tabelas();
}
