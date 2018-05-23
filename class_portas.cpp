#include "circuito_STL.h"

//CLASSE PORTA
int Porta::getId_in(unsigned i)
{
  if( i < Nin )return id_in[i];
  else return 0;
}
void Porta::setId_in(unsigned i, int N)
{
  if( i < Nin ) id_in[i] = N;
}

Porta::Porta(unsigned NI)
{
  if(NI < 4) Nin = NI;
}

Porta::Porta(const Porta& P)
{
  Nin = P.Nin;
  saida = P.saida;
  for(unsigned i = 0; i < Nin; i++) id_in[i] = P.id_in[i];
}

void Porta::digitar()
{
  unsigned N_inputs;
  do{
    cout << "Numero de entradas (2 ha 4) ? ";
    cin >> N_inputs;
  }while(N_inputs < 2 || N_inputs > 4);
  Nin = N_inputs;

  for(unsigned i = 0; i < Nin; i++)
  {
    cout<<"id da entrada " <<i + 1<< "\? ";
    cin >> id_in[i];
  }
}

void Porta::ler(istream &I)
{
  unsigned N_inputs;

  I >> N_inputs;
  if( N_inputs < 2 || N_inputs > 4) return;
  Nin = N_inputs;
  I.ignore(1,':');
  for(unsigned i = 0 ; i < Nin ; i++)
    I >> id_in[i];
}

ostream &Porta::imprimir(ostream &O) const
{
  for(unsigned i = 0 ; i < Nin; i++) O <<' '<<id_in[i];
  return O;
}
//FUNCOES AUXILIARES

//FUNCAO NOT
bool_3S operator~(const bool_3S A)
{
  if( A == UNDEF_3S )
    return UNDEF_3S;
  return  (A == TRUE_3S)?FALSE_3S:TRUE_3S;
}
//FUNCAO AND
bool_3S operator&(const bool_3S A,const bool_3S B)
{
  if(A == UNDEF_3S && B == UNDEF_3S )return UNDEF_3S;
  if( (A == UNDEF_3S && B == TRUE_3S)||(A == TRUE_3S && B == UNDEF_3S))return UNDEF_3S;
  if(A == FALSE_3S || B == FALSE_3S )return FALSE_3S;
  return TRUE_3S;
}
//FUNCAO OR
bool_3S operator|(const bool_3S A, const bool_3S B)
{
  if(A == TRUE_3S || B == TRUE_3S) return TRUE_3S;
  if(A == FALSE_3S && B == FALSE_3S) return FALSE_3S;
  return UNDEF_3S;
}
//PORTA NOT
void Porta_NOT::digitar()
{
  cout<<"id da entrada \?";
  cin >> id_in[0];
}
void Porta_NOT::ler(istream &I)
{
  unsigned N_inputs;
  I >> N_inputs;
  if(N_inputs != 1) return;
  Nin = N_inputs;
  I.ignore(1,':');
  I >> id_in[0];
}
ostream& Porta_NOT::imprimir(ostream &O) const
{
  O << "NT " << Nin <<": "<< id_in[0];
  return O;
}

bool_3S Porta_NOT::simular(const bool_3S in[0])
{
  return ~in[0];
}
//PORTA AND
ostream &Porta_AND::imprimir(ostream &O) const
{
  O << "AN " << Nin <<':';
  Porta::imprimir(O);
  return O;
}

bool_3S Porta_AND::simular(const bool_3S in[])
{
  bool_3S output = in[0];
  for(unsigned i = 1 ; i < Nin; i++)output = output & in[i];
  return output;
}

// PORTA NAND
ostream &Porta_NAND::imprimir(ostream &O) const
{
  O << "NA " << Nin <<':';
  Porta::imprimir(O);
  return O;
}

bool_3S Porta_NAND::simular(const bool_3S in[])
{
  bool_3S output = in[0];
  for(unsigned i = 1 ; i < Nin; i++) output = output & in[i];
  return ~output;
}
//PORTA OR

ostream &Porta_OR::imprimir(ostream &O) const
{
  O << "OR " << Nin <<':';
  Porta::imprimir(O);
  return O;
}

bool_3S Porta_OR::simular(const bool_3S in[])
{
  bool_3S output = in[0];
  for(unsigned i = 1 ; i < Nin; i++) output = output | in[i];
  return output;
}

// PORTA NOR
ostream &Porta_NOR::imprimir(ostream &O) const
{
  O << "NO " << Nin <<':';
  Porta::imprimir(O);
  return O;
}

bool_3S Porta_NOR::simular(const bool_3S in[])
{
  bool_3S output = in[0];
  for(unsigned i = 1 ; i < Nin; i++) output = output | in[i];
  return ~output;
}
//PORTA XOR
ostream &Porta_XOR::imprimir(ostream &O) const
{
  O << "NO " << Nin <<':';
  Porta::imprimir(O);
  return O;
}

bool_3S Porta_XOR::simular(const bool_3S in[])
{
  bool_3S output = in[0];
  for(unsigned i = 1 ; i < Nin; i++) output = (~output)&in[i] | (~in[i])&output;
  return output;
}
//PORTA NXOR
ostream &Porta_NXOR::imprimir(ostream &O) const
{
  O << "NX " << Nin <<':';
  Porta::imprimir(O);
  return O;
}

bool_3S Porta_NXOR::simular(const bool_3S in[])
{
  bool_3S output = in[0];
  for(unsigned i = 1 ; i < Nin; i++) output = (~output)&in[i] | (~in[i])&output;
  return ~output;
}
