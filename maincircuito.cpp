#include "maincircuito.h"
#include "ui_maincircuito.h"
#include "modificarporta.h"
#include "modificarsaida.h"
#include "circuito_STL.h"
#include <QStringList>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <time.h>
#include <vector>

MainCircuito::MainCircuito(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainCircuito),
    NumIn(this),
    NumOut(this) ,
    NumPortas(this),
    newCircuito(this),
    modificarPorta(this),
    modificarSaida(this)
{
    ui->setupUi(this);

    // Cabecalhos da tabela de portas
    ui->tablePortas->setHorizontalHeaderLabels(QStringList() << "TIPO" << "Nº\nENTR"
                                               << "ENTR\n1" << "ENTR\n2" << "ENTR\n3" << "ENTR\n4");
    ui->tableSaidas->setHorizontalHeaderLabels(QStringList() << "ORIG\nSAÍDA");

    // Insere os widgets da barra de status
    statusBar()->insertWidget(0,new QLabel("Nº entradas: "));
    statusBar()->insertWidget(1,&NumIn);
    statusBar()->insertWidget(2,new QLabel("   Nº saídas: "));
    statusBar()->insertWidget(3,&NumOut);
    statusBar()->insertWidget(4,new QLabel("   Nº portas: "));
    statusBar()->insertWidget(5,&NumPortas);

    // Redimensiona todas as tabelas e reexibe os valores da barra de status
    // Essa funcao deve ser chamada sempre que mudar o circuito
    redimensiona_tabelas();

}

MainCircuito::~MainCircuito()
{
    delete ui;
}

// Funcoes de consulta
int MainCircuito::getNumEntradas() const
{
    int numCombinacoesEntrada = ui->tableTabelaVerdade->rowCount() - 1;
    if (numCombinacoesEntrada <= 0) return 0;

    int numInputs = round(log(numCombinacoesEntrada)/log(3));
    return numInputs;
}

int MainCircuito::getNumSaidas() const
{
    return ui->tableSaidas->rowCount();
}

int MainCircuito::getNumPortas() const
{
    return ui->tablePortas->rowCount();
}

// Redimensiona todas as tabelas e reexibe todos os valores da barra de status
// Essa funcao deve ser chamada sempre que mudar o circuito (digitar ou ler de arquivo)
void MainCircuito::redimensiona_tabelas()
{
    int numInputs, numOutputs, numPortas;
    QString texto;
    QLabel *prov;
    int i;

    // Esses numeros devem ser lidos a partir de metodos de consulta da classe Circuito
    // Para fazer um teste, vamos atribuir quantidades aleatorias
    srand(time(NULL));
    numInputs = C.getNin();
    numOutputs = C.getNout();
    numPortas = C.getNportas();

    // ==========================================================
    // Ajusta os valores da barra de status
    // ==========================================================

    NumIn.setNum(numInputs);
    NumOut.setNum(numOutputs);
    NumPortas.setNum(numPortas);

    // ==========================================================
    // Redimensiona a tabela das portas e conexoes
    // ==========================================================

    // Limpa o conteudo, mas nao os cabecalhos
    ui->tablePortas->clearContents();

    ui->tablePortas->setRowCount(numPortas);
    for (i=0; i<numPortas; i++)
    {
        exibe_porta(i);
    }

    // ==========================================================
    // Redimensiona a tabela de saidas
    // ==========================================================

    // Limpa o conteudo, mas nao os cabecalhos
    ui->tableSaidas->clearContents();

    ui->tableSaidas->setRowCount(numOutputs);
    for (i=0; i<numOutputs; i++)
    {
        exibe_saida(i);
    }

    // ==========================================================
    // Redimensiona a tabela verdade
    // ==========================================================

    // Antes de redimensionar a tabela, anula todos os setSpan da primeira linha
    // Se nao fizer isso, dah erro ao redimensionar
    ui->tableTabelaVerdade->clearSpans();

    // Limpa todo o conteudo, inclusive cabecalhos
    ui->tableTabelaVerdade->clear();

    // Modifica as dimensoes
    ui->tableTabelaVerdade->setColumnCount(numInputs+numOutputs);
    int numCombinacoesEntrada = (numInputs>0 ? round(pow(3,numInputs)) : 0);
    // a tabela verdade tem uma linha a mais do que o numero de combinacoes de entrada
    // para conter o cabecalho
    ui->tableTabelaVerdade->setRowCount(1 + numCombinacoesEntrada);

    // Cria os cabecalhos na primeira linha
    // Entradas
    if (numInputs > 0)
    {
        ui->tableTabelaVerdade->setSpan(0,0,1,numInputs);
        prov = new QLabel("ENTRADAS");
        prov->setAlignment(Qt::AlignCenter);
        prov->setStyleSheet("font-weight: bold");
        ui->tableTabelaVerdade->setCellWidget(0,0,prov);
    }
    // Saidas
    if (numOutputs > 0)
    {
        ui->tableTabelaVerdade->setSpan(0,numInputs,1,numOutputs);
        prov = new QLabel("SAÍDAS");
        prov->setAlignment(Qt::AlignCenter);
        prov->setStyleSheet("font-weight: bold");
        ui->tableTabelaVerdade->setCellWidget(0,numInputs,prov);
    }

    // ==========================================================
    // Fixa os limites para os spin boxs de entradas de portas (classe ModificarPorta)
    // ==========================================================

    modificarPorta.setRangeInputs(-numInputs, numPortas);

    // ==========================================================
    // Fixa os limites para os spin boxs de origem das saidas (classe ModificarSaida)
    // ==========================================================

    modificarSaida.setRangeInputs(-numInputs, numPortas);
}

