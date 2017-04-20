#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <time.h>
#include <stdlib.h>
#include "grafos.h"


using namespace std;


void criarVertice(grafo *Teste2)
{
    system("cls");
    int voltar = 0,sair = 0;
    while(sair == 0){

        Teste2->criarVertice();
        cout << "Vertice criada"<<endl;
        cout << "Deseja criar outra vertice ?"<< endl;
        cout << "1)" << " " << "Sim"<<endl;
        cout <<"2)" << " " << "Nгo"<<endl;
        cin >> sair;
        switch(sair)
        {
            case 1: sair = 0;
                break;
            case 2: sair = 1;
                break;
        }

    }

    /*cout <<"1)"<<" "<< "Voltar menu principal"<<endl;
     cin >> voltar;
     if(voltar != 0)
     {
     system("cls");
     return;
     }
     */
    system("cls");
    return;

}
void vereficarIdxiste(grafo *Teste2)
{
    system("cls");
    int voltar = 0,id,sair = 1;
    bool verifica;

    while(sair!=0){
        cout << "Digite um id"<<endl;
        cin >> id;
        verifica = Teste2->verificaIdExiste(id);
        if(verifica == true)
        {
            cout << "O id passado existe";
            cout << "Deseja sair:"<<endl;
            cout << "1)" << " " << "Sim"<<endl;
            cout <<"2)" << " " << "Nгo"<<endl;
            cin >> sair;
            switch(sair)
            {
                case 1: sair = 0;
                    break;
                case 2: sair = 1;
                    break;
            }
        }
        else
        {
            cout << "O id passado não existe";
            cout << "Deseja sair:"<<endl;
            cout << "1)" << " " << "Sim"<<endl;
            cout <<"2)" << " " << "Não"<<endl;
            cin >> sair;
            switch(sair)
            {
                case 1: sair = 0;
                    break;
                case 2: sair = 1;
                    break;
            }
        }
    }



    cout <<"1)"<<" "<< "Voltar menu principal"<<endl;
    cin >> voltar;
    if(voltar != 0)
    {
        system("cls");
        return;
    }
    return;

}

void deletarVertice(grafo *Teste2)
{
    system("cls");
    int voltar = 0,id,sair = 1;
    bool verifica;

    while(sair!=0){
        cout << "Digite um id"<<endl;
        cin >> id;
        verifica = Teste2->verificaIdExiste(id);
        if(verifica == true)
        {
            Teste2->deletarVertice(id);
            cout << "O id passado foi deletado"<<endl;
            cout << "Deseja sair:"<<endl;
            cout << "1)" << " " << "Sim"<<endl;
            cout <<"2)" << " " << "Nгo"<<endl;
            cin >> sair;
            switch(sair)
            {
                case 1: sair = 0;
                    break;
                case 2: sair = 1;
                    break;
            }
        }
        else
        {
            cout << "O id passado não existe ou ja foi deletado";
            cout << "Deseja sair:"<<endl;
            cout << "1)" << " " << "Sim"<<endl;
            cout <<"2)" << " " << "Não"<<endl;
            cin >> sair;
            switch(sair)
            {
                case 1: sair = 0;
                    break;
                case 2: sair = 1;
                    break;
            }
        }
    }



    if(sair == 0)
    {
        system("cls");
        return;
    }
    return;


}


void  deletarAresta(grafo *Teste2)
{

    system("cls");
    int voltar = 0,id1,id2,peso,sair = 1;
    bool verifica;

    while(sair!=0){
        cout << "Digite primeiro id onde uma arestasera sera deletada"<<endl;
        cin >> id1;
        cout << "Digite segundo id onde uma aresta sera deletada entre o primeiro e o segundo id digitados"<<endl;
        cin >> id2;
        cout << "Digite o peso do id que sera deletado"<<endl;
        cin >> peso;
        verifica = Teste2->verificaIdExiste(id1);
        if(verifica == true)
        {
            Teste2->deletarAresta(id1,id2,peso);
            cout << "O id passado foi deletado";
            cout << "Deseja sair:"<<endl;
            cout << "1)" << " " << "Sim"<<endl;
            cout <<"2)" << " " << "Nгo"<<endl;
            cin >> sair;
            switch(sair)
            {
                case 1: sair = 0;
                    break;
                case 2: sair = 1;
                    break;
            }
        }
        else
        {
            cout << "O id passado não existe ou ja foi deletado";
            cout << "Deseja sair:"<<endl;
            cout << "1)" << " " << "Sim"<<endl;
            cout <<"2)" << " " << "Não"<<endl;
            cin >> sair;
            switch(sair)
            {
                case 1: sair = 0;
                    break;
                case 2: sair = 1;
                    break;
            }
        }
    }



    if(sair == 0)
    {
        system("cls");
        return;
    }
    return;

}

