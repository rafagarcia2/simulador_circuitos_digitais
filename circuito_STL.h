#ifndef _CIRCUITO_H_
#define _CIRCUITO_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Criando um tipo de dados enumerado para representar um booleano com 3 estados:
// TRUE_3S, FALSE_3S e UNDEF_3S

enum bool_3S {
  FALSE_3S = 0,
  TRUE_3S = 1,
  UNDEF_3S = -1
};

#define NUM_MAX_INPUTS_PORTA 4

class Porta;
typedef Porta *ptr_Porta;

class Porta {
protected:
  unsigned Nin;
  int id_in[NUM_MAX_INPUTS_PORTA];
  bool_3S saida;
public:
  Porta(unsigned NI=2);
  Porta(const Porta&P);
  inline virtual ~Porta() {}

  virtual ptr_Porta clone() const = 0;
  inline unsigned getNumInputs() const {return Nin;}
  inline bool_3S getSaida() const {return saida;}
  inline void setSaida(bool_3S s) { saida = s; }
  int getId_in(unsigned i);
  void setId_in(unsigned i, int N);
  void setNin(unsigned NI) { Nin = NI; }
  virtual void digitar();
  virtual void ler(istream &I);
  virtual ostream &imprimir(ostream &O) const;

  virtual int getTipo() const = 0;
  virtual bool_3S simular(const bool_3S in[]) = 0;
  friend class Circuito;
};

istream &operator>>(istream &I,bool_3S &in);
//FUNCAO NOT
bool_3S operator~(const bool_3S A);
//FUNCAO AND
bool_3S operator&(const bool_3S A,const bool_3S B);
//FUNCAO OR
bool_3S operator|(const bool_3S A, const bool_3S B);

// Operador << com comportamento polimorfico
inline ostream &operator<<(ostream &O, const Porta &X) {return (&X)->imprimir(O);};

class Porta_NOT: public Porta {
public:
  inline Porta_NOT():Porta(1) {}
  inline ~Porta_NOT() {}
  ptr_Porta clone() const {return new Porta_NOT(*this);}

  inline int getTipo() const { return 0;}

  void digitar();
  void ler(istream &I);
  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_AND: public Porta {
public:
  inline Porta_AND(): Porta() {}
  inline ~Porta_AND() {}
  ptr_Porta clone() const {return new Porta_AND(*this);}

  inline int getTipo() const { return 1;}
  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_NAND: public Porta {
public:
  inline Porta_NAND(): Porta() {}
  inline ~Porta_NAND() {}
  ptr_Porta clone() const {return new Porta_NAND(*this);}

  inline int getTipo() const { return 2;}
  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_OR: public Porta {
public:
  inline Porta_OR(): Porta() {}
  inline ~Porta_OR() {}
  ptr_Porta clone() const {return new Porta_OR(*this);}

  inline int getTipo() const { return 3;}
  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_NOR: public Porta {
public:
  inline Porta_NOR(): Porta() {}
  inline ~Porta_NOR() {}
  ptr_Porta clone() const {return new Porta_NOR(*this);}

  inline int getTipo() const { return 4;}
  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_XOR: public Porta {
public:
  inline Porta_XOR(): Porta() {}
  inline ~Porta_XOR() {}
  ptr_Porta clone() const {return new Porta_XOR(*this);}

  inline int getTipo() const { return 5;}
  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_NXOR: public Porta {
public:
  inline Porta_NXOR(): Porta() {}
  inline ~Porta_NXOR() {}
  ptr_Porta clone() const {return new Porta_NXOR(*this);}

  inline int getTipo() const { return 6;}
  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Circuito {
private:
  unsigned Nin;      // Numero de entradas
  unsigned Nout;     // Numero de saidas
  unsigned Nportas;  // Numero de portas
  vector<bool_3S> inputs;   // vetor que deve ser alocado com dimensao "Nin"
  vector<int> id_out;      // vetor que deve ser alocado com dimensao "Nout"
  vector<ptr_Porta> portas; // vetor que deve ser alocado com dimensao "Nportas"
  void alocar(unsigned NI, unsigned NO, unsigned NP);// ATENCAO: fora de construtor, sempre chamar antes limpar()
  bool alocar(const string &tipo, bool enable = true, unsigned id = 0);
  void copiar(const Circuito &C);                     // ATENCAO: fora de construtor, sempre chamar antes limpar()
public:
  // As variaveis do tipo Circuito sao sempre criadas sem nenhum dado
  // A definicao do numero de entradas, saidas e portas eh feita ao ler do teclado ou arquivo
  inline Circuito():Nin(0),Nout(0),Nportas(0),inputs(),id_out(),portas() {}
  // Construtor por copia apenas chama a funcao copiar
  inline Circuito(const Circuito &C) {copiar(C);}
  void replace(unsigned id,string tipo,unsigned numIn,int idIn[]);

  inline unsigned getNin() const { return Nin; }
  inline unsigned getNout() const { return Nout; }
  inline unsigned getNportas() const { return Nportas; }
  inline int getId_out(unsigned i) const { return id_out[i]; }
  ptr_Porta getPorta(unsigned i) const { return portas[i]->clone(); }

  inline void setInputs(const vector<bool_3S> &in) { inputs = in;}

  void newCircuito(unsigned NI, unsigned NO, unsigned NP);
  // Limpa todo o conteudo do circuito
  void limpar();
  // Destrutor apenas chama a funcao limpar
  inline ~Circuito() {limpar();}
  // Operador de atribuicao apenas chama as funcoes copiar e limpar
  inline void operator=(const Circuito &C) {if (this!=&C) {limpar(); copiar(C);}}

  // Entrada dos dados de um circuito via teclado
  void digitar();
  bool arq_valido(const char* arq);
  // Entrada dos dados de um circuito via arquivo
  void ler(const char* arq);
  // Saida dos dados de um circuito (em tela ou arquivo, mesma funcao)
  ostream &imprimir(ostream &O=cout) const;
  // Salvar circuito em arquivo
  // Abre a stream e depois chama o metodo imprimir
  void salvar(const char* arq) const;

  // Calcula a saida das portas do circuito para os valores de entrada que estao em inputs[i]
  void simular();
  void port_map(bool_3S in[],const Porta &P);
  // Calcula a tabela verdade do circuito:
  void gerarTabela(void);
};
ostream &operator<<(ostream &O,const bool_3S &in);
inline ostream &operator<<(ostream &O, const Circuito &C) {return C.imprimir(O);}
extern Circuito C;
#endif // _CIRCUITO_H_
