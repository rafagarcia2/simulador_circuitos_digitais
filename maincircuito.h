#ifndef MAINCIRCUITO_H
#define MAINCIRCUITO_H

#include <QMainWindow>
#include <QLabel>
#include "newcircuito.h"
#include "modificarporta.h"
#include "modificarsaida.h"

/* ======================================================================== *
 * ESSA EH A CLASSE QUE REPRESENTA A TELA PRINCIPAL DO APLICATIVO           *
 * ======================================================================== */

namespace Ui {
class MainCircuito;
}

class MainCircuito : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainCircuito(QWidget *parent = 0);
    ~MainCircuito();
    // Funcoes de consulta
    int getNumEntradas() const;
    int getNumSaidas() const;
    int getNumPortas() const;
    // Redimensiona todas as tabelas e reexibe todos os valores da barra de status
    // Essa funcao deve ser chamada sempre que mudar o circuito (digitar ou ler de arquivo)
    void redimensiona_tabelas();
    // Exibe os dados da i-esima porta
    // Essa funcao deve ser chamada sempre que mudar caracteristicas da porta
    // A funcao redimensiona_tabela jah chama essa funcao para todas as portas
    void exibe_porta(int i);
    // Exibe os dados da i-esima saida
    // Essa funcao deve ser chamada sempre que mudar valores da saida
    // A funcao redimensiona_tabela jah chama essa funcao para todas as saidas
    void exibe_saida(int i);
private slots:
    void on_actionSair_triggered();

    // Exibe a caixa de dialogo para fixar caracteristicas de um novo circuito
    void on_actionNovo_triggered();

    // Abre uma caixa de dialogo para ler um arquivo
    void on_actionLer_triggered();

    // Abre uma caixa de dialogo para salvar um arquivo
    void on_actionSalvar_triggered();

    // Gera e exibe a tabela verdade para o circuito
    // Chama a funcao simular da classe circuito
    void on_actionGerar_tabela_triggered();

    // Exibe a caixa de dialogo para fixar caracteristicas de uma porta
    void on_tablePortas_activated(const QModelIndex &index);

    // Exibe a caixa de dialogo para fixar caracteristicas de uma saida
    void on_tableSaidas_activated(const QModelIndex &index);

private:
    Ui::MainCircuito *ui;
    QLabel NumIn;     // Exibe o numero de entradas do circuito na barra de status
    QLabel NumOut;    // Exibe o numero de saidas do circuito na barra de status
    QLabel NumPortas; // Exibe o numero de portas do circuito na barra de status
    NewCircuito newCircuito;        // Caixa de dialogo para criar um novo circuito
    ModificarPorta modificarPorta;  // Caixa de dialogo para modificar uma porta
    ModificarSaida modificarSaida;  // Caixa de dialogo para modificar uma saida
};

#endif // MAINCIRCUITO_H