void   criarAresta(grafo *Teste2)
{

    system("cls");
    int voltar = 0,id1,id2,peso,sair = 1;
    bool verifica;

    while(sair!=0){
        cout << "Digite primeiro id onde uma aresta sera criada"<<endl;
        cin >> id1;
        cout << "Digite segundo id onde uma aresta sera criada entre o primeiro e o segundo id digitados "<<endl;
        cin >> id2;
        cout << "Digite o pese desta aresta"<<endl;
        cin >> peso;
        verifica = Teste2->verificaIdExiste(id1);
        if(verifica == true)
        {
            Teste2->criarAresta(id1,id2,peso);
            cout << "A aresta foi criada";
            cout << "Deseja sair:"<<endl;
            cout << "1)" << " " << "Sim"<<endl;
            cout <<"2)" << " " << "Nгo"<<endl;
            cin >> sair;
            switch(sair)
            {
                case 1: sair = 0;
                    break;
                case 2: sair = 1;
                    break;
            }
        }
        else
        {
            cout << "O id passado não existe ou ja foi deletado";
            cout << "Deseja sair:"<<endl;
            cout << "1)" << " " << "Sim"<<endl;
            cout <<"2)" << " " << "Não"<<endl;
            cin >> sair;
            switch(sair)
            {
                case 1: sair = 0;
                    break;
                case 2: sair = 1;
                    break;
            }
        }
    }



    if(sair == 0)
    {
        system("cls");
        return;
    }
    return;
}

void obterGrauVertice(grafo *Teste2)
{

    system("cls");
    int voltar = 0,id,sair = 1;
    bool verifica;

    while(sair!=0){
        cout << "Digite um id"<<endl;
        cin >> id;
        verifica = Teste2->verificaIdExiste(id);
        if(verifica == true)
        {
            int grau = Teste2->obterGrau(id);
            cout << "Grau do vertice"<<" "<<grau;
            cout << "Deseja sair:"<<endl;
            cout << "1)" << " " << "Sim"<<endl;
            cout <<"2)" << " " << "Nгo"<<endl;
            cin >> sair;
            switch(sair)
            {
                case 1: sair = 0;
                    break;
                case 2: sair = 1;
                    break;
            }
        }
        else
        {
            cout << "O id passado não existe ou ja foi deletado";
            cout << "Deseja sair:"<<endl;
            cout << "1)" << " " << "Sim"<<endl;
            cout <<"2)" << " " << "Não"<<endl;
            cin >> sair;
            switch(sair)
            {
                case 1: sair = 0;
                    break;
                case 2: sair = 1;
                    break;
            }
        }
    }



    if(sair == 0)
    {
        system("cls");
        return;
    }
    return;




}

void obterGrauGrafo(grafo *Teste2) {
    system("cls");
    int grau = Teste2->obterGrauGrafo();
    cout << "Grau do grafo: "<<grau<<endl;

    int sair = 1;
    while(sair!=0){
        cout << "Deseja sair?:"<<endl;
        cout << "1)" << " " << "Sim"<<endl;
        cout <<"2)" << " " << "Nao"<<endl;
        cin >> sair;
        switch(sair)
        {
            case 1: sair = 0;
                break;
            case 2: sair = 1;
                break;
        }
    }
}

void verificarKRegular(grafo *Teste2) {
    system("cls");
    cout << "Digite o K: "<<endl;
    int k;
    cin >> k;
    if(Teste2->verificaRegular(k)){
        cout << "O Grafo eh "<<k<<" regular.";
    } else {
        cout << "O Grafo nao eh "<<k<<" regular.";
    }

    int sair = 1;
    while(sair != 0){
        cout << "Deseja sair?:"<<endl;
        cout << "1)" << " " << "Sim"<<endl;
        cout <<"2)" << " " << "Nao"<<endl;
        cin >> sair;
        switch(sair)
        {
            case 1: sair = 0;
                break;
            case 2: sair = 1;
                break;
        }
    }
}


