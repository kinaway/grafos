#include "grafos.h"

//FunÁ„o cria um grafo passando a quantida de vertices que se deseja
grafo::grafo(int tam, int direcionado)
{
    tamanho = tam+1;// Varaivel È inicializada  o parametro passado pelo usuario
    vetor = new int [tamanho];// criar um vetor com o tamanho do grafo
    adj = new list<pair<int, int> >[tamanho];// … criado um vetor de lista;
    this->direcionado = direcionado;
    for(int i=1;i<tamanho;i++)// Percorre toda a extenÁao do vetor
    {
        vetor[i] = i;// vetor recebe o posicao i;
    }
    
}

// mapea o vetor de listas para que o id deletado nao seja acessado novamente
void grafo::mapaVerticedeletar(int id)
{
    for(int i=id;i<tamanho;i++)//percorre toda a estenÁ„o do id
    {
        if(id == i)//id passado e igual a posiÁ„o i
        {
            vetor[i] = - 1;// vetor nesta poiÁao recebe -1;
        }
        else
        {
            
            vetor[i] = vetor[i] - 1;//as posiÁıes a frente do vetor na posiÁ„o i reecebem seu valor subtraido de 1
        }
    }
    
    
}

void grafo::mapaVerticecriar()
{
    vetor = new int[tamanho];//aumenta o tamanho do vetor casa o tamanho do grafo seja modificado pela funÁ„o  "void criarVertice()"
}

//Verifica se o id passado existe no grafo
bool grafo::verificaIdExiste(int id)
{
    
    
    
    if(id>=tamanho || id < 0)// caso seja maior que o tamanho retorna falso
    {
        return false;
    }
    if(vetor[id] < 0)// caso a valor da posiÁ„o id seja menor que 0 retorna falso
    {
        return false;
    }
    else// caso um das duas condiÁıes acima venham a falhar retorna verdadeiro
    {
        return true;
    }
    
    
    
}

// FunÁ„o cria uma aresta passando os vertices que se deseja "ligar" e o peso desta "ligaÁ„o"
void grafo::criarAresta(int vet1, int vet2,int peso)
{
    if(verificaIdExiste(vet1))//verifica se o id passo e valido
    {
        if(verificaIdExiste(vet2))
        {
            
            pair<int, int> aresta = make_pair(vet2,peso);//Um tipo pair aresta È criado recebendo o peso da aresta e um vertice vet2;
            
            adj[vetor[vet1]].push_back(aresta);//A aresta entre o id referente na posiÁ„o vetor[vet1] È aresta e criado;
        }
        else
            cout<<"O segundo id passado nao existe  ou foi deletado favor escolher outro: " << vet2;
    }
    else
        cout<<"O primeiro id passado nao existe ou foi deletado favor escolher outro: " << vet1;
}

// FunÁ„o adiciona um vertice no grafo
void grafo::criarVertice()
{
    
    list<pair<int, int> > *adj2 = new list<pair<int, int> >[tamanho+1];// Uma lista adjacente È criado com o tamanho acrescentado de mais um
    
    int j=1;
    
    for(int i=1; i<tamanho; i++)
    {
        adj2[i] = adj[j];// Todos os parametrso do adj sao copiado para adj2
        
        j++;
    }
    
    tamanho = tamanho+1;//Variavel tamanho e atualizada;
    mapaVerticecriar();
    adj = adj2;// Variavel adj È atualizada
}

// FunÁ„o obtem o grau de um vertice;
int grafo::obterGrau(int id)
{
    
    if(verificaIdExiste(id))//Verifica se o id passado existe no grafo
        return adj[vetor[id]].size();// Retorna o tamanho da lista referente ao veritice id;
    else
        cout<<"O id passado nao existe ou foi deletado favor escolher outro";
    return 0;
}

