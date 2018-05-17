#include <iostream>
#include <fstream>
#include <math.h>
#include "circuito.h"

using namespace std;

Porta::Porta(const Porta &P)
{
    Nin = P.Nin;
    for (unsigned i =0; i<Nin; i++){
        id_in[i] = P.id_in[i];
    }
    saida = P.saida;
}
void Porta::setSaida(bool_3S s)
{
    switch (s)
    {
    case TRUE_3S:
        saida = TRUE_3S;
        break;
    case FALSE_3S:
        saida = FALSE_3S;
    default:
        saida = UNDEF_3S;
    }
}
int Porta::getId_in(unsigned i) const
{
    return id_in[i];
}
void Porta::setId_in(unsigned i, int N)
{
    id_in[i] = N;
}
void Porta::digitar()
{
    int t;
    unsigned cont=0;
    cout << "Digite a quantidade de  entradas: ";
    cin >> Nin;
    if(Nin > 1 &&  Nin < 4){
        for (unsigned i =0; i<Nin; i++){
            cout << "digite o id da entrada " << i +1 << ": ";
            cin >> t;
            if(t >= -4 && t != 0 && t <= 7){
                id_in[i] = t;
                cont++;
            }
            else{
                cerr << "id invalido.";
                break;
            }
        }
        if(cont != Nin) cerr << "Numero inputs porta incompativel.";
    }else{
        cerr << "Entradas inpossiveis na porta";
    }
    saida = UNDEF_3S;
}
bool Porta::ler(istream &I)
{
    I >> Nin;
    //cout << Nin;
    I.ignore(255,' ');
    for (unsigned i =0; i<Nin; i++){
                I >> this ->id_in[i];
        }
    saida = UNDEF_3S;
    return true;
    /*if(Nin > 1 &&  Nin < 4){
        for (int i =0; i<Nin; i++){
                I >> this ->id_in[i];
        }
        return true;
    }else{
        cerr << "Entradas inpossiveis na porta";
        return false;
    }*/
}
ostream &Porta::imprimir(ostream &O) const
{
    if(Nin > 0 &&  Nin < 4){
        for (unsigned i =0; i<Nin; i++){          //ajustar a funcao !!!
            O << id_in[i] << " ";
        }
    }
    return O;
}
void Porta_NOT::digitar()
{
    int t;
    Nin = 1;
    cout << "Digite o id da entrada: ";
    cin >> t;
    if(t > -5 && t <= 7){
        id_in[0] = t;
    }else{
        cerr << "id invalido";
        return;
    }
    saida = UNDEF_3S;
}
bool Porta_NOT::ler(istream &I)
{
    unsigned t;
    I >> t;
    /*if(t!=1){
        cerr << "entradas em ecesso.";
        return false;
    }*/
    I.ignore(255,' ');
    I >> this -> id_in[0];
    Nin = t;
    saida = UNDEF_3S;
    return true;
}
ostream &Porta_NOT::imprimir(ostream &O) const
{
    O << ") NT " << Nin << ": ";
    if(Nin == 1){
        O << id_in[0] << " ";
    }
    return O;
}
bool_3S Porta_NOT::simular(const bool_3S in[])
{
    if(in[0] == TRUE_3S){
        saida = FALSE_3S;
        return saida;
    }else if(in[0] == FALSE_3S){
        saida = TRUE_3S;
        return saida;
    }else{
        saida = UNDEF_3S;
        return saida;
    }
}