// Exibe os dados da i-esima porta
// Essa funcao deve ser chamada sempre que mudar caracteristicas da porta
// A funcao redimensiona_tabela jah chama essa funcao para todas as portas
void MainCircuito::exibe_porta(int i)
{
    if (i >= getNumPortas()) return;

    QString nomePorta;
    int numInputsPorta, idInputPorta[4];

    QLabel *prov;
    int j;

    // Esses valores (nomePorta, numInputsPorta, idInputPorta[])
    // devem ser lidos a partir de metodos de consulta da classe Circuito
    // Para fazer um teste, vamos atribuir quantidades aleatorias
    switch (C.getPorta(i)->getTipo())
    {
    case 0:
        nomePorta = "NT";
        break;
    case 1:
        nomePorta = "AN";
        break;
    case 2:
        nomePorta = "NA";
        break;
    case 3:
        nomePorta = "OR";
        break;
    case 4:
        nomePorta = "NO";
        break;
    case 5:
        nomePorta = "XO";
        break;
    case 6:
        nomePorta = "NX";
        break;
    default:
        nomePorta = "??";
        break;
    }
    numInputsPorta = (nomePorta != "NT" ? C.getPorta(i)->getNumInputs() : 1);
    for (j=0; j<numInputsPorta; j++)
        idInputPorta[j] = C.getPorta(i)->getId_in(j);
    // Cria e define valores dos widgets da linha da tabela que corresponde aa porta

    // Coluna 0
    ui->tablePortas->setCellWidget(i,0,new QLabel(nomePorta));
    // Coluna 1
    prov = new QLabel;
    prov->setAlignment(Qt::AlignCenter);
    prov->setNum(numInputsPorta);
    ui->tablePortas->setCellWidget(i,1,prov);

    // As entradas de cada porta
    for (j=0; j<4; j++)
    {
        // Cria os widgets das celulas da tabela de portas
        // Coluna 2 em diante
        prov = new QLabel;
        prov->setAlignment(Qt::AlignCenter);
        if (j<numInputsPorta) prov->setNum(idInputPorta[j]);
        ui->tablePortas->setCellWidget(i,2+j,prov);
    }
}

// Exibe os dados da i-esima saida
// Essa funcao deve ser chamada sempre que mudar valores da saida
// A funcao redimensiona_tabela jah chama essa funcao para todas as saidas
void MainCircuito::exibe_saida(int i)
{
    if (i >= getNumSaidas()) return;

    int idOutput;
    QLabel *prov;

    // Esse valor (idOutput) deve ser lido a partir de metodos de consulta da classe Circuito
    idOutput = C.getId_out(i);
    // Cria o widget da celula da tabela de saidas
    // Coluna 0 (unica)
    prov = new QLabel;
    prov->setAlignment(Qt::AlignCenter);
    prov->setNum(idOutput);
    ui->tableSaidas->setCellWidget(i,0,prov);
}

void MainCircuito::on_actionSair_triggered()
{
    QCoreApplication::quit();
}

// Exibe a caixa de dialogo para fixar caracteristicas de um novo circuito
void MainCircuito::on_actionNovo_triggered()
{
    newCircuito.show();
}

