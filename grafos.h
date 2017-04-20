#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <list>
#include <algorithm>




using namespace std;
class grafo
{
public:
    grafo (int tam, int direcionado);
    void criarAresta(int vet1, int vet2,int peso);
    void mapaVerticedeletar(int id);
    void mapaVerticecriar();
    bool verificaIdExiste(int id);
    void criarVertice();
    void deletarVertice(int id);
    void deletarAresta(int id,int id2,int peso);
    int obterGrau(int id);
    int obterGrauGrafo();
    bool verificarVizinhanca(int id1,int id2);
    void listarAdjacentes(int id1);
    bool verificaRegular(int regular);
    bool verificarCompleto();
    bool verificaConexo();
    int*  buscaProfundidade(int id);
    void auxbuscaProfundidade(int* vetor, int id,int i);
    bool verificaArestaPonte(int id1, int id2);
    int numeroComponeteconexo();
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
    void getComponentes();
    bool verificaEuriliano();
    grafo grafoTrasposto();
    void getArticulacoes();
    void getPontes();
    void getRaioDiametroCentroPeriferia();
    void getAGM();

    ~grafo();

private:
    int tamanho;
    bool direcionado;
    list<pair<int, int> > *adj;
    int *vetor;
    
    void calculaCaminhoDijkstra(int no1, int no2);
    void calculaCaminhoFloyd(int no1, int no2);

};


#endif // GRAFO_H_INCLUDED
