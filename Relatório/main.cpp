#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include "Aresta.h"
#include "Vertice.h"
#include "Grafo.h"

using namespace std;

int getInputInt()
{
    int numero;
    string input;
    getline (std::cin, input);
    stringstream(input) >> numero;
    return numero;
}

string getInputString()
{
    string input;
    getline (std::cin, input);
    return input;
}

void clear()
{
    // system('cls') so funciona no windows
    // maneira multiplataforma mais simples de limpar console
    cout << string(80, '\n');
}

void voltarMenu()
{
    cout << "Pressione Enter para voltar ao menu." << endl;
    getInputString();
    clear();
}


void getPAGMGRandomizado(Grafo *g){
    g->getPAGMGRandomizado();
}

void getPAGMGReativo(Grafo *g){
    g->getPAGMGReativo();
}

void getPAGMGGuloso(Grafo *g){
    g->getPAGMGGuloso();
}

void getPAGMGGulosoRandomizado(Grafo *g){
    g->getPAGMGGulosoRandomizado();
}

void salvarArquivo(Grafo *g, char nome[])
{
    ofstream arquivo(nome);
    if(arquivo.is_open())
    {
        g->salvarArquivo(arquivo);
    }
    else
    {
        cout << "arquivo de saida '"<<nome<<"' não encontrado!"<<endl;
    }
}

void menu()
{
    cout << endl << endl << "\t\t\t ---MENU PRINCIPAL---" << endl << endl;
    cout << "\t Escolha uma opção:" << endl;
    cout << "\t 1)" << " " << "Guloso"<< endl;
    cout << "\t 2)" << " " << "Randomizado"<< endl;
    cout << "\t 3)" << " " << "Reativo"<< endl;

    cout << "\t 0)"  << " " << "Salvar em arquivo e Sair"<<endl;
}




int main()
{
    char *instancias[] = {"10att48.clu", "10gr48.clu","10hk48.clu","11eil51.clu","12brazil58.clu","14st70.clu","15spain47.clu","16eil76.clu","16pr76.clu","20gr96.clu","20kroa100.clu","20krob100.clu","20kroc100.clu","20krod100.clu","20kroe100.clu","20rat99.clu","20rd100.clu","21eil101.clu","21lin105.clu","22pr107.clu","24gr120.clu","25pr124.clu","26bier127.clu","27europ47.clu","28gr137.clu","28pr136.clu","29pr144.clu","30kroa150.clu","30krob150.clu","31pr152.clu","32u159.clu","34gr202europe.clu","35gr137america.clu","40kroa200.clu","40krob200.clu","50gr96africa.clu"};
    for(int i = 0; i<14; i++){
    ifstream txtFile;
    string nome, input, line, buffer;
    int escolhas = 1;
    nome = instancias[i];
    cout << nome << endl;
    bool direcionado = false;

    txtFile.open(nome.c_str());
    if(!txtFile.is_open()){
        cout << "Arquivo nao encontrado." << endl;
    }
    stringstream ss(line);
    vector<int> v;
    vector<int> vertices;

    Grafo g(direcionado);

    while (getline(txtFile, line)){
        string buffer;
        stringstream ss(line); // Insert the string into a stream
        while (ss >> buffer){
            int valor = atoi(buffer.c_str());
            v.push_back(valor);
        }

        if(v.size() == 1){
            //cout << "É uma particão! " << endl;
            vertices.push_back(v[0]);
        }

        else if(v.size() == 3){
            //cout << "É uma aresta!" << endl;
            g.criarAresta(v[0], v[1], v[2]);
        }
        else{
            //cout << "Vertices: "<< endl;
            for(int i = 0; i < vertices.size(); i++){
                //cout << "[" << i << "]: " << vertices[i] << endl;
                g.criarVertice(i, vertices[i]);
            }
        }

        v.clear();

    }


    txtFile.close();
    clock_t Ticks[2];

    Ticks[0] = clock();
    getPAGMGGuloso(&g);
    Ticks[1] = clock();
    double tempo = (Ticks[1] - Ticks[0]) * 1000.0;
    cout << "Tempo: " << tempo << endl << endl;

    tempo = (Ticks[1] - Ticks[0]) * 1000.0;

    Ticks[0] = clock();
    getPAGMGGulosoRandomizado(&g);
    Ticks[1] = clock();
     tempo = (Ticks[1] - Ticks[0]) * 1000.0;
    cout << "Tempo: " << tempo << endl << endl;


    Ticks[0] = clock();
    getPAGMGRandomizado(&g);
    Ticks[1] = clock();
    tempo = (Ticks[1] - Ticks[0]) * 1000.0;
    cout << "Tempo: " << tempo << endl << endl;
    cout << "----------------------------------" << endl;

    }
}
