#include "modificarporta.h"
#include "ui_modificarporta.h"
#include "maincircuito.h"
#include "circuito_STL.h"

ModificarPorta::ModificarPorta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModificarPorta),
    idPorta(0)
{
    ui->setupUi(this);

    // Inclui os tipos de portas
    ui->comboTipoPorta->addItems(QStringList() << "NT" << "AN" << "OR" << "XO" << "NA" << "NO" << "NX");
    // Seleciona o primeiro tipo de porta (NOT)
    ui->comboTipoPorta->setCurrentIndex(0);

    // Como o index foi alterado via programa, chama on_comboTipoPorta_currentIndexChanged

    // Desabilita os widgets das entradas 2, 3 e 4, jah que portas NOT soh teem uma entrada
    ui->labelInput2->setEnabled(false);
    ui->spinInput2->setEnabled(false);
    ui->labelInput3->setEnabled(false);
    ui->spinInput3->setEnabled(false);
    ui->labelInput4->setEnabled(false);
    ui->spinInput4->setEnabled(false);
}

ModificarPorta::~ModificarPorta()
{
    delete ui;
}

// Fixa a id da porta que estah sendo modificada
void ModificarPorta::setPorta(int IdPorta)
{
    int numPortas = ((MainCircuito*)parentWidget())->getNumPortas();
    if (IdPorta>=1 && IdPorta<=numPortas)
    {
        idPorta = IdPorta;
        ui->labelIdPorta->setNum(idPorta);
    }
}

// Fixa o limite inferior (-numInputs) e superior (numPortas)
// dos spinBoxs que sao usados para indicar a origem das entradas das portas
void ModificarPorta::setRangeInputs(int minimo, int maximo)
{
    ui->spinInput1->setRange(minimo,maximo);
    ui->spinInput2->setRange(minimo,maximo);
    ui->spinInput3->setRange(minimo,maximo);
    ui->spinInput4->setRange(minimo,maximo);
}

// Sempre que modificar o tipo de porta, modifica os limites do spinBox que eh utilizado
// para escolher o numero de entradas daquela porta:
// NT: de 1 a 1
// Demais: de 2 a 4
void ModificarPorta::on_comboTipoPorta_currentIndexChanged(const QString &arg1)
{
    // Fixa os limites para o numero de entradas: de 1 a 1 se for NT, 2 a 4 para outros tipos
    if (arg1=="NT") ui->spinNumInputs->setRange(1,1);
    else ui->spinNumInputs->setRange(2,4);
}

// Quando modifica o numero de entradas da porta, habilita apenas os spinBoxs que sao utilizados
// para indicar a origem do sinal de entradas que existem na porta em questao
void ModificarPorta::on_spinNumInputs_valueChanged(int arg1)
{
    ui->labelInput2->setEnabled(arg1 >= 2);
    ui->spinInput2->setEnabled(arg1 >= 2);
    ui->labelInput3->setEnabled(arg1 >= 3);
    ui->spinInput3->setEnabled(arg1 >= 3);
    ui->labelInput4->setEnabled(arg1 >= 4);
    ui->spinInput4->setEnabled(arg1 >= 4);
}

// Altera as caracteristas de uma porta de acordo com os valores especificados pelo usuario
void ModificarPorta::on_buttonBox_accepted()
{
    // Os valores da porta com id "idPorta" devem ser alterados de acordo
    // com o conteudo dos buttons, chamando um metodo da classe circuito
    QString tipoPorta = ui->comboTipoPorta->currentText();
    int numInputsPorta = ui->spinNumInputs->value();
    int idInputPorta[] = {ui->spinInput1->value(),
                          ui->spinInput2->value(),
                          ui->spinInput3->value(),
                          ui->spinInput4->value()};

    // Aqui deve ser chamado um metodo da classe Circuito que altere a porta cuja
    // id eh idPorta para que ela assuma as caracteristicas especificadas por
    // tipoPorta, numInputsPorta, idInputPorta[]
    C.replace(idPorta,tipoPorta.toStdString(),numInputsPorta,idInputPorta);

    // Depois de alterado, deve ser reexibida a porta correspondente
    ((MainCircuito*)parentWidget())->exibe_porta(idPorta-1);
}
