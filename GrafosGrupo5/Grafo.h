#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <list>
#include <algorithm>
#include "Aresta.h"
#include "Vertice.h"

using namespace std;
typedef list<pair<int, list<pair<int, int> > > >  lista_adjacencia;
typedef list<Vertice> listaVertices;

class Grafo
{
public:
    Grafo (int direcionado);
    bool direcionado;

    bool criarVertice(int id);      // 1
    bool verificaIdExiste(int id);  // 2
    bool deletarVertice(int id);    // 3
    bool deletarAresta(int id,int id2,int peso);    // 4
    bool criarAresta(int vet1, int vet2,int peso);  // 5
    int getGrau(int id);        // 6
    int getGrauEntrada(int id); // 6
    int getGrauSaida(int id);   // 6
    int getGrauGrafo(); // 7
    bool verificaRegular(int regular); // 8
    int getOrdemGrafo(); // 9
    bool verificaTrivial(); // 10
    bool verificaNulo(); // 11
    //void calculaCaminhoDijkstra(int no1, int no2); // 12
    //void calculaCaminhoFloyd(int no1, int no2);    // 12
    //void fechoTransitivoDireto(int id1); // 13
    //void fechoTransitivoIndireto(int id1); // 14
    void getSequenciaGraus(); // 15
    void getSubgrafoInduzido(list<int> vertices); // 16
    void getComplementar(); // 17
    //void getComponentesFortementeConexas(); // 18
    bool verificaEuleriano(); // 19
    void getArticulacoes(); // 20
    void getPontes(); // 21
    //void getRaioDiametroCentroPeriferia(); // 22
    //void getAGM(); // 23
    void salvarArquivo(ofstream& arquivo);
    //grafo grafoTransposto();
    int getComponentesConexas();
    void imprimirGrafo();

    ~Grafo();

private:
    //lista_adjacencia *lista_vertices; //lista com um pair contendo :id do vertice, lista de adjacência dele contendo: id do nó para quem tem ligação, valor da aresta;
    listaVertices lista_vertices;

    Vertice* getVertice(int id);

    int* buscaProfundidade();
    void auxbuscaProfundidade(int* vetor, int id_vertice,int i);
    bool verificaVerticeArticulacao(int id);
    Grafo copiarGrafo();
    bool verificaArestaPonte(int id1, int id2, int peso);
    bool possuiAresta(int id1, int id2);
    bool verificaConexo();
    /*void calculaCaminhoDijkstra(int no1, int no2);
    void calculaCaminhoFloyd(int no1, int no2);
    int* retornaVetorDijkstra(int no1);
    double** retornaMatrizFloyd();

    bool buscaProfundidadeCiclo();
    bool auxbuscaProfundidadeCiclo(list<int> visitados, int id, int pai);
    list<pair<int, int> >* getAdj(int no);
    void mapaVerticedeletar(int id);
    void mapaVerticecriar();
    void listarAdjacentes(int id1);
    bool verificarCompleto();




    bool verificaBipartido(int id);
    void auxVerificaBipartido(int* vetor,int id,int *j,int id2,bool *verifica);

    void buscaVertice(pair<int, int> *b,int *vetor,int id,int id2,int valor);
    int* auxbuscaProfundidadeTransitivo(int* vetor,int id1,int id2,int* j);
    void fechoTransitivoIndireto(int id1,int id2, grafo grafos2);


    int numeroArestas();
    bool possuiCiclo();
    */


};


#endif // GRAFO_H_INCLUDED