//Obtem o grau total do grafo
int grafo::obterGrauGrafo()
{
    int tam = 0;
    
    for(int i = 1; i<tamanho; i++)//Usado para percorrer todos os vertices do grafo
    {
        int tam2 = adj[vetor[i]].size();//Retorna o tamanho da lista referente ao veritice id;
        
        if(tamanho == tam2)
        {
            return tam2;
        }
        
        if(tam2 > tam )//Atualiza tam com o maior grau encontrado
        {
            tam  = tam2;
        }
        
    }
    
    return tam;//Retorna o grau do grafo
    
}

//Verifica se existe uma aresta entre id1 e id2
bool grafo::verificarVizinhanca(int id1,int id2)
{
    if(verificaIdExiste(id1)) //Verifica se o id passado existe no grafo
    {
        if(verificaIdExiste(id2)) //Verifica se o id passado existe no grafo
        {
            bool retorno = false;
            for(list<pair<int, int> >::iterator it = adj[vetor[id1]].begin(); it != adj[vetor[id1]].end(); it++){
                if(it->first == id2)
                    return true;
            }
            return false;
            /*for_each(adj[vetor[id1]].begin(),adj[vetor[id1]].end(),[&](pair<int, int> a)//Percorre a lista referente ao id1 pegando cada parametro da lista e colocando-o na variavel pair a, sendo que a posiÁ„o È atualizada de acordo com o valor do vetor[id1]
             {
             if(a.first == id2)//Verifica se o primeiro paramtro de a e igual ao id2
             {
             retorno=true;
             }
             });
             
             return retorno;*/
        }
        else
            cout<<"O segundo id passado nao existe ou foi deletado favor escolher outro";
    }
    else
        cout<<"O primeiro id passado nao existe ou foi deletado favor escolher outro";
    return false;
}

//Retorna os elementos que possuem vertice com o id1
void grafo::listarAdjacentes(int id1)
{
    if(verificaIdExiste(id1)) //Verifica se o id passado existe no grafo
    {
        cout << "Vertices adjacentes : " << endl;
        for(list<pair<int, int> >::iterator it = adj[vetor[id1]].begin(); it != adj[vetor[id1]].end(); it++){
            cout << it->first << endl;
        }
        /*for_each(adj[vetor[id1]].begin(),adj[vetor[id1]].end(),[&](pair<int, int> a)//Percorre a lista referente ao id1 pegando cada parametro da lista e colocando-o na variavel pair a
         {
         cout <<  a.first;
         });*/
    }
    else
        cout<<"O id passado nao existe ou foi deletado favor escolher outro";
}

//Verifica se o grafo È regular
bool grafo::verificaRegular(int regular)
{
    
    if(regular >=tamanho)
    {
        for(int i = 1; i<tamanho; i++)// Usado para percorrer todo o grafo
        {
            if(adj[i].size() != regular)//Verifica se o grau passado È diferente do grau do vertice
            {
                
                return false;
            }
        }
        
        return true;
    }
    else
        cout<< "O parametro passado eh irregular, favor escolher outro";
    return false;
}

bool grafo::verificaVerticeArticulacao(int id)
{
    
    list<pair<int,pair<int,int> > > lista;
    int comp1 = numeroComponeteconexo();
    for(int i = 0; i < tamanho; i++)
    {
        for(list<pair<int, int> >::iterator it = adj[i].begin(); it != adj[i].end(); it++){
            /*for_each(adj[i].begin(),adj[i].end(),[&](pair<int,int>a)
             {*/
            int id1 = it->first;
            if(id == i || id == id1 )
            {
                
                lista.push_back(make_pair(i,make_pair(it->first, it->second)));
                
                
                
                
                
            }
            
            
        }
    }
    
    deletarVertice(id);
    int temp2 = numeroComponeteconexo();
    for(list<pair<int, pair<int, int> > >::iterator it = lista.begin(); it != lista.end(); it++){
        criarAresta(it->first,it->second.first, it->second.second);
    }
    int comp2 = numeroComponeteconexo();
    if(comp2>comp1)
    {
        return true;
    }
    else
        return false;
    
}
//Verifica se o grafo È completo
bool grafo::verificarCompleto()
{
    
    return verificaRegular(tamanho-1);//Passa o quantidade de vertices como parametro para a funÁ„o
}

