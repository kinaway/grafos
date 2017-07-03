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




int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        cout << "Falta argumentos!" << endl << "Nome de arquivo de entrada e nome de arquivo de saida necessários.";
        exit(0);
    }

    ifstream txtFile;
    string nome, input, line, buffer;
    int escolhas = 1;
    nome = argv[1];

    bool direcionado = false;

    txtFile.open(nome.c_str());

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
            cout << "Vertices: "<< endl;
            for(int i = 0; i < vertices.size(); i++){
                cout << "[" << i << "]: " << vertices[i] << endl;
                g.criarVertice(i, vertices[i]);
            }
        }

        v.clear();

    }


    txtFile.close();

    while(escolhas !=0)
    {
        menu();
        escolhas = getInputInt();
        clear();
        switch(escolhas)
        {
        case 1:
            getPAGMGGuloso(&g);
            break;
        case 2:
            getPAGMGRandomizado(&g);
            break;
        case 3:
            getPAGMGReativo(&g);
            break;
        case 0:
            salvarArquivo(&g, argv[2]);
            break;
        }
    }
}