ostream &Porta_AND::imprimir(ostream &O) const
{
    O << ") AN " << Nin << ": ";
    for(unsigned i = 0; i<Nin; i++){
        O << id_in[i] << " ";
    }
    return O;
}
bool_3S Porta_AND::simular(const bool_3S in[])
{
    switch (Nin)
    {
        case 2:
            if(in[0] == FALSE_3S || in[1] == FALSE_3S){
                saida = FALSE_3S;
                return saida;
            }else if(in[0] == UNDEF_3S || in[1] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else{
                saida = TRUE_3S;
                return saida;
            }
            break;
        case 3:
            if(in[0] == FALSE_3S || in[1] == FALSE_3S || in[2] == FALSE_3S){
                saida = FALSE_3S;
                return saida;
            }else if(in[0] == UNDEF_3S || in[1] == UNDEF_3S || in[2] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else{
                saida = TRUE_3S;
                return saida;
            }
            break;
        case 4:
            if(in[0] == FALSE_3S || in[1] == FALSE_3S || in[2] == FALSE_3S || in[3] == FALSE_3S){
                saida = FALSE_3S;
                return saida;
            }else if(in[0] == UNDEF_3S || in[1] == UNDEF_3S || in[2] == UNDEF_3S || in[3] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else{
                saida = TRUE_3S;
                return saida;
            }
            break;
        default:
            cerr << "Numero de entradas invalido.";
            return UNDEF_3S;
    }
}
ostream &Porta_NAND::imprimir(ostream &O) const
{
    O << ") NA " << Nin << ": ";
    for(unsigned i = 0; i<Nin; i++){
        O << id_in[i] << " ";
    }
    return O;
}
bool_3S Porta_NAND::simular(const bool_3S in[])
{
    switch (Nin)
    {
        case 2:
            if(in[0] == FALSE_3S || in[1] == FALSE_3S){
                saida = TRUE_3S;
                return saida;
            }else if(in[0] == UNDEF_3S || in[1] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else{
                saida = FALSE_3S;
                return saida;
            }
            break;
        case 3:
            if(in[0] == FALSE_3S || in[1] == FALSE_3S || in[2] == FALSE_3S){
                saida = TRUE_3S;
                return saida;
            }else if(in[0] == UNDEF_3S || in[1] == UNDEF_3S || in[2] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else{
                saida = FALSE_3S;
                return saida;
            }
            break;
        case 4:
            if(in[0] == FALSE_3S || in[1] == FALSE_3S || in[2] == FALSE_3S || in[3] == FALSE_3S){
                saida = TRUE_3S;
                return saida;
            }else if(in[0] == UNDEF_3S || in[1] == UNDEF_3S || in[2] == UNDEF_3S || in[3] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else{
                saida = FALSE_3S;
                return saida;
            }
            break;
        default:
            cerr << "Numero de entradas invalido.";
            return UNDEF_3S;
    }
}

ostream &Porta_OR::imprimir(ostream &O) const
{
    O << ") OR " << Nin << ": ";
    for(unsigned i = 0; i<Nin; i++){
        O << id_in[i] << " ";
    }
    return O;
}

bool_3S Porta_OR::simular(const bool_3S in[])
{
    switch (Nin)
    {
        case 2:
            if(in[0] == TRUE_3S || in[1] == TRUE_3S){
                saida = TRUE_3S;
                return saida;
            }else if(in[0] == UNDEF_3S || in[1] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else{
                saida = FALSE_3S;
                return saida;
            }
            break;
        case 3:
            if(in[0] == TRUE_3S || in[1] == TRUE_3S || in[2] == TRUE_3S){
                saida = TRUE_3S;
                return saida;
            }else if(in[0] == UNDEF_3S || in[1] == UNDEF_3S || in[2] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else{
                saida = FALSE_3S;
                return saida;
            }
            break;
        case 4:
            if(in[0] == TRUE_3S || in[1] == TRUE_3S || in[2] == TRUE_3S || in[3] == TRUE_3S){
                saida = TRUE_3S;
                return saida;
            }else if(in[0] == UNDEF_3S || in[1] == UNDEF_3S || in[2] == UNDEF_3S || in[3] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else{
                saida = FALSE_3S;
                return saida;
            }
            break;
        default:
            cerr << "Numero de entradas invalido.";
            return UNDEF_3S;
    }
}

ostream &Porta_NOR::imprimir(ostream &O) const
{
    O << ") NO " << Nin << ": ";
    for(unsigned i = 0; i<Nin; i++){
        O << id_in[i] << " ";
    }
    return O;
}

bool_3S Porta_NOR::simular(const bool_3S in[])
{
    switch (Nin)
    {
        case 2:
            if(in[0] == TRUE_3S || in[1] == TRUE_3S){
                saida = FALSE_3S;
                return saida;
            }else if(in[0] == UNDEF_3S || in[1] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else{
                saida = TRUE_3S;
                return saida;
            }
            break;
        case 3:
            if(in[0] == TRUE_3S || in[1] == TRUE_3S || in[2] == TRUE_3S){
                saida = FALSE_3S;
                return saida;
            }else if(in[0] == UNDEF_3S || in[1] == UNDEF_3S || in[2] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else{
                saida = TRUE_3S;
                return saida;
            }
            break;
        case 4:
            if(in[0] == TRUE_3S || in[1] == TRUE_3S || in[2] == TRUE_3S || in[3] == TRUE_3S){
                saida = FALSE_3S;
                return saida;
            }else if(in[0] == UNDEF_3S || in[1] == UNDEF_3S || in[2] == UNDEF_3S || in[3] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else{
                saida = TRUE_3S;
                return saida;
            }
            break;
        default:
            cerr << "Numero de entradas invalido.";
            return UNDEF_3S;
    }
}

ostream &Porta_XOR::imprimir(ostream &O) const
{
    O << ") XO " << Nin << ": ";
    for(unsigned i = 0; i<Nin; i++){
        O << id_in[i] << " ";
    }
    return O;
}

bool_3S Porta_XOR::simular(const bool_3S in[])
{
    switch (Nin)
    {
        case 2:
            if(in[0] == UNDEF_3S || in[1] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else if(in[0] == TRUE_3S && in[1] == TRUE_3S){
                saida = FALSE_3S;
                return saida;
            }else if(in[0] == FALSE_3S && in[1] == FALSE_3S){
                saida = FALSE_3S;
                return saida;
            }else{
                saida = TRUE_3S;
                return saida;
            }
            break;
        case 3:
            if(in[0] == UNDEF_3S || in[1] == UNDEF_3S || in[2] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else if(in[0] == TRUE_3S && in[1] == TRUE_3S && in[2] == TRUE_3S){
                saida = FALSE_3S;
                return saida;
            }else if(in[0] == FALSE_3S && in[1] == FALSE_3S && in[2] == FALSE_3S){
                saida = FALSE_3S;
                return saida;
            }else{
                saida = TRUE_3S;
                return saida;
            }
            break;
        case 4:
            if(in[0] == UNDEF_3S || in[1] == UNDEF_3S || in[2] == UNDEF_3S || in[3] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else if(in[0] == TRUE_3S && in[1] == TRUE_3S && in[2] == TRUE_3S && in[3] == TRUE_3S){
                saida = FALSE_3S;
                return saida;
            }else if(in[0] == FALSE_3S && in[1] == FALSE_3S && in[2] == FALSE_3S && in[3] == FALSE_3S){
                saida = FALSE_3S;
                return saida;
            }else{
                saida = TRUE_3S;
                return saida;
            }
            break;
        default:
            cerr << "Numero de entradas invalido.";
            return UNDEF_3S;
    }
}

ostream &Porta_NXOR::imprimir(ostream &O) const
{
    O << ") NX " << Nin << ": ";
    for(unsigned i = 0; i<Nin; i++){
        O << id_in[i] << " ";
    }
    return O;
}

bool_3S Porta_NXOR::simular(const bool_3S in[])
{
    switch (Nin)
    {
        case 2:
            if(in[0] == UNDEF_3S || in[1] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else if(in[0] == TRUE_3S && in[1] == TRUE_3S){
                saida = TRUE_3S;
                return saida;
            }else if(in[0] == FALSE_3S && in[1] == FALSE_3S){
                saida = TRUE_3S;
                return saida;
            }else{
                saida = FALSE_3S;
                return saida;
            }
            break;
        case 3:
            if(in[0] == UNDEF_3S || in[1] == UNDEF_3S || in[2] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else if(in[0] == TRUE_3S && in[1] == TRUE_3S && in[2] == TRUE_3S){
                saida = TRUE_3S;
                return saida;
            }else if(in[0] == FALSE_3S && in[1] == FALSE_3S && in[2] == FALSE_3S){
                saida = TRUE_3S;
                return saida;
            }else{
                saida = FALSE_3S;
                return saida;
            }
            break;
        case 4:
            if(in[0] == UNDEF_3S || in[1] == UNDEF_3S || in[2] == UNDEF_3S || in[3] == UNDEF_3S){
                saida = UNDEF_3S;
                return saida;
            }else if(in[0] == TRUE_3S && in[1] == TRUE_3S && in[2] == TRUE_3S && in[3] == TRUE_3S){
                saida = TRUE_3S;
                return saida;
            }else if(in[0] == FALSE_3S && in[1] == FALSE_3S && in[2] == FALSE_3S && in[3] == FALSE_3S){
                saida = TRUE_3S;
                return TRUE_3S;
            }else{
                saida = FALSE_3S;
                return saida;
            }
            break;
        default:
            cerr << "Numero de entradas invalido.";
            return UNDEF_3S;
    }
}
void Circuito::limpar()
{
    for(unsigned i =0; i<Nportas; i++){
        delete portas[i];
    }
    delete[] inputs;
    delete[] id_out;
    delete[] portas;
    Nin = Nout = Nportas = 0;
    inputs = NULL;
    id_out = NULL;
    portas = NULL;
}
void Circuito::alocar(unsigned NI, unsigned NO, unsigned NP)
{
    inputs = new bool_3S [NI];
    Nin = NI;
    id_out = new int [NO];
    Nout = NO;
    portas = new ptr_Porta [NP];
    Nportas = NP;
}
void Circuito::copiar(const Circuito &C)
{
    alocar(Nin,Nout,Nportas);
    for(unsigned i = 0; i<Nin; i++) inputs[i] = C.inputs[i];
    for(unsigned i = 0; i<Nout; i++) id_out[i] = C.id_out[i];
    for(unsigned i = 0; i<Nportas; i++) portas[i] = C.portas[i]->clone();
}
void Circuito::calcularEntradas(unsigned I)
{
    int vetorBase3[Nin];
    int contador(Nin - 1);
    for(int i = 0; i<Nin; i++) vetorBase3[i] = 0;
    while(I>0){
        vetorBase3[contador] = I%3;
        I = I/3;
        contador--;
    }

    for(int i = 0; i<Nin; i++){
        switch (vetorBase3[i])
        {
        case  2:
            inputs[i] = UNDEF_3S;
            break;
        case 0:
            inputs[i] = FALSE_3S;
            break;
        case 1:
            inputs[i] = TRUE_3S;
            break;
        default:
            ;
        }
    }
}
void Circuito::digitar()
{
    int t,NI,NO,NP;
    string nomePorta;
    cout << "digite a quantidade de entradas: ";
    cin >> NI;
    if(NI > 4){
        cerr << "Nin > 4" << endl;
        return;
    }
    cout << "digite a quantidade de saidas: ";
    cin >> NO;
    cout << "digite a quantidade de portas: ";
    cin >> NP;
    if(NO <= 0 || NO > (NI + NP)){
        cerr << "circuito sem saida ou com saida impossivel." << endl;
        return;
    }
    if(NP <= 0){
        cerr << "Nportas = 0" << endl;
        return;
    }
    limpar();
    alocar(NI, NO, NP);
    unsigned flag=1, i=0;
        Porta_NOT NT;
        Porta_AND AN;
        Porta_NAND NA;
        Porta_OR OR;
        Porta_NOR NOR;
        Porta_XOR XO;
        Porta_NXOR NX;
        do
        {
            cout << "digite o tipo da porta " << flag << ": ";
            cin >> nomePorta;
            if(nomePorta == "NT") portas[i] = (&NT) -> clone();
            else if(nomePorta == "AN") portas[i] = (&AN) -> clone();
            else if(nomePorta == "NA") portas[i] = (&NA) -> clone();
            else if(nomePorta == "OR") portas[i] = (&OR) -> clone();
            else if(nomePorta == "NO") portas[i] = (&NOR) -> clone();
            else if(nomePorta == "XO") portas[i] = (&XO) -> clone();
            else if(nomePorta == "NX") portas[i] = (&NX) -> clone();
            else{
                cerr << "Tipo de porta inesistente.";
                limpar();
                return;
            }
            portas[i] -> digitar();
            flag++;
            i++;
        }while(flag <= Nportas);
        flag = 1;
        for(unsigned i=0; i<Nout; i++)
        {
            cout << "digite o id da porta ou entrada de onde vem a saida " << i+1 << endl;
            cin >> t;
            if(t <= Nportas && t != 0){
            int N(Nin);
            if(t > -N)id_out[i] = t;
            else{
                cerr << "id invalido.";
                return;
            }
        }else{
            cerr << "id invalido.";
            return;
        }
    }
    if(!verificar()){
        limpar();
    }
}
void Circuito::ler(const char *file_name)
{
    ifstream myFile(file_name);
    if(myFile.is_open())
    {
        string word_circuito, word_PORTAS, word_SAIDA, nomePorta;
        unsigned N_in, N_out, N_portas;
        getline(myFile, word_circuito, ':');
        if(word_circuito != "CIRCUITO")
        {
            cerr<<"Arquivo faltando 'CIRCUITO:' .\n";
            limpar();
            return;
        }
        //myFile.ignore(255,' ');
        myFile >> N_in;
        myFile >> N_out;
        myFile >> N_portas;
        limpar();
        alocar(N_in, N_out, N_portas);
        myFile.ignore(255,'\n');
        myFile >> word_PORTAS;
        if(word_PORTAS != "PORTAS:")
        {
            cerr<<"Arquivo faltando 'PORTAS:' .\n";
            limpar();
            return;
        }
        myFile.ignore(255, '\n');
        unsigned flag=1, i=0, id_porta_prov;
        Porta_NOT NT;
        Porta_AND AN;
        Porta_NAND NA;
        Porta_OR OR;
        Porta_NOR NO;
        Porta_XOR XO;
        Porta_NXOR NX;
        do
        {
            myFile >> id_porta_prov;
            if(id_porta_prov != flag)
            {
                cerr<<"ids fora de ordem.\n";
                limpar();
                return;
            }
            myFile.ignore(255, ' ');
            myFile >> nomePorta;
            if(nomePorta == "NT") portas[i] = (&NT) -> clone();
            else if(nomePorta == "AN") portas[i] = (&AN) -> clone();
            else if(nomePorta == "NA") portas[i] = (&NA) -> clone();
            else if(nomePorta == "OR") portas[i] = (&OR) -> clone();
            else if(nomePorta == "NO") portas[i] = (&NO) -> clone();
            else if(nomePorta == "XO") portas[i] = (&XO) -> clone();
            else if(nomePorta == "NX") portas[i] = (&NX) -> clone();
            else{
                cerr << "Tipo de porta inesistente.";
                limpar();
                return;
            }
            portas[i] -> ler(myFile);
            flag++;
            i++;
        }while(flag <= Nportas);
        //pegar as saidas
        myFile >> word_SAIDA;
        if(word_SAIDA != "SAIDAS:")
        {
            cerr<<"Arquivo faltando 'SAIDAS:' .\n";
            limpar();
            return;
        }
        myFile.ignore(255, '\n');
        flag = 1;
        unsigned id_saida;
        for(unsigned i=0; i<Nout; i++)
        {
            myFile >> id_saida;
            if(id_saida == flag)
            {
                myFile.ignore(255, ' ');
                myFile >> id_out[i];
                /*if(id_out[i] == 0){
                    cerr << "id == 0;";
                    limpar();
                    return;
                }
                if(id_out[i] > Nportas){
                    cerr << "id > Nportas;";
                    limpar();
                    return;
                }*/
                flag++;
            }
            else
            {
                cerr<<"Saidas fora de ordem.\n";
                limpar();
                return;
            }
        }
    }else{
        cerr << "arquivo inesistente.";
        limpar();
        return;
    }
    if(!verificar()){
        limpar();
    }
}
ostream &Circuito::imprimir(ostream &O) const
{
    O << "CIRCUITO:";
    O << Nin << " " << Nout << " " << Nportas << endl;
    O << "PORTAS:" << endl;
    for(unsigned i = 0; i<Nportas; i++){
        O << i+1;
        portas[i]->imprimir(O);
        O << endl;
    }
    O << "SAIDAS:" << endl;
    for(unsigned i = 0; i<Nout; i++){
        O << i+1 << ") " << id_out[i] << endl;
    }
    return O;
}
void Circuito::salvar(const char *A) const
{
    if(A == 0){
        cerr << "Nenhum nome de arquivo foi digitado.";
    }else{
    ofstream my_arq(A);
    imprimir(my_arq);
    }
}
void Circuito::digitarEntradas() //atecncao semore ter certezada da memoria de saida esta alocada
{
    char t;
    int i(0), in(Nin);
    cout << " Para entrada verdadeira    T \n Para entrada falsa         F \n Para entrada indefinida    X \n";
    while(i<in){
        cout << "digite a entrada " << -(i+1) << ": ";
        cin >> t;
        switch (t)
        {
        case 'X':
            inputs[i] = UNDEF_3S;
            i++;
            break;
        case 'F':
            inputs[i] = FALSE_3S;
            i++;
            break;
        case 'T':
            inputs[i] = TRUE_3S;
            i++;
            break;
        default:
            cerr << "entrada inaceitavel.";
        }
    }
}
void Circuito::imprimirEntradas(void) const
{
    cout << "ENTRADAS: ";
    for(unsigned i = 0; i<Nin; i++){
        switch (inputs[i])
        {
        case FALSE_3S:
            cout << "F" << " ";
            break;
        case TRUE_3S:
            cout << "T" << " ";
            break;
        default:
            cout << "X" << " ";
        }
    }
}
void Circuito::imprimirSaidas(void) const
{
    cout << "SAIDAS: ";
    for(unsigned i = 0; i<Nout; i++){
        if(id_out[i] > 0){
            switch (portas[id_out[i]-1]->getSaida())
            {
            case FALSE_3S:
                cout << "F"  << " ";
                break;
            case TRUE_3S:
                cout << "T" << " ";
                break;
            default:
                cout << "X" << " ";
            }
        }else {
            switch (id_out[i])
            {
            case -4:
                switch(inputs[3])
                {
                case FALSE_3S:
                    cout << "F" << " ";
                    break;
                case TRUE_3S:
                    cout << "T" << " ";
                    break;
                default:
                    cout << "X" << " ";
                }
                break;
            case -3:
                switch(inputs[2])
                {
                case FALSE_3S:
                    cout << "F" << " ";
                    break;
                case TRUE_3S:
                    cout << "T" << " ";
                    break;
                default:
                    cout << "X" << " ";
                }
                break;
            case -2:
                switch(inputs[1])
                {
                case FALSE_3S:
                    cout << "F" << " ";
                    break;
                case TRUE_3S:
                    cout << "T" << " ";
                    break;
                default:
                    cout << "X" << " ";
                }
                break;
            case -1:
                switch(inputs[0])
                {
                case FALSE_3S:
                    cout << "F" << " ";
                    break;
                case TRUE_3S:
                    cout << "T" << " ";
                    break;
                default:
                    cout << "X" << " ";
                }
                break;
            default:
                cout << "id = 0";
            }
        }
    }
    for(int i =0; i<Nportas; i++){
        portas[i]->setSaida(UNDEF_3S);
    }
}
void Circuito::simular()
{
    unsigned stop=0;
    do
    {
        for(unsigned i=0; i<Nportas; i++)
        {
            const unsigned n = portas[i]->getNumInputs();    //n = número de entradas da porta a ser simulada
            bool_3S prov[n];//vetor de entrada da porta a ser simulada
            for(unsigned j=0; j<n; j++)
            {
                int id_input = portas[i]->getId_in(j);
                if(id_input < 0)
                {
                    prov[j] = inputs[(id_input*-1)-1];
                }
                else
                {
                    prov[j] = portas[id_input-1]->getSaida();
                }
            }
            portas[i]->simular(prov);
        }
    stop++;
    }while(stop<10);
}
bool Circuito::verificar(void) const
{
    if(Nin > 4){
        cerr << "quantidade de entrada maior que 4";
        return false;
    }
    if(Nin == 0){
        cerr << "Nin == 0";
        return false;
    }
    if(Nout == 0){
        cerr << "Nout == 0";
        return false;
    }
    if(Nout > (Nportas + Nin)){
        cerr << "quantidade de saida maior que maior que o numero de entradas e saida somados";
        return false;
    }
    if(Nportas == 0){
        cerr << "o circuito tem quantidade de portas nula";
        return false;
    }

    unsigned contOut(0);
    int entradas(Nin), saidas(Nout), port(Nportas);

    for(unsigned cont = 0; cont <(Nin + Nportas); cont++){

        if (cont < Nportas){

            for(unsigned i = 0; i < portas[cont]->getIn(); i++){
                if(portas[cont]->getId_in(i) == 0){
                    cerr << "id_in == 0";
                    return false;
                }
                if(portas[cont]->getId_in(i) < -entradas ){
                    cerr << "id_in < -Nin";
                    return false;
                }
                if(portas[cont]->getId_in(i) > port)
                {
                    cerr << "id_in > numero de portas";
                    return false;
                }
            }
        }
        if(cont < Nout){
                if(id_out[contOut] == 0){
                    cerr << "id_out == 0";
                    return false;
                }
                if(id_out[contOut] < -saidas){
                    cerr << "id_out < -Nin";
                    return false;
                }
                if(id_out[contOut] > port){
                    cerr << "id_out > numero de portas";
                    cout << " " << id_out[contOut];
                    return false;
                }
                contOut++;
        }
    }
    return true;
}
void Circuito::gerarTabela(void)
{
    int lim;
    lim = pow(3,Nin);
    for(int i = 0; i<lim; i++){
        calcularEntradas(i);
        imprimirEntradas();
        simular();
        imprimirSaidas();
        cout <<endl;
    }

}
