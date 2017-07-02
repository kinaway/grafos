#include "Vertice.h"

Vertice::Vertice(int id){
    this->id = id;
}


void Vertice::adicionaAresta(int id, int peso){
    Aresta aresta(id, peso);
    lista_arestas.push_back(aresta);
}

Vertice::~Vertice(){
    lista_arestas.clear();
}
