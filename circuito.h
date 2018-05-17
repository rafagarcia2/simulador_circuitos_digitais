#ifndef _CIRCUITO_H_
#define _CIRCUITO_H_

#include <iostream>

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
  inline Porta(unsigned NI = 2): Nin(NI){saida = UNDEF_3S;}
  Porta(const Porta &P);
  inline virtual ~Porta() {}

  virtual ptr_Porta clone() const = 0;
  inline unsigned getNumInputs() const {return Nin;}
  inline bool_3S getSaida() const {return saida;}
  void setSaida(bool_3S s);
  int getId_in(unsigned i) const;
  void setId_in(unsigned i, int N);
  unsigned getIn() {return Nin;}

  virtual void digitar();
  virtual bool ler(istream &I);
  virtual ostream &imprimir(ostream &O) const =0 ;

  virtual bool_3S simular(const bool_3S in[]) = 0;
};

// Operador << com comportamento polimorfico
inline ostream &operator<<(ostream &O, const Porta &X) {return (&X)->imprimir(O);};

class Porta_NOT: public Porta {
public:
  inline Porta_NOT(): Porta(1) {}
  inline ~Porta_NOT() {}
  inline ptr_Porta clone() const {return new Porta_NOT(*this);}

  void digitar();
  bool ler(istream &I);
  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_AND: public Porta {
public:
  inline Porta_AND(): Porta() {}
  inline ~Porta_AND() {}
  inline ptr_Porta clone() const {return new Porta_AND(*this);}

  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_NAND: public Porta {
public:
  inline Porta_NAND(): Porta() {}
  inline ~Porta_NAND() {}
  ptr_Porta clone() const {return new Porta_NAND(*this);}

  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_OR: public Porta {
public:
  inline Porta_OR(): Porta() {}
  inline ~Porta_OR() {}
  ptr_Porta clone() const {return new Porta_OR(*this);}

  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_NOR: public Porta {
public:
  inline Porta_NOR(): Porta() {}
  inline ~Porta_NOR() {}
  ptr_Porta clone() const {return new Porta_NOR(*this);}

  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_XOR: public Porta {
public:
  inline Porta_XOR(): Porta() {}
  inline ~Porta_XOR() {}
  ptr_Porta clone() const {return new Porta_XOR(*this);}

  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_NXOR: public Porta {
public:
  inline Porta_NXOR(): Porta() {}
  inline ~Porta_NXOR() {}
  ptr_Porta clone() const {return new Porta_NXOR(*this);}

  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Circuito {
private:
  unsigned Nin;      // Numero de entradas
  unsigned Nout;     // Numero de saidas
  unsigned Nportas;  // Numero de portas
  bool_3S *inputs;   // array com dimensao "Nin"
  int *id_out;       // array com dimensao "Nout"
  ptr_Porta *portas; // array com dimensao "Nportas"
  void limpar();
  void alocar(unsigned NI, unsigned NO, unsigned NP);  // ATENCAO: fora de construtor, sempre chamar antes limpar()
  void copiar(const Circuito &C);                      // ATENCAO: fora de construtor, sempre chamar antes limpar()
  bool verificar(void) const;
  void calcularEntradas(unsigned I);      //calcular as entradas com o id I e salva em id_out
public:
  inline Circuito():Nin(0),Nout(0),Nportas(0),inputs(NULL),id_out(NULL),portas(NULL) {}
  inline Circuito(const Circuito &C) {copiar(C);}
  inline ~Circuito() {limpar();}
  inline void operator=(const Circuito &C) {if (this!=&C) {limpar(); copiar(C);}}

  void digitar();
  void ler(const char *);
  ostream &imprimir(ostream &O=cout) const;
  void salvar(const char *) const;
  void digitarEntradas();
  void imprimirEntradas(void) const;
  void imprimirSaidas(void) const;

  void simular();                             //grande loaco
  void gerarTabela(void);
};

inline ostream &operator<<(ostream &O, const Circuito &C) {return C.imprimir(O);}

#endif // _CIRCUITO_H_

