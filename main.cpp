#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include "Aresta.h"
#include "Vertice.h"
#include "Grafo.h"

using namespace std;

int getInputInt(){
    int numero;
    string input;
    getline (std::cin, input);
    stringstream(input) >> numero;
    return numero;
}

string getInputString(){
    string input;
    getline (std::cin, input);
    return input;
}

void clear(){
    // system('cls') so funciona no windows
    // maneira multiplataforma mais simples de limpar console
    cout << string(80, '\n');
}

void voltarMenu(){
    cout << "Pressione Enter para voltar ao menu." << endl;
    getInputString();
    clear();
}


void criarVertice(Grafo *g)
{
    cout << "Digite o id do vertice que deseja criar:" << endl;
    int id = getInputInt();

    if(g->criarVertice(id))
        cout << "Vertice "<< id <<" criado." <<endl;
    else
        cout << "Não foi possível criar um vértice com esse ID." << endl;

    voltarMenu();
}
void verificarIdxiste(Grafo *g)
{
    int id;
    cout << "Digite o id do vertice que deseja verificar: " << endl;
    id = getInputInt();

    if(g->verificaIdExiste(id) == true)
    {
        cout << "O id passado existe." << endl;
    }
    else
    {
        cout << "O id passado não existe." << endl;
    }

    voltarMenu();
}

void deletarVertice(Grafo *g)
{
    int id;

    cout << "Digite um id:" <<endl;
    id = getInputInt();

    if(g->deletarVertice(id) == true)
    {
        cout << "O id passado foi deletado" << endl;
    }
    else
    {
        cout << "O id passado não existe." << endl;
    }

    voltarMenu();
}


void  deletarAresta(Grafo *g)
{
    int id1,id2,peso;

    cout << "Digite o id do primeiro vértice: " << endl;
    id1 = getInputInt();
    cout << "Digite o id do segundo vértice: " << endl;
    id2 = getInputInt();
    cout << "Digite o peso da aresta: " << endl;
    peso = getInputInt();

    if(g->deletarAresta(id1,id2,peso) == true)
    {
        cout << "A aresta foi deletada." << endl;
    }
    else
    {
        cout << "Não foi possível excluir a aresta." << endl;
    }

    voltarMenu();
}

void criarAresta(Grafo *g)
{
    int id1,id2,peso;

    cout << "Digite primeiro id onde uma aresta será criada: " << endl;
    id1 = getInputInt();
    cout << "Digite segundo id onde uma aresta será criada: " << endl;
    id2 = getInputInt();
    cout << "Digite o peso desta aresta: " << endl;
    peso = getInputInt();

    if(g->criarAresta(id1,id2,peso) == true){
        cout << "A aresta foi criada." << endl;
    }
    else{
        cout << "Não é possível criar a aresta pois um dos vértices não existe no grafo." << endl;
    }
    voltarMenu();
}

void obterGrauVertice(Grafo *g)
{
    int id;
    bool check = false;

    cout << "Digite um id: " << endl;
    id = getInputInt();

    if(g->direcionado == true){
        int grau_entrada = g->getGrauEntrada(id);
        int grau_saida = g->getGrauSaida(id);

        if(grau_entrada != -1 && grau_saida != -1){
            cout << "Grau de entrada do vértice " << id << ": "<< grau_entrada << endl;
            cout << "Grau de saída do vértice " << id << ": "<< grau_saida << endl;
            check = true;
        }
    }
    else{
        int grau = g->getGrau(id);
        if(grau != -1){
            cout << "Grau do vértice " << id << ": "<< grau << endl;
            check = true;
        }
    }

    if(check == false){
        cout << "Não foi possível obter o grau do vértice selecionado. " << endl;
    }

    voltarMenu();
}

void obterGrauGrafo(Grafo *g) {
    int grau = g->getGrauGrafo();
    cout << "Grau do grafo: " << grau << endl;

    voltarMenu();
}

void verificarKRegular(Grafo *g) {
    cout << "Digite o K: "<<endl;
    int k;
    k = getInputInt();

    if(g->verificaRegular(k)){
        cout << "O Grafo é " << k << " regular." << endl;
    } else {
        cout << "O Grafo não é " << k << " regular." << endl;
    }

    voltarMenu();
}


void obterOrdemGrafo(Grafo *g) {
    cout << "A ordem do Grafo é "<< g->getOrdemGrafo() <<endl;

    voltarMenu();
}

void isTrivial(Grafo *g) {
    if(g->verificaTrivial()){
        cout << "O Grafo é trivial.";
    } else {
        cout << "O Grafo nao é trivial.";
    }

    voltarMenu();
}

void isNulo(Grafo *g) {
    if(g->verificaNulo()){
        cout << "O Grafo é nulo." << endl;
    } else {
        cout << "O Grafo nao é nulo." << endl;
    }

    voltarMenu();
}