// Realiza uma busca em profundidade comenÁando a busca apartir do id
int* grafo::buscaProfundidade(int id)
{
    if(verificaIdExiste(id)) //Verifica se o id passado existe no grafo
    {
        
        int *vetor = new int[tamanho] ;// Um ponteiro de int È criado
        
        for(int i=1; i < tamanho; i++)
        {
            vetor[i] = 0;//O vetor È inicializado com todos os seus parametros sendo igual a 0
        }
        
        int j = 1 ;
        
        auxbuscaProfundidade(vetor,id,j);//A funÁ„o auxbuscaProfundidade È chamada passando como parametro um vetor e duas variaveis, sendo que os trÍs parametros s„o inteiros
        
        return vetor;
    }
    else
        cout<<"O  id passado nao existe favor escolher outro";
    
    return 0;
}
//FunÁao que realiza a busca em profundida
void grafo::auxbuscaProfundidade(int* vetor,int id,int j)
{
    
    if(vetor[id] == 0)
    {
        vetor[id] = j;//Coloca um valor diferente de zero indicando que o vertice igual ao id ja foi consultado;
        for(list<pair<int, int> >::iterator it = adj[id].begin(); it != adj[id].end(); it++)
            //for_each(adj[id].begin(),adj[id].end(),[&](pair<int, int> a)//Percorre a lista referente ao id1 pegando cada parametro da lista e colocando-o na variavel pair a
        {
            
            auxbuscaProfundidade(vetor,it->first,j);//A funcao se chama, fazendo um metodo recursivo,atualizando os parametros da funcao
            
        }
    }
}

bool grafo::verificaArestaPonte(int id1, int id2)
{
    
    pair<int, int> *b;
    for(list<pair<int, int> >::iterator it = adj[id1].begin(); it != adj[id1].end(); it++){
        
        if (it->first == id2)
        {
            //b = it ;
        }
    }
    for(list<pair<int, int> >::iterator it = adj[id2].begin(); it != adj[id2].end(); it++){
        
        if ( it->first== id2)
        {
            // b = &it;
        }
    }
    return false;
}
//Verifica se o grafo È conexo
bool grafo::verificaConexo()
{
    int* vetor = buscaProfundidade(1);//Variavel vetor ira receber o vetor retornado pela funÁ„o buscaProfundidade;
    
    for(int i=1; i<tamanho; i++)
    {
        if(vetor[i]==0)//Percorre todo o vetor em busca de algum espaÁo igual a 0
            return false;
    }
    
    return true;
}

//Verifica a quantidade de numeros conexos
int grafo::numeroComponeteconexo()
{
    int *vetor = buscaProfundidade(1);//Variavel vetor ira receber o vetor retornado pela funÁ„o buscaProfundidade;
    
    int j = 2;
    
    for(int i=1; i<tamanho; i++)
    {
        if(vetor[i] == 0)//Percorre todo o vetor em busca de algum espaÁo igual a 0
        {
            
            auxbuscaProfundidade(vetor,i,j);////A funÁ„o auxbuscaProfundidade È chamada comeÁando sua busca apartir do vertice que n„o foi visitado.
            j++;
        }
    }
    return vetor[tamanho-1];//Retorna a ultima posiÁao do vetor;
}
//
void grafo::auxVerificaBipartido(int *vetor2,int id,int *j,int id2,bool *verifica)
{
    if(vetor2[id] == 0)//Verifica se a posiÁ„o consultada do vetor2  È igual a zero
    {
        if(*j==2)//j e atualizado com 1 caso seu valor seja 2;
        {
            *j=1;
        }
        
        else//j e atualizado com 2 caso seu valor seja 1;
        {
            *j=2;
        }
        
        vetor2[id] = *j;
        for(list<pair<int, int> >::iterator it = adj[id].begin(); it != adj[id].end(); it++){
            //for_each(adj[id].begin(),adj[id].end(),[&](pair<int, int> a)//Percorre a lista referente ao id1 pegando cada parametro da lista e colocando-o na variavel pair a
            //{
            
            auxVerificaBipartido(vetor2,it->first,j,id,verifica);//A funÁ„o se chama, fazendo um metodo recursivo,atualizando os paramtros da funÁ„o
            
        }
    }
    else//Caso a posiÁao consultada do vetor2 nao seja igual a 0
    {
        if(vetor2[id] == vetor2[id2])//Verifica se o valor(1 ou 2) na posiÁao id1 e id2 sao iguais.
        {
            *verifica = false;//Atualiza o valor de verifica
            return;
        }
    }
}

