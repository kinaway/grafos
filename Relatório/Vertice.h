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
    int particao;
    listaArestas lista_arestas;

    Vertice (int id, int particao);
    void adicionaAresta(int id, int peso);

    ~Vertice();

private:


};


#endif // VERTICE_H_INCLUDED