void calcularCaminho(Grafo *g) {
    int algoritmo;
    int no1, no2;


    cout << "Qual algoritmo usar?:"<<endl;
    cout << "1 - Dijkstra"<<endl;
    cout << "2 - Floyd"<<endl;
    algoritmo = getInputInt();

    cout << "Qual o primeiro nó?:"<<endl;
    no1 = getInputInt();
    cout << "Qual o segundo nó?:"<<endl;
    no2 = getInputInt();

    if(algoritmo == 1){
        g->calculaCaminhoDijkstra(no1, no2);
    }
    else if(algoritmo == 2){
        g->calculaCaminhoFloyd(no1, no2);
    }
    else{
        cout << "Algoritmo escolhido inválido." << endl;
    }

    voltarMenu();
}

void calcularFechoDireto(Grafo *g) {
    cout << "Informe o numero do no1:"<<endl;
    int no1;
    no1 = getInputInt();
//    int no2;
//    no2 = getInputInt();
    g->fechoTransitivoDireto(no1);
    voltarMenu();
}

void calcularFechoIndireto(Grafo *g) {
    cout << "Informe o numero do no1:"<<endl;
    int no1;
    no1 = getInputInt();
    g->fechoTransitivoIndireto(no1);

    voltarMenu();
}

void imprimirSequenciaGraus(Grafo *g) {
    cout << "A sequencia de Graus é:" << endl;
    g->getSequenciaGraus(); //Imprime a sequencia de graus do grafo

    voltarMenu();
}

void getSubgrafoInduzido(Grafo *g) {
    cout << "Digite os vertices. -1 para parar." << endl;
    int c = 0;
    list<int> vertices;
    while(true){
        c = getInputInt();
        if(c == -1)
            break;
        vertices.push_back(c);
    }
    cout << "Subgrafo induzido: ";
    g->getSubgrafoInduzido(vertices); //Imprime o subgrafo induzido

    voltarMenu();
}

void getGrafoComplementar(Grafo *g) {
    cout << "O grafo complementar é:" << endl;
    g->getComplementar(); //Imprime o grafo complementar do grafo lido

    voltarMenu();
}
void getComponentesFortementeConexas(Grafo *g) {
    cout << "As componentes são:" << endl;
    g->getComponentesFortementeConexas(); //

    voltarMenu();
}

void isEuleriano(Grafo *g) {
    if(g->verificaEuleriano()){
        cout << "O Grafo é Euleriano." << endl;
    } else {
        cout << "O Grafo nao é Euleriano." << endl;
    }

    voltarMenu();
}

void getArticulacoes(Grafo *g) {
    cout << "Os nós de articulação são:" << endl;
    g->getArticulacoes();

    voltarMenu();
}

void getPontes(Grafo *g) {
    cout << "As arestas pontes são:" << endl;
    g->getPontes();

    voltarMenu();
}

void getRaioDiametroCentroPeriferia(Grafo *g){
    cout << "O raio, diâmetro, centro e periferia são:" << endl;
    g->getRaioDiametroCentroPeriferia(); //

    voltarMenu();
}

void getAGM(Grafo *g){
    cout << "A AGM ou floresta mínima é:" << endl;
    g->getAGM();

    voltarMenu();
}

void salvarArquivo(Grafo *g, char nome[]){
    ofstream arquivo(nome);
    if(arquivo.is_open()){
        g->salvarArquivo(arquivo);
    } else {
        cout << "arquivo de saida '"<<nome<<"' não encontrado!"<<endl;
    }
}

void menu()
{
    cout << endl << endl << "\t\t\t ---MENU PRINCIPAL---" << endl << endl;
    cout << "\t Escolha uma opção:" << endl;
    cout << "\t 1)" << " " << "Criar vertice"<< endl;
    cout << "\t 2)" << " " << "Verificar se vertice existe"<< endl;
    cout << "\t 3)" << " " << "Deletar vertice"<< endl;
    cout << "\t 4)" << " " << "Deletar aresta"<< endl;
    cout << "\t 5)" << " " << "Criar aresta"<< endl;
    cout << "\t 6)" << " " << "Obter grau de um vertice"<< endl;
    cout << "\t 7)" << " " << "Obter grau do grafo"<< endl;
    cout << "\t 8)" << " " << "Verificar se o grafo é kregular"<< endl;
    cout << "\t 9)" << " " << "Consultar ordem do grafo"<< endl;
    cout << "\t 10)" << " " << "Consultar se o grafo é trivial"<< endl;
    cout << "\t 11)" << " " << "Consultar se o grafo é nulo"<< endl;
    cout << "\t 12)" << " " << "Calcular caminho minimo"<< endl;
    cout << "\t 13)" << " " << "Calcular fecho trasitivo direto de um no"<< endl;
    cout << "\t 14)" << " " << "Calcular fecho trasitivo indireto de um no"<< endl;
    cout << "\t 15)" << " " << "Imprimir sequencia de graus"<< endl;
    cout << "\t 16)" << " " << "Calcular subgrafo induzido"<< endl;
    cout << "\t 17)" << " " << "Imprimir o grafo complementar"<< endl;
    cout << "\t 18)" << " " << "Imprimir componentes fortemente conexas"<< endl;
    cout << "\t 19)" << " " << "Verificar se o Grafo é Euleriano"<< endl;
    cout << "\t 20)" << " " << "Apresentar nós de articulação"<< endl;
    cout << "\t 21)" << " " << "Apresentar arestas pontes"<< endl;
    cout << "\t 22)" << " " << "Apresentar o raio, diâmetro, centro e periferia do grafo"<< endl;
    cout << "\t 23)" << " " << "Apresentar o AGM ou florestas de custo mínimo"<< endl;
    cout << "\t 0)"  << " " << "Salvar em arquivo e Sair"<<endl;
}