// Vetifica se a funÁ„o È bipartida
bool grafo::verificaBipartido(int id)
{
    
    if(verificaIdExiste(id)) //Verifica se o id passado existe no grafo
    {
        bool verifica = true;
        int *vetorBipartido = new int[tamanho] ;
        
        for(int i=1; i < tamanho; i++)
        {
            vetorBipartido[i] = 0;//Inicializa todos os valores do vetor com 0;
        }
        
        
        int j = 2;
        
        int id2 = 0;
        
        auxVerificaBipartido(vetorBipartido,vetor[id],&j,vetor[id2],&verifica);//Chama a funÁ„o que ira auxiliar a funÁ„o verificaBipartido, usando busca em profundidade
        
        return verifica;
    }
    else
        cout<<"O  id passado nao existe  ou foi deletado favor escolher outro";
    
    return false;
}

//Deleta um vertice selecionado
void grafo::deletarVertice(int id)
{
    if(verificaIdExiste(id)) //Verifica se o id passado existe no grafo
    {
        list<pair<int, int> > *adj2 = new list<pair<int, int> >[tamanho-1];//Uma lista adjacente È criado com o tamanho acrescentado de mais um
        
        int j=1;
        mapaVerticedeletar(id);
        for(int i=1; i<tamanho; i++)
        {
            if(id !=i)
            {
                adj2[j] = adj[i];// Todos os parametrso do adj, com exeÁ„o do id, s„o copiado para adj2
                j++;
            }
        }
        
        tamanho = tamanho-1;//O tamanho È atualizado com seu revalor subtraido de um
        
        adj = adj2;//aj1 È atualizado com os valores de adj2
    }
    else
        cout<<"O  id passado nao existe ou ja foi deletado favor escolher outro"<<endl;
    
    
}

//FunÁ„o deleta uma aresta entre dois vertices
void grafo::deletarAresta(int id,int id2, int peso)
{
    if(verificaIdExiste(id)) //Verifica se o id passado existe no grafo
    {
        
        if(verificaIdExiste(id2)) //Verifica se o id passado existe no grafo
        {
            for(list<pair<int, int> >::iterator it = adj[id].begin(); it != adj[id].end(); it++){
                //for_each(adj[vetor[id]].begin(),adj[vetor[id]].end(),[&](pair<int, int> a)//Percorre a lista referente ao id1 pegando cada parametro da lista e colocando-o na variavel pair a
                //{
                if(it->first == id2 && it->second == peso)//Verifica se o id e o peso da aresta que se deseja remover s„o iguais aos passados como parametro
                {
                    adj[vetor[id]].remove(*it);//A aresta desejada È removida
                    return;
                }
            }
        }
        else
            cout<<"O segundo id passado nao existe ou foi deletado favor escolher outro";
    }
    else
        cout<<"O  primeiro id passado nao existe ou foi deletado favor escolher outro";
}


//Retorna um grafo transposto
grafo grafo::grafoTrasposto()
{
    
    grafo grafoTrasposto(tamanho, this->direcionado);//cria um novo grafo
    
    for(int k=1; k<tamanho; k++)
    {
        for(list<pair<int, int> >::iterator it = adj[k].begin(); it != adj[k].end(); it++){
            //for_each(adj[k].begin(),adj[k].end(),[&](pair<int, int> a)//Percorre a lista referente ao id1 pegando cada parametro da lista e colocando-o na variavel pair a
            //{
            
            grafoTrasposto.criarAresta(it->first,k,0);//Criar aresta com o sentido inverso ao do vertive com id igual a K,ou seja, pega a o adjacente de k e cirar uma aresta entre o vertice k e o seu adjacente
        }
    }
    
    return grafoTrasposto;//retorna o grafo criado;
}






