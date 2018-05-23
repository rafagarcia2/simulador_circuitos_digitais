#ifndef MODIFICARPORTA_H
#define MODIFICARPORTA_H

#include <QDialog>

/* ======================================================================== *
 * ESSA EH A CLASSE QUE REPRESENTA A CAIXA DE DIALOGO PARA ALTERAR PORTAS   *
 * ======================================================================== */

namespace Ui {
class ModificarPorta;
}

class ModificarPorta : public QDialog
{
    Q_OBJECT

public:
    explicit ModificarPorta(QWidget *parent = 0);
    ~ModificarPorta();

    // Fixa o limite inferior (-numInputs) e superior (numPortas)
    // dos spinBoxs que sao usados para indicar a origem das entradas das portas
    void setRangeInputs(int minimo, int maximo);
    // Fixa a id da porta que estah sendo modificada
    void setPorta(int IdPorta);

private slots:
    // Sempre que modificar o tipo de porta, modifica os limites do spinBox que eh utilizado
    // para escolher o numero de entradas daquela porta:
    // NT: de 1 a 1
    // Demais: de 2 a 4
    void on_comboTipoPorta_currentIndexChanged(const QString &arg1);

    // Quando modifica o numero de entradas da porta, habilita apenas os spinBoxs que sao utilizados
    // para indicar a origem do sinal de entradas que existem na porta em questao
    void on_spinNumInputs_valueChanged(int arg1);

    // Altera as caracteristas de uma porta de acordo com os valores especificados pelo usuario
    void on_buttonBox_accepted();

private:
    Ui::ModificarPorta *ui;
    int idPorta;
};

#endif // MODIFICARPORTA_H
