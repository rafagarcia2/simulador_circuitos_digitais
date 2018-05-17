#include <iostream>
#include <string>
#include "circuito.h"

using namespace std;

int main(void)
{
  Circuito C;
  string nome;
  int opcao;

  do {
    cout << "\nPROGRAMA SIMULADOR DE CIRCUITOS DIGITAIS:\n";
    do {
      cout << "0 - Sair\n";
      cout << "1 - Digitar um circuito via teclado\n";
      cout << "2 - Salvar um circuito em arquivo\n";
      cout << "3 - Ler um circuito de arquivo\n";
      cout << "4 - Imprimir o circuito na tela\n";
      cout << "5 - Simular o circuito para uma determinada entrada\n";
      cout << "6 - Simular o circuito para todas as entrada (gerar tabela verdade)\n";
      cout << "Qual sua opcao? ";
      cin >> opcao;
    } while(opcao<0 || opcao>6);
    switch(opcao){
    case 1:
      C.digitar();
      break;
    case 2:
    case 3:
      // Antes de ler a string com o nome do arquivo, esvaziar o buffer do teclado
      cin.ignore(256,'\n');
      do {
        cout << "Arquivo: ";
        getline(cin,nome);
      } while (nome.size() < 3); // Nome do arquivo >= 3 caracteres
      if (opcao==3) {
        C.ler(nome.c_str());
      }
      else {
        C.salvar(nome.c_str());
      }
      break;
    case 4:
      C.imprimir();
      break;
    case 5:
      C.digitarEntradas();
      C.simular();
      C.imprimirSaidas();
      break;
    case 6:
      C.gerarTabela();
      break;
    default:
      break;
    }
  } while(opcao != 0);
}