int* grafo::auxbuscaProfundidadeTransitivo(int* vetor3,int id1,int id2,int* j)
{
    if(vetor3[id1] == 0)
    {
        vetor3[id1] = *j;//Coloca um valor diferente de zero indicando que o vertice igual ao id ja foi consultado;
        for(list<pair<int, int> >::iterator it = adj[vetor[id1]].begin(); it != adj[vetor[id1]].end(); it++){
            //for_each(adj[vetor[id1]].begin(),adj[vetor[id1]].end(),[&](pair<int, int> a)//Percorre a lista referente ao id1 pegando cada parametro da lista e colocando-o na variavel pair a
            //{
            if(it->first == id2)
            {
                *j = *j + 1;//altera j caso id seja encontrado
            }
            
            auxbuscaProfundidadeTransitivo(vetor3,vetor[it->first],vetor[id2],j);//A funÁ„o se chama, fazendo um metodo recursivo,atualizando os paramtros da funÁ„o
            
        }
    }
    
    return 0;
}
//Verifica o conjunto vertices que sao transitivos direto
void grafo::fechoTransitivoDireto(int id1,int id2)
{
    if(verificaIdExiste(id1)) //Verifica se o id passado existe no grafo
    {
        if(verificaIdExiste(id2)) //Verifica se o id passado existe no grafo
        {
            int *vetor3 = new int[tamanho] ;// Um vetor È criado
            
            for(int i=0; i < tamanho; i++)
            {
                vetor3[i] = 0;//O vetor È inicializado com todos os seus parametros sendo igual a 0
            }
            
            int j = 1 ;
            
            auxbuscaProfundidadeTransitivo(vetor,vetor[id1],vetor[id2],&j);//A funÁ„o auxbuscaProfundidade È chamada passando como parametro um vetor e duas variaveis, sendo que os trÍs parametros s„o inteiros
            
            if(j != 1) //verifica se o j foi alterado, ou seja, se existe um ou mais caminhos entre o id1 e id2
            {
                for(int m=1; m<tamanho; m++)
                {
                    
                    
                    if(vetor[m] >= 1 && vetor[m]<j)//verifica se o vetor possui um numero entre os intervalos de j, que È incrementado quando encontra o id passado na busca em profundidade
                    {
                        if(m != id1 && m != id2 )
                        {
                            cout << "Vertice" <<  vetor[m] << endl;
                        }
                    }
                    
                    
                }
                j=0;
            }
            else
                cout<<"Nao existe nenhum caminho, onde se possa sair de id1 e chager em id2";
            
        }
        else
            cout<<"O  id passado nao existe favor escolher outro";
        
    }
    else
        cout<<"O  id passado nao existe favor escolher outro";
    
}

// Verifica o conjunto vertices que sao transitivos indiretos
void grafo::fechoTransitivoIndireto(int id1,int id2, grafo grafos2)
{
    
    grafos2 = grafos2.grafoTrasposto();//cria uma grafo Transposto
    grafos2.fechoTransitivoDireto(vetor[id2],vetor[id1]);//Chama a funÁao que verifica o conjunto vertices que sao transitivos diretos
    
}

bool grafo::verificaTrivial(){
    return false;
}

bool grafo::verificaNulo(){
    return false;
}

void grafo::calcularCaminho(int algoritmo){
    
}

int grafo::getTamanho(){
    return tamanho;
}

void grafo::fechoTransitivoIndireto(int id1){
    
}

void grafo::getSequenciaGraus(){
    
}

void grafo::getSubgrafoInduzido(list<int> vertices){
    
}

void grafo::getComplementar(){
    
}

void grafo::getComponentes(){
    
}

bool grafo::verificaEuriliano(){
    return false;
}

void grafo::getArticulacoes(){
    
}

void grafo::getPontes(){
    
}

void grafo::getRaioDiametroCentroPeriferia(){
    
}

void grafo::getAGM(){
    
}

grafo::~grafo()
{
    //dtor
}