// Abre uma caixa de dialogo para ler um arquivo
void MainCircuito::on_actionLer_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Arquivo de circuito"), QString(),
            tr("Circuitos (*.txt);;Todos (*.*)"));

    if (!fileName.isEmpty()) {
        C.ler(fileName.toStdString().c_str());
        // Feita a leitura, reexibe todas as tabelas
        redimensiona_tabelas();
    }
}

// Abre uma caixa de dialogo para salvar um arquivo
void MainCircuito::on_actionSalvar_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Arquivo de circuito"), QString(),
            tr("Circuitos (*.txt);;Todos (*.*)"));

    if (!fileName.isEmpty()) {
        if (!fileName.isEmpty()) {
            C.salvar(fileName.toStdString().c_str());
        }
    }
}

// Gera e exibe a tabela verdade para o circuito
// Chama a funcao simular da classe circuito
void MainCircuito::on_actionGerar_tabela_triggered()
{
    //
    // Gera todas as possibilidades de combinacao das entradas
    //

    int numInputs = getNumEntradas();
    int numOutputs = getNumSaidas();
    int numCombinacoesEntrada = (numInputs>0 ? round(pow(3,numInputs)) : 0);;
    QString texto;
    QLabel *prov;
    int i,j;

    std::vector<int> inputs(numInputs);  // -1=UNDEF; 0=FALSE; 1=TRUE
    std::vector<bool_3S> B3S_inputs(numInputs);
    std::vector<int> outputs(numOutputs);  // -1=UNDEF; 0=FALSE; 1=TRUE

    // Inicializa todas as entradas com UNDEF
    for (i=0; i<numInputs; i++) inputs[i] = -1;
    //
    // Gera todas as linhas da tabela verdade
    //
    for (i=0; i<numCombinacoesEntrada; i++)
    {
        //
        // Exibe a i-esima combinação de entrada: inputs[0] a inputs[numInputs-1]
        //
        //TIRAR ESSA GAMBIARRA
        for(int k = 0; k < numInputs; k++) B3S_inputs[k] = bool_3S(inputs[k]);//Gambiarra
        C.setInputs(B3S_inputs);
        C.simular();
        // Cria os QLabels correspondentes aas entradas inputs[j]
        for (j=0; j<numInputs; j++)
        {
            switch (inputs[j])
            {
            default:
            case -1:
                texto="X";
                break;
            case 0:
                texto="F";
                break;
            case 1:
                texto="T";
                break;
            }
            prov = new QLabel(texto);
            prov->setAlignment(Qt::AlignCenter);
            ui->tableTabelaVerdade->setCellWidget(i+1, j, prov);
        }

        // Determina qual entrada deve ser incrementada na proxima linha
        // Incrementa a ultima possivel que nao for TRUE
        // Se a ultima for TRUE, faz essa ser UNDEF e tenta incrementar a anterior
        j = numInputs-1;
        while (inputs[j]==1 && j>=0) // inputs[j]==TRUE && j>=0
        {
          inputs[j] = -1;  // UNDEF
          j--;
        };
        // Incrementa a input selecionada
        if (j>=0) inputs[j] += 1;

        //
        // Exibe a j-esima saida
        //

        // As saidas devem ser lidas/simuladas usando uma funcao da classe Circuito
        for (j=0; j<numOutputs; j++)
        {
            if(C.getId_out(j) > 0)
              outputs[j] = C.getPorta(C.getId_out(j) - 1)->getSaida();
            else
              outputs[j] = inputs[j];
        }

        // Cria os QLabels correspondentes aas saidas outputs[j]
        for (j=0; j<numOutputs; j++)
        {
            switch (outputs[j])
            {
            default:
            case -1:
                texto="X";
                break;
            case 0:
                texto="F";
                break;
            case 1:
                texto="T";
                break;
            }
            prov = new QLabel(texto);
            prov->setAlignment(Qt::AlignCenter);
            ui->tableTabelaVerdade->setCellWidget(i+1, j+numInputs, prov);
        }
    }
}

// Exibe a caixa de dialogo para fixar caracteristicas de uma porta
void MainCircuito::on_tablePortas_activated(const QModelIndex &index)
{
    int id_porta = index.row()+1;
    modificarPorta.setPorta(id_porta);
    modificarPorta.show();
}

// Exibe a caixa de dialogo para fixar caracteristicas de uma saida
void MainCircuito::on_tableSaidas_activated(const QModelIndex &index)
{
    int id_saida = index.row()+1;
    modificarSaida.setSaida(id_saida);
    modificarSaida.show();
}
