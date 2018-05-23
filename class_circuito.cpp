#include <string>
#include <algorithm>
#include <fstream>
#include "circuito_STL.h"

/**
 * unsigned Nin;
 * unsigned Nout;
 * unsigned Nportas;
 * vector<bool_3S> inputs;
 * vector<int> id_out;
 * vector<ptr_Porta> portas;
 */

void Circuito::alocar(unsigned NI, unsigned NO, unsigned NP)
{
    Nin = NI;
    Nout = NO;
    Nportas  = NP;
    inputs.resize(NI);
    id_out.resize(NO);
    portas.resize(NP);
}

void Circuito::copiar(const Circuito &C)//falta conferir
{
  Nin     = C.Nin;
  Nout    = C.Nout;
  Nportas = C.Nportas;
  inputs  = C.inputs;
  id_out  = C.id_out;
  for(unsigned i = 0 ; i < Nportas; i++) portas[i] = C.portas[i]->clone();
}

void Circuito::limpar()
{
  inputs.erase(inputs.begin(),inputs.begin() + inputs.size());
  id_out.erase(id_out.begin(),id_out.begin() + id_out.size());
  for(unsigned i = 0; i < Nportas; i++) delete portas[i];
  portas.erase(portas.begin(),portas.begin() + portas.size());

  Nin = 0;
  Nout = 0;
  Nportas = 0;
}

bool Circuito::alocar(const string &tipo,bool enable,unsigned id)
{
  if(tipo == "NT")
  {
    if(enable)portas[id] = (new Porta_NOT);
  }
  else if(tipo == "AN")
  {
    if(enable)portas[id] = (new Porta_AND);
  }
  else if(tipo == "NA")
  {
    if(enable)portas[id] = (new Porta_NAND);
  }
  else if(tipo == "OR")
  {
    if(enable)portas[id] = (new Porta_OR);
  }
  else if(tipo == "NO")
  {
    if(enable)portas[id] = (new Porta_NOR);
  }
  else if(tipo == "XO")
  {
    if(enable)portas[id] = (new Porta_XOR);
  }
  else if(tipo == "NX")
  {
    if(enable)portas[id] = (new Porta_NXOR);
  }
  else
    return false;
  return true;
}

void Circuito::ler(const char* arq)
{
  ifstream read(arq);
  string key_word;
  int aux;

  if(!arq_valido(arq)) return;
  limpar();

  getline(read,key_word,':');
  read >> Nin;
  read >> Nout;
  read >> Nportas;
  alocar(Nin,Nout,Nportas);
  for(unsigned i = 0; i < Nportas; i++)
  {
    read.ignore(256,' ');
    getline(read,key_word,' ');
    alocar(key_word,true,i);
    portas[i]->ler(read);
  }

  for(unsigned i = 0 ; i < Nout; i++)
  {
    read.ignore(256,' ');
    read >> aux;
    id_out[i] = aux;
  }
  read.close();
}

