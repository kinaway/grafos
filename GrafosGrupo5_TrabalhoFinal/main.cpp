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
    int ordem, direcionado,escolhas = 1;
    vector<int>* particoes = NULL;
    nome = argv[1];

    cout << endl << "O grafo é direcionado?"  <<endl;
    cout << "1 - Sim" << endl;
    cout << "0 - Nao" << endl;
    direcionado = getInputInt();

    txtFile.open(nome.c_str());
    getline(txtFile, line);

    stringstream ss(line);
    vector<int> v;

     while (ss >> buffer){
        int valor = atoi(buffer.c_str());
        v.push_back(valor);
    }

    if(v.size() == 1){
        ordem = v[0];
    }
    else if(v.size() > 1){
        ordem = v[0];
        int total = 0;
        particoes = new vector<int>;
        for(int i = 1; i < v.size(); i++){
            particoes->push_back(v[i]);
            total += v[i];
        }
        if(total != ordem){
            cout << "Primeira linha do arquivo deve conter m [d]" << endl;
            cout << "Onde m é a ordem do grafo, e d são diferentes particões" << endl;
            cout << "dado que a soma de todas as partiçoes é igual a m" << endl;
            return 0;
        }
    }
    else{
        cout << "Primeira linha do arquivo deve conter m [d]" << endl;
        cout << "Onde m é a ordem do grafo, e d são diferentes particões" << endl;
        cout << "dado que a soma de todas as partiçoes é igual a m" << endl;
        return 0;
    }

    Grafo g(direcionado, ordem, particoes);

    while (getline(txtFile, line)){

        string buffer;
        stringstream ss(line); // Insert the string into a stream

        vector<int> vetor; // Create vector to hold our words

        while (ss >> buffer){
            int v = atoi(buffer.c_str());
            vetor.push_back(v);
        }

        // caso não tenha peso nas arestas, adicionamos peso 0
        if(vetor.size() == 2)
            vetor.push_back(0);

        g.criarAresta(vetor[0],vetor[1],vetor[2]);
        if(direcionado == 0)
            g.criarAresta(vetor[1],vetor[0],vetor[2]);
        cout << "Nó criado: " << vetor[0] << ", " << vetor[1]<< ", " << vetor[2] << endl;

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