int main(int argc, char *argv[])
{
    if(argc < 3){
        cout << "Falta argumentos!" << endl << "Nome de arquivo de entrada e nome de arquivo de saida necessários.";
        exit(0);
    }

    ifstream txtFile;
    string input;
    int i,vetor[3],c, direcionado,escolhas = 1,ponderado;
    string nome;
    nome = argv[1];
    cout << endl << "O grafo é direcionado?"  <<endl;
    cout << "1 -" << " " << "Sim" << endl;
    cout << "0 -" << " " << "Nao" << endl;
    direcionado = getInputInt();
    cout << endl;
    clear();
    txtFile.open(nome.c_str());
    txtFile >> c;

    Grafo g(direcionado, c);

    cout << endl << "O grafo é ponderado?"  <<endl;
    cout << "1 -" << " " << "Sim" << endl;
    cout << "0 -" << " " << "Nao" << endl;
    ponderado = getInputInt();
if(ponderado == 1){
    while(!txtFile.eof())
    {
        i = 0;
        while(i!=3){
            txtFile >> c;
            vetor[i] = c;
            i++;
            if(i == 3)
            {
                /*if(!g.verificaIdExiste(vetor[0])){
                    g.criarVertice(vetor[0]);
                }
                if(!g.verificaIdExiste(vetor[1])){
                    g.criarVertice(vetor[1]);
                }*/
                g.criarAresta(vetor[0],vetor[1],vetor[2]);
                if(direcionado == 0)
                    g.criarAresta(vetor[1],vetor[0],vetor[2]);
            }
        }
    }

    }
 else
    {
    while(!txtFile.eof())
    {
        i = 0;
        while(i!=2){
            txtFile >> c;
            vetor[i] = c;
            i++;
            if(i == 2)
            {
                /*if(!g.verificaIdExiste(vetor[0])){
                    g.criarVertice(vetor[0]);
                }
                if(!g.verificaIdExiste(vetor[1])){
                    g.criarVertice(vetor[1]);
                }*/
                g.criarAresta(vetor[0],vetor[1],0);
                if(direcionado == 0)
                    g.criarAresta(vetor[1],vetor[0],0);
            }
        }

    }
}


    txtFile.close();

    while(escolhas !=0){


        menu();
        escolhas = getInputInt();
        clear();
        switch(escolhas)
        {
            case 1:
                criarVertice(&g);
                break;
            case 2:
                verificarIdxiste(&g);
                break;
            case 3:
                deletarVertice(&g);
                break;
            case 4:
                deletarAresta(&g);
                break;
            case 5:
                criarAresta(&g);
                break;
            case 6:
                obterGrauVertice(&g);
                break;
            case 7:
                obterGrauGrafo(&g);
                break;
            case 8:
                verificarKRegular(&g);
                break;
            case 9:
                obterOrdemGrafo(&g);
                break;
            case 10:
                isTrivial(&g);
                break;
            case 11:
                isNulo(&g);
                break;
            case 12:
                calcularCaminho(&g);
                break;
            case 13:
                calcularFechoDireto(&g);
                break;
            case 14:
                calcularFechoIndireto(&g);
                break;
            case 15:
                imprimirSequenciaGraus(&g);
                break;
            case 16:
                getSubgrafoInduzido(&g);
                break;
            case 17:
                getGrafoComplementar(&g);
                break;
            case 18:
                getComponentesFortementeConexas(&g);
                break;
            case 19:
                isEuleriano(&g);
                break;
            case 20:
                getArticulacoes(&g);
                break;
            case 21:
                getPontes(&g);
                break;
            case 22:
                getRaioDiametroCentroPeriferia(&g);
                break;
            case 23:
                getAGM(&g);
                break;
            case 0:
                salvarArquivo(&g, argv[2]);
                break;
        }
    }
}
