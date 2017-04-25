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
    void criarAresta(int vet1, int vet2,int peso);
    void mapaVerticedeletar(int id);
    void mapaVerticecriar();
    bool verificaIdExiste(int id);
    void criarVertice(int id);
    void deletarVertice(int id);
    void deletarAresta(int id,int id2,int peso);

    int obterGrau(int id);
    void imprimirGrau(int id);
    int obterGrauGrafo();
    void listarAdjacentes(int id1);
    bool verificaRegular(int regular);
    bool verificarCompleto();
    bool verificaConexo();
    int*  buscaProfundidade(int id);
    void auxbuscaProfundidade(int* vetor, int id,int i);
    bool verificaArestaPonte(int id1, int id2, int peso);
    bool verificaBipartido(int id);
    void auxVerificaBipartido(int* vetor,int id,int *j,int id2,bool *verifica);
    bool verificaVerticeArticulacao(int id);
    void buscaVertice(pair<int, int> *b,int *vetor,int id,int id2,int valor);
    void fechoTransitivoDireto(int id1);
    int* auxbuscaProfundidadeTransitivo(int* vetor,int id1,int id2,int* j);
    void fechoTransitivoIndireto(int id1);
    void fechoTransitivoDireto(int id1,int id2);
    void fechoTransitivoIndireto(int id1,int id2, grafo grafos2);
    bool verificaTrivial();
    bool verificaNulo();
    void calcularCaminho(int no1, int no2, int algoritmo);
    int getTamanho();
    void getSequenciaGraus();
    void getSubgrafoInduzido(list<int> vertices);
    void getComplementar();
    void getComponentesFortementeConexas();
    bool verificaEuriliano();
    grafo grafoTransposto();
    void getArticulacoes();
    void getPontes();
    void getRaioDiametroCentroPeriferia();
    void getAGM();
    void salvarArquivo(ofstream& arquivo);
    void imprimirGrafo();
    int numeroArestas();
    bool possuiCiclo();
    grafo copiarGrafo();

    ~grafo();

private:
    bool direcionado;
    lista_adjacencia *lista_vertices; //lista com um pair contendo :id do vertice, lista de adjacência dele contendo: id do nó para quem tem ligação, valor da aresta;

    void calculaCaminhoDijkstra(int no1, int no2);
    long int** calculaCaminhoFloyd(int no1, int no2);
    int getComponentesConexas();
    bool buscaProfundidadeCiclo();
    bool auxbuscaProfundidadeCiclo(list<int> visitados, int id, int pai);
    list<pair<int, int> >* getAdj(int no);

};


#endif // GRAFO_H_INCLUDED
