#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <list>
#include <algorithm>



using namespace std;
typedef list<pair<int, list<pair<int, int> > > >  lista_adjacencia;

class grafo
{
public:
    grafo (int tam, int direcionado);
    void criarVertice(int id);      // 1
    bool verificaIdExiste(int id);  // 2
    void deletarVertice(int id);    // 3
    void deletarAresta(int id,int id2,int peso);    // 4
    void criarAresta(int vet1, int vet2,int peso);  // 5
    void imprimirGrau(int id); // 6
    int obterGrauGrafo(); // 7
    bool verificaRegular(int regular); // 8
    int getTamanho(); // 9
    bool verificaTrivial(); // 10
    bool verificaNulo(); // 11
    void calcularCaminho(int no1, int no2, int algoritmo); // 12
    void fechoTransitivoDireto(int id1); // 13
    void fechoTransitivoIndireto(int id1); // 14
    void getSequenciaGraus(); // 15
    void getSubgrafoInduzido(list<int> vertices); // 16
    void getComplementar(); // 17
    void getComponentesFortementeConexas(); // 18
    bool verificaEuleriano(); // 19
    void getArticulacoes(); // 20
    void getPontes(); // 21
    void getRaioDiametroCentroPeriferia(); // 22
    void getAGM(); // 23
    void salvarArquivo(ofstream& arquivo);
    grafo grafoTransposto();

    ~grafo();

private:
    bool direcionado;
    lista_adjacencia *lista_vertices; //lista com um pair contendo :id do vertice, lista de adjacência dele contendo: id do nó para quem tem ligação, valor da aresta;

    int obterGrau(int id);
    void calculaCaminhoDijkstra(int no1, int no2);
    void calculaCaminhoFloyd(int no1, int no2);
    int* retornaVetorDijkstra(int no1);
    double** retornaMatrizFloyd();
    int getComponentesConexas();
    bool buscaProfundidadeCiclo();
    bool auxbuscaProfundidadeCiclo(list<int> visitados, int id, int pai);
    list<pair<int, int> >* getAdj(int no);
    void mapaVerticedeletar(int id);
    void mapaVerticecriar();
    void listarAdjacentes(int id1);
    bool verificarCompleto();
    bool verificaConexo();
    int*  buscaProfundidade(int id);
    void auxbuscaProfundidade(int* vetor, int id,int i);
    bool verificaArestaPonte(int id1, int id2, int peso);
    bool verificaBipartido(int id);
    void auxVerificaBipartido(int* vetor,int id,int *j,int id2,bool *verifica);
    bool verificaVerticeArticulacao(int id);
    void buscaVertice(pair<int, int> *b,int *vetor,int id,int id2,int valor);
    int* auxbuscaProfundidadeTransitivo(int* vetor,int id1,int id2,int* j);
    void fechoTransitivoIndireto(int id1,int id2, grafo grafos2);

    void imprimirGrafo();
    int numeroArestas();
    bool possuiCiclo();
    grafo copiarGrafo();

};


#endif // GRAFO_H_INCLUDED
