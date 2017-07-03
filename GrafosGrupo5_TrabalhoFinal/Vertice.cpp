#include "Vertice.h"

Vertice::Vertice(int id, int particao){
    this->id = id;
    this->particao = particao;
}

void Vertice::adicionaAresta(int id, int peso){
    Aresta aresta(id, peso);
    lista_arestas.push_back(aresta);
}

Vertice::~Vertice(){
    lista_arestas.clear();
}
