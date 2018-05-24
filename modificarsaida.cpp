#include "modificarsaida.h"
#include "ui_modificarsaida.h"
#include "maincircuito.h"
#include "circuito_STL.h"

ModificarSaida::ModificarSaida(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModificarSaida)
{
    ui->setupUi(this);
}

ModificarSaida::~ModificarSaida()
{
    delete ui;
}

// Fixa o limite inferior (-numInputs) e superior (numPortas)
// do spinBox que eh usado para indicar a origem das saidas
void ModificarSaida::setRangeInputs(int minimo, int maximo)
{
    ui->spinOrigemSaida->setRange(minimo,maximo);
}

// Fixa a id da saida que estah sendo modificada
void ModificarSaida::setSaida(int IdSaida)
{
    int numSaidas = ((MainCircuito*)parentWidget())->getNumSaidas();
    if (IdSaida>=1 && IdSaida<=numSaidas)
    {
        idSaida = IdSaida;
        ui->labelIdSaida->setNum(idSaida);
    }
}

// Altera a origem de uma saida de acordo com o valor especificado pelo usuario
void ModificarSaida::on_buttonBox_accepted()
{
    // A origem da saida com id "idSaida" deve ser alterada de acordo
    // com o conteudo do button, chamando um metodo da classe circuito
    int idOutput = ui->spinOrigemSaida->value();

    // Aqui deve ser chamado um metodo da classe Circuito que altere a saida cuja
    // id eh idSaida para que ela assuma a origem especificada por
    // idOutput
    C.setIdOutput(idSaida-1, idOutput);

    // Depois de alterada, deve ser reexibida a saida correspondente
    ((MainCircuito*)parentWidget())->exibe_saida(idSaida-1);
}
