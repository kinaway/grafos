#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include "grafos.h"


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
    cout << "Pressione Enter para voltar ao menu"<<endl;
    getInputString();
    clear();
}


void criarVertice(grafo *Teste2)
{
    cout << "Digite o id do vertice que deseja criar" << endl;
    int id = getInputInt();

    Teste2->criarVertice(id);
    cout << "Vertice "<< id <<" criado" <<endl;

    voltarMenu();
}
void vereficarIdxiste(grafo *Teste2)
{
    int id;
    bool verifica;
    cout << "Digite o id do vertice que deseja verificar" << endl;
    id = getInputInt();
    verifica = Teste2->verificaIdExiste(id);
    if(verifica == true)
    {
        cout << "O id passado existe" << endl;
    }
    else
    {
        cout << "O id passado não existe" << endl;
    }

    voltarMenu();
}

void deletarVertice(grafo *Teste2)
{
    int id;
    bool verifica;

    cout << "Digite um id" <<endl;
    id = getInputInt();
    verifica = Teste2->verificaIdExiste(id);
    if(verifica == true)
    {
        Teste2->deletarVertice(id);
        cout << "O id passado foi deletado"<<endl;
    }
    else
    {
        cout << "O id passado não existe ou ja foi deletado";
    }

    voltarMenu();
}


void  deletarAresta(grafo *Teste2)
{
    int id1,id2,peso;
    bool verifica;

    cout << "Digite primeiro id onde uma arestasera sera deletada"<<endl;
    id1 = getInputInt();
    cout << "Digite segundo id onde uma aresta sera deletada entre o primeiro e o segundo id digitados"<<endl;
    id2 = getInputInt();
    cout << "Digite o peso do id que sera deletado"<<endl;
    peso = getInputInt();
    verifica = Teste2->verificaIdExiste(id1);
    if(verifica == true)
    {
        Teste2->deletarAresta(id1,id2,peso);
        cout << "O id passado foi deletado";
    }
    else
    {
        cout << "O id passado não existe ou ja foi deletado";
    }

    voltarMenu();
}

void   criarAresta(grafo *Teste2)
{
    int id1,id2,peso;
    bool verifica;

    cout << "Digite primeiro id onde uma aresta sera criada"<<endl;
    id1 = getInputInt();
    cout << "Digite segundo id onde uma aresta sera criada entre o primeiro e o segundo id digitados "<<endl;
    id2 = getInputInt();
    cout << "Digite o pese desta aresta"<<endl;
    peso = getInputInt();
    verifica = Teste2->verificaIdExiste(id1);
    if(verifica == true)
    {
        Teste2->criarAresta(id1,id2,peso);
        cout << "A aresta foi criada";
    }
    else
    {
        cout << "O id passado não existe ou ja foi deletado";
    }

    voltarMenu();
}

void obterGrauVertice(grafo *Teste2)
{
    int id;
    bool verifica;

    cout << "Digite um id"<<endl;
    id = getInputInt();
    verifica = Teste2->verificaIdExiste(id);
    if(verifica == true)
    {
        int grau = Teste2->obterGrau(id);
        cout << "Grau do vertice"<<" "<<grau;
    }
    else
    {
        cout << "O id passado não existe ou ja foi deletado";
    }

    voltarMenu();
}

void obterGrauGrafo(grafo *Teste2) {
    int grau = Teste2->obterGrauGrafo();
    cout << "Grau do grafo: "<<grau<<endl;

    voltarMenu();
}

void verificarKRegular(grafo *Teste2) {
    cout << "Digite o K: "<<endl;
    int k;
    k = getInputInt();
    if(Teste2->verificaRegular(k)){
        cout << "O Grafo eh "<<k<<" regular.";
    } else {
        cout << "O Grafo nao eh "<<k<<" regular.";
    }

    voltarMenu();
}


void informarGrau(grafo *Teste2) {
    cout << "A ordem do Grafo eh "<< Teste2->getTamanho() <<endl;

    voltarMenu();
}

