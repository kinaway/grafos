#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <list>
#include "Aresta.h"

using namespace std;

typedef list<Aresta> listaArestas;

class Vertice
{
public:
    int id;
    listaArestas lista_arestas;
    int particao;
    Vertice (int id);
    void adicionaAresta(int id, int peso);

    ~Vertice();

private:


};


#endif // VERTICE_H_INCLUDED
