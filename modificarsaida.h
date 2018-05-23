#ifndef MODIFICARSAIDA_H
#define MODIFICARSAIDA_H

#include <QDialog>

/* ======================================================================== *
 * ESSA EH A CLASSE QUE REPRESENTA A CAIXA DE DIALOGO PARA ALTERAR SAIDAS   *
 * ======================================================================== */

namespace Ui {
class ModificarSaida;
}

class ModificarSaida : public QDialog
{
    Q_OBJECT

public:
    explicit ModificarSaida(QWidget *parent = 0);
    ~ModificarSaida();

    // Fixa o limite inferior (-numInputs) e superior (numPortas)
    // do spinBox que eh usado para indicar a origem das saidas
    void setRangeInputs(int minimo, int maximo);
    // Fixa a id da saida que estah sendo modificada
    void setSaida(int IdSaida);

private slots:
    // Altera a origem de uma saida de acordo com o valor especificado pelo usuario
    void on_buttonBox_accepted();

private:
    Ui::ModificarSaida *ui;
    int idSaida;
};

#endif // MODIFICARSAIDA_H