void isTrivial(grafo *Teste2) {
    if(Teste2->verificaTrivial()){
        cout << "O Grafo eh trivial.";
    } else {
        cout << "O Grafo nao eh trivial.";
    }

    cout << "Pressione Enter para voltar ao menu"<<endl;
    getInputString();
}

void isNulo(grafo *Teste2) {
    if(Teste2->verificaNulo()){
        cout << "O Grafo eh nulo.";
    } else {
        cout << "O Grafo nao eh nulo.";
    }

    voltarMenu();
}

void calcularCaminho(grafo *Teste2) {
    cout << "Qual algoritmo usar?:"<<endl;
    cout << "1)" << " " << "Dijkstra"<<endl;
    cout <<"2)" << " " << "Floyd"<<endl;
    int algoritmo;
    algoritmo = getInputInt();

    int no1, no2;
    cout << "Qual o primeiro nó?:"<<endl;
    no1 = getInputInt();
    cout << "Qual o segundo nó?:"<<endl;
    no2 = getInputInt();
    Teste2->calcularCaminho(no1, no2, algoritmo);

    voltarMenu();
}

void calcularFechoDireto(grafo *Teste2) {
    cout << "Informe o numero do no1:"<<endl;
    int no1;
    no1 = getInputInt();
    int no2;
    no2 = getInputInt();
    Teste2->fechoTransitivoDireto(no1, no2);

    voltarMenu();
}

void calcularFechoIndireto(grafo *Teste2) {
    cout << "Informe o numero do no1:"<<endl;
    int no1;
    no1 = getInputInt();
    Teste2->fechoTransitivoIndireto(no1);

    voltarMenu();
}

void imprimirSequenciaGraus(grafo *Teste2) {
    cout << "A sequencia de Graus eh:" << endl;
    Teste2->getSequenciaGraus(); //Imprime a sequencia de graus do grafo

    voltarMenu();
}

void getSubgrafoInduzido(grafo *Teste2) {
    cout << "Digite os vertices. -1 para parar." << endl;
    int c = 0;
    list<int> vertices;
    while(c!=-1){
        c = getInputInt();
        vertices.push_back(c);
    }
    Teste2->getSubgrafoInduzido(vertices); //Imprime o subgrafo induzido

    voltarMenu();
}

void getGrafoComplementar(grafo *Teste2) {
    cout << "O grafo complementar eh:" << endl;
    Teste2->getComplementar(); //Imprime o grafo complementar do grafo lido

    voltarMenu();
}
void getComponentes(grafo *Teste2) {
    cout << "As componentes são:" << endl;
    Teste2->getComponentes(); //

    voltarMenu();
}

void isEuriliano(grafo *Teste2) {
    if(Teste2->verificaEuriliano()){
        cout << "O Grafo eh Euriliano.";
    } else {
        cout << "O Grafo nao eh Euriliano.";
    }

    voltarMenu();
}

void getArticulacoes(grafo *Teste2) {
    cout << "Os nós de articulação são:" << endl;
    Teste2->getArticulacoes(); //

    voltarMenu();
}

void getPontes(grafo *Teste2) {
    cout << "As arestas pontes são:" << endl;
    Teste2->getPontes(); //

    voltarMenu();
}

void getRaioDiametroCentroPeriferia(grafo *Teste2){
    cout << "O raio, diâmetro, centro e periferia são:" << endl;
    Teste2->getRaioDiametroCentroPeriferia(); //

    voltarMenu();
}

void getAGM(grafo *Teste2){
    cout << "A AGM ou floresta mínima é:" << endl;
    Teste2->getAGM(); //

    voltarMenu();
}

