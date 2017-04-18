#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
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


void menu()
{
        cout << endl << endl << "\t\t\t ---MENU PRINCIPAL---" << endl << endl;
        cout << "\t Escolha uma opção:" << endl;
        cout << "\t 1)" << " " << "Crirar vertice"<< endl;
        cout << "\t 2)" << " " << "Verificar se vertice existe"<< endl;
        cout << "\t 3)" << " " << "Deletar vertice"<< endl;
        cout << "\t 4)" << " " << "Deletar aresta"<< endl;
        cout << "\t 5)" << " " << "Criar aresta"<< endl;
        cout << "\t 6)" << " " << "Obter grau vertice"<< endl;
        cout << "\t 7)" << " " << "Obter grau grafo"<< endl;
        cout << "\t 8)" << " " << "Verificar se o vertice x й adjacente ao vertice y"<< endl;
        cout << "\t 9)" << " " << "Listar adjacenstes de um vertice"<< endl;
        cout << "\t 10)" << " " << "Verificar se o grafo й regular"<< endl;
        cout << "\t 11)" << " " << "Verificar se o grafo й completo"<< endl;
        cout << "\t 12)" << " " << "Verificar se o grafo й conexo"<< endl;
        cout << "\t 13)" << " " << "Verificar se a aresta й ponte"<< endl;
        cout << "\t 14)" << " " << "Verificar o numero de componentes conexas"<< endl;
        cout << "\t 15)" << " " << "Verificar se o grafo й bipartido"<< endl;
        cout << "\t 16)" << " " << "Verificar se o grafo й bipartido"<< endl;
        cout << "\t 0)"  << " " << "Sair"<<endl;
}



int main()
{
    ifstream txtFile;
    int i,vetor[3],c, direcionado,escolhas = 1;
    string nome;

       cout << "Digitar o texto que se quer abrir: " << endl;
       cin >> nome;
       cout << endl << "O grafo e direcionado?"  <<endl;
       cout << "1)" << " " << "Sim"<<endl;
       cout << "0)" << " " << "Nao"<<endl;
       cin >> direcionado;
       cout << endl;
    txtFile.open(nome);

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
    case 0:
        escolhas = 0;
        break;
        }
    }
}