void informarGrau(grafo *Teste2) {
    cout << "A ordem do Grafo eh "<< Teste2->getTamanho() -1 <<endl;
    int sair = 1;
    while(sair != 0){
        cout << "Deseja sair?:"<<endl;
        cout << "1)" << " " << "Sim"<<endl;
        cout <<"2)" << " " << "Nao"<<endl;
        cin >> sair;
        switch(sair)
        {
            case 1: sair = 0;
                break;
            case 2: sair = 1;
                break;
        }
    }
}

void isTrivial(grafo *Teste2) {
    if(Teste2->verificaTrivial()){
        cout << "O Grafo eh trivial.";
    } else {
        cout << "O Grafo nao eh trivial.";
    }

    int sair = 1;
    while(sair != 0){
        cout << "Deseja sair?:"<<endl;
        cout << "1)" << " " << "Sim"<<endl;
        cout <<"2)" << " " << "Nao"<<endl;
        cin >> sair;
        switch(sair)
        {
            case 1: sair = 0;
                break;
            case 2: sair = 1;
                break;
        }
    }
}

void isNulo(grafo *Teste2) {
    if(Teste2->verificaNulo()){
        cout << "O Grafo eh nulo.";
    } else {
        cout << "O Grafo nao eh nulo.";
    }

    int sair = 1;
    while(sair != 0){
        cout << "Deseja sair?:"<<endl;
        cout << "1)" << " " << "Sim"<<endl;
        cout <<"2)" << " " << "Nao"<<endl;
        cin >> sair;
        switch(sair)
        {
            case 1: sair = 0;
                break;
            case 2: sair = 1;
                break;
        }
    }
}

void calcularCaminho(grafo *Teste2) {
    system("cls");
    cout << "Qual algoritmo usar?:"<<endl;
    cout << "1)" << " " << "Dijkstra"<<endl;
    cout <<"2)" << " " << "Floyd"<<endl;
    int algoritmo;
    cin >> algoritmo;
    Teste2->calcularCaminho(algoritmo);

    int sair = 1;
    while(sair != 0){
        cout << "Deseja sair?:"<<endl;
        cout << "1)" << " " << "Sim"<<endl;
        cout <<"2)" << " " << "Nao"<<endl;
        cin >> sair;
        switch(sair)
        {
            case 1: sair = 0;
                break;
            case 2: sair = 1;
                break;
        }
    }
}

void calcularFechoDireto(grafo *Teste2) {
    system("cls");
    cout << "Informe o numero do no1:"<<endl;
    int no1;
    cin >> no1;
    int no2;
    cin >> no1;
    Teste2->fechoTransitivoDireto(no1, no2);

    int sair = 1;
    while(sair != 0){
        cout << "Deseja sair?:"<<endl;
        cout << "1)" << " " << "Sim"<<endl;
        cout <<"2)" << " " << "Nao"<<endl;
        cin >> sair;
        switch(sair)
        {
            case 1: sair = 0;
                break;
            case 2: sair = 1;
                break;
        }
    }
}

void calcularFechoIndireto(grafo *Teste2) {
    system("cls");
    cout << "Informe o numero do no1:"<<endl;
    int no1;
    cin >> no1;
    Teste2->fechoTransitivoIndireto(no1);

    int sair = 1;
    while(sair != 0){
        cout << "Deseja sair?:"<<endl;
        cout << "1)" << " " << "Sim"<<endl;
        cout <<"2)" << " " << "Nao"<<endl;
        cin >> sair;
        switch(sair)
        {
            case 1: sair = 0;
                break;
            case 2: sair = 1;
                break;
        }
    }
}

void imprimirSequenciaGraus(grafo *Teste2) {
    cout << "A sequencia de Graus eh:" << endl;
    Teste2->getSequenciaGraus(); //Imprime a sequencia de graus do grafo
    int sair = 1;
    while(sair != 0){
        cout << "Deseja sair?:"<<endl;
        cout << "1)" << " " << "Sim"<<endl;
        cout <<"2)" << " " << "Nao"<<endl;
        cin >> sair;
        switch(sair)
        {
            case 1: sair = 0;
                break;
            case 2: sair = 1;
                break;
        }
    }
}