void salvarArquivo(grafo *Teste2, char nome[]){
    ofstream arquivo(nome);
    if(arquivo.is_open()){
        Teste2->salvarArquivo(arquivo);
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
    cout << "\t *6)" << " " << "Obter grau de um vertice"<< endl;
    cout << "\t 7)" << " " << "Obter grau do grafo"<< endl;
    cout << "\t 8)" << " " << "Verificar se o grafo eh kregular"<< endl;
    cout << "\t 9)" << " " << "Consultar ordem do grafo"<< endl;
    cout << "\t 10)" << " " << "Consultar se o grafo eh trivial"<< endl;
    cout << "\t 11)" << " " << "Consultar se o grafo eh nulo"<< endl;
    cout << "\t 12)" << " " << "Calcular caminho minimo"<< endl;
    cout << "\t *13)" << " " << "Calcular fecho trasitivo direto de um no"<< endl;
    cout << "\t *14)" << " " << "Calcular fecho trasitivo indireto de um no"<< endl;
    cout << "\t 15)" << " " << "Imprimir sequencia de graus"<< endl;
    cout << "\t *16)" << " " << "Calcular subgrafo induzido"<< endl;
    cout << "\t 17)" << " " << "Imprimir o grafo complementar"<< endl;
    cout << "\t *18)" << " " << "Imprimir componentes fortemente conexas"<< endl;
    cout << "\t *19)" << " " << "Verificar se o Grafo é Euliriano"<< endl;
    cout << "\t *20)" << " " << "Apresentar nós de articulação"<< endl;
    cout << "\t *21)" << " " << "Apresentar arestas pontes"<< endl;
    cout << "\t *22)" << " " << "Apresentar o raio, diâmetro, centro e periferia do grafo"<< endl;
    cout << "\t *23)" << " " << "Apresentar o AGM ou florestas de custo mínimo"<< endl;
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
    int i,vetor[3],c, direcionado,escolhas = 1;
    string nome;
    nome = argv[1];
    cout << endl << "O grafo eh direcionado?"  <<endl;
    cout << "1)" << " " << "Sim"<<endl;
    cout << "0)" << " " << "Nao"<<endl;
    direcionado = getInputInt();
    cout << endl;
    txtFile.open(nome.c_str());

    txtFile >> c;

    grafo Teste1(c, direcionado);

    while(!txtFile.eof())
    {
        i = 0;
        while(i!=3){
            txtFile >> c;
            vetor[i] = c;
            i++;
            if(i == 3)
            {
                if(!Teste1.verificaIdExiste(vetor[0])){
                    Teste1.criarVertice(vetor[0]);
                }
                if(!Teste1.verificaIdExiste(vetor[1])){
                    Teste1.criarVertice(vetor[1]);
                }
                Teste1.criarAresta(vetor[0],vetor[1],vetor[2]);
                if(direcionado == 0)
                    Teste1.criarAresta(vetor[1],vetor[0],vetor[2]);
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
                criarVertice(&Teste1);
                break;
            case 2:
                vereficarIdxiste(&Teste1);
                break;
            case 3:
                deletarVertice(&Teste1);
                break;
            case 4:
                deletarAresta(&Teste1);
                break;
            case 5:
                criarAresta(&Teste1);
                break;
            case 6:
                obterGrauVertice(&Teste1);
                break;
            case 7:
                obterGrauGrafo(&Teste1);
                break;
            case 8:
                verificarKRegular(&Teste1);
                break;
            case 9:
                informarGrau(&Teste1);
                break;
            case 10:
                isTrivial(&Teste1);
                break;
            case 11:
                isNulo(&Teste1);
                break;
            case 12:
                calcularCaminho(&Teste1);
                break;
            case 13:
                calcularFechoDireto(&Teste1);
                break;
            case 14:
                calcularFechoIndireto(&Teste1);
                break;
            case 15:
                imprimirSequenciaGraus(&Teste1);
                break;
            case 16:
                getSubgrafoInduzido(&Teste1);
                break;
            case 17:
                getGrafoComplementar(&Teste1);
                break;
            case 18:
                getComponentes(&Teste1);
                break;
            case 19:
                isEuriliano(&Teste1);
                break;
            case 20:
                getArticulacoes(&Teste1);
                break;
            case 21:
                getPontes(&Teste1);
                break;
            case 22:
                getRaioDiametroCentroPeriferia(&Teste1);
                break;

            case 23:
                getAGM(&Teste1);
                break;
            case 0:
                salvarArquivo(&Teste1, argv[2]);
                escolhas = 0;
                break;
        }
    }
}