bool Circuito::arq_valido(const char* arq)
{
  ifstream read(arq);
  string key_word;
  unsigned prov_Nin,prov_Nout,prov_Nportas;
  unsigned prov_num_int,index;
  int id_prov;


  if(!read.is_open())return false;
  getline(read,key_word,':');
  if(key_word != "CIRCUITO")return false;
  read >> prov_Nin;
  read >> prov_Nout;
  read >> prov_Nportas;
  if(prov_Nin == 0 || prov_Nout == 0 || prov_Nportas == 0)return false;

  read.ignore(1,'\n');
  getline(read,key_word,':');

  if(key_word != "PORTAS")return false;
  //For para verificar todas as portas
  for(unsigned i =0 ; i < prov_Nportas; i++)
  {
    read >> index;//index da porta
    //encerra se as portas nao estiverem na ordem
    if(index != i+1)return false;

    read.ignore(1,' ');
    getline(read,key_word,' ');//deve ter armazenado o tipo da porta
    if(!alocar(key_word,false,i))return false;//testa se a porta existe

    read >> prov_num_int;// salva o numero de entradas da porta

    if(key_word == "NT" && prov_num_int != 1)return false;
    if(prov_num_int > 4)return false; //Testa a quantidade de entradas da porta
    read.ignore(1,':');

    for(unsigned k = 0 ; k < prov_num_int; k++)
    {
      read >> id_prov;

      if(id_prov > 0 && id_prov > prov_Nportas)return false;
      if(id_prov < 0 && (-1*id_prov) > prov_Nin)return false;
      if(id_prov == 0)return false;
    }
  }
  read.ignore(1,'\n');
  getline(read,key_word,':');
  if(key_word != "SAIDAS")return false;
  for(unsigned i = 0; i < prov_Nout; i++)
  {
    read >> index;
    if(index != i+1)return false;

    read.ignore(256,' ');
    read >> id_prov;

    if(id_prov > 0 && (id_prov > prov_Nportas || id_prov == 0))return false;
    if((id_prov < 0) && (-id_prov > prov_Nin))return false;
  }
  read.close();
  return true;
}
ostream &Circuito::imprimir(ostream &O)const
{
  O << "CIRCUITO: "<< Nin << ' ' << Nout << ' ' << Nportas << '\n';
  O << "PORTAS:";
  for(unsigned i = 0; i < Nportas; i++)
  {
    O << '\n';
    O << i+1 << ')' <<' ';
    portas[i]->imprimir(O);
  }
  O << '\n';
  O << "SAIDAS:";
  for(unsigned i = 0; i < Nout; i++)
  {
    O << '\n';
    O << i+1 << ')' <<' ';
    O << id_out[i];
  }
  return O;
}
void Circuito::salvar(const char* arq) const
{
  ofstream write(arq);
  write << (*this);
  write.close();
}
istream &operator>>(istream &I,bool_3S &in)
{
  char entrada;
  I >> entrada;
  entrada = toupper(entrada);
  switch(entrada){
  case 'T':
    in = TRUE_3S;
    break;
  case 'F':
    in = FALSE_3S;
    break;
  case 'X':
    in = UNDEF_3S;
    break;
  default:
    break;
  }
  return I;
}
ostream &operator<<(ostream &O,const bool_3S &in)
{
  switch(in){
  case TRUE_3S:
    O << 'T';
    break;
  case FALSE_3S:
    O << 'F';
    break;
  case UNDEF_3S:
    O << 'X';
    break;
  default:
    O <<' ';
    break;
  }
  return O;
}

void Circuito::port_map(bool_3S in[],const Porta &P)
{
  int index;
  for(unsigned i = 0; i < P.getNumInputs(); i++)
  {
    index = P.id_in[i];
    if(index < 0) // id de uma entrada do circuito
      in[i] = inputs[-index -1];
    else
      in[i] = portas[index-1]->getSaida();
  }
}


void Circuito::simular()
{
  bool_3S in[NUM_MAX_INPUTS_PORTA];
  bool tudo_def,algum_def;

  for(unsigned i = 0; i < Nportas ; i++)portas[i]->setSaida(UNDEF_3S);

  do
  {
    tudo_def = true;
    algum_def = false;
    for(unsigned i = 0 ; i < Nportas; i++)
    {
      if( portas[i]->getSaida() == UNDEF_3S)
      {
        port_map(in,*portas[i]);
        portas[i]->setSaida(portas[i]->simular(in));
        if(portas[i]->getSaida() == UNDEF_3S)
          tudo_def = false;
        else
          algum_def = true;
      }
    }
  }while(!tudo_def && algum_def);
}

void Circuito::gerarTabela(void)
{
  int k = Nin;
  inputs.erase(inputs.begin(), inputs.begin() + inputs.size());
  for(unsigned i = 0; i < Nin; i++)inputs.push_back(FALSE_3S);

  do
  {
    simular();
    //imprimirEntradas();
    //cout << ' ';
   // imprimirSaidas();
    //cout << endl;
    k = Nin - 1;
    while( k >= 0 && inputs[k] == UNDEF_3S)
    {
      inputs[k] = FALSE_3S;
      k--;
    }
    if(k >= 0)
    {
      if(inputs[k] == FALSE_3S)inputs[k] = TRUE_3S;
      else inputs[k] = UNDEF_3S;
    }

  }while(k >= 0 );
}

void Circuito::replace(unsigned id,string tipo,unsigned numIn,int idIn[])
{
    if(id >=  Nportas) return;
    delete C.portas[id];
    C.alocar(tipo,true,id);
    C.portas[id]->setNin(numIn);
    for(int i = 0; i < NUM_MAX_INPUTS_PORTA; i++)
        C.portas[id]->setId_in(i,idIn[i]);
}

void Circuito::newCircuito(unsigned NI, unsigned NO, unsigned NP)
{
    limpar();
    alocar(NI,NO,NP);
}