void getSubgrafoInduzido(grafo *Teste2) {
    cout << "Digite os vertices. -1 para parar." << endl;
    int c = 0;
    list<int> vertices;
    while(c!=-1){
        cin >> c;
        vertices.push_back(c);
    }
    Teste2->getSubgrafoInduzido(vertices); //Imprime o subgrafo induzido
    int sair = 1;
    while(sair != 0){
        cout << "Deseja sair?:"<<endl;
        cout << "1)" << " " << "Sim"<<endl;
        cout <<"2)" << " " << "Nao"<<endl;
        cin >> sair;
        switch(sair)
        {
            case 1: sair = 0;
                break;
            case 2: sair = 1;
                break;
        }
    }
}

void getGrafoComplementar(grafo *Teste2) {
    cout << "O grafo complementar eh:" << endl;
    Teste2->getComplementar(); //Imprime o grafo complementar do grafo lido
    int sair = 1;
    while(sair != 0){
        cout << "Deseja sair?:"<<endl;
        cout << "1)" << " " << "Sim"<<endl;
        cout <<"2)" << " " << "Nao"<<endl;
        cin >> sair;
        switch(sair)
        {
            case 1: sair = 0;
                break;
            case 2: sair = 1;
                break;
        }
    }
}
void getComponentes(grafo *Teste2) {
    cout << "As componentes são:" << endl;
    Teste2->getComponentes(); //
    int sair = 1;
    while(sair != 0){
        cout << "Deseja sair?:"<<endl;
        cout << "1)" << " " << "Sim"<<endl;
        cout <<"2)" << " " << "Nao"<<endl;
        cin >> sair;
        switch(sair)
        {
            case 1: sair = 0;
                break;
            case 2: sair = 1;
                break;
        }
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
    cout << "\t *10)" << " " << "Consultar se o grafo eh trivial"<< endl;
    cout << "\t *11)" << " " << "Consultar se o grafo eh nulo"<< endl;
    cout << "\t *12)" << " " << "Calcular caminho minimo"<< endl;
    cout << "\t *13)" << " " << "Calcular fecho trasitivo direto de um no"<< endl;
    cout << "\t *14)" << " " << "Calcular fecho trasitivo indireto de um no"<< endl;
    cout << "\t *15)" << " " << "Imprimir sequencia de graus"<< endl;
    cout << "\t *16)" << " " << "Calcular subgrafo induzido"<< endl;
    cout << "\t *17)" << " " << "Imprimir o grafo complementar"<< endl;
    cout << "\t *18)" << " " << "Imprimir componentes fortemente conexas"<< endl;
    cout << "\t 0)"  << " " << "Sair"<<endl;
}



int main()
{
    ifstream txtFile;
    int i,vetor[3],c, direcionado,escolhas = 1;
    string nome;

    cout << "Digitar o texto que se quer abrir: " << endl;
    cin >> nome;
    cout << endl << "O grafo eh direcionado?"  <<endl;
    cout << "1)" << " " << "Sim"<<endl;
    cout << "0)" << " " << "Nao"<<endl;
    cin >> direcionado;
    cout << endl;
    txtFile.open(nome.c_str());

    txtFile >> c;

    grafo Teste1(c, direcionado);
    //cout << "vertices" << c;

    while(!txtFile.eof())
    {
        i = 0;
        while(i!=3){
            txtFile >> c;
            vetor[i] = c;
            //cout << "arestas" <<" "<<i<<" "<< c;
            i++;
            if(i == 3)
            {
                // cout << "criou vertice";
                Teste1.criarAresta(vetor[0],vetor[1],vetor[2]);
                if(direcionado == 0)
                    Teste1.criarAresta(vetor[1],vetor[0],vetor[2]);
                //cout << vetor[j];

            }
        }
    }
    txtFile.close();




    while(escolhas !=0){


        menu();
        cin >> escolhas;
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
            case 0:
                escolhas = 0;
                break;
        }
    }
}
