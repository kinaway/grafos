#include "grafos.h"
#include <limits>
#include <fstream>
//FunÁ„o cria um grafo passando a quantida de vertices que se deseja
grafo::grafo(int tam, int direcionado)
{

    lista_vertices = new lista_adjacencia();// … criado um vetor de lista;
    this->direcionado = direcionado;
}

//Função que retorna a lista de adjacência do nó no
list<pair<int, int> >* grafo::getAdj(int no){
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        if(it->first == no)
            return &(it->second);
    }
    return NULL;
}


//Verifica se o id passado existe no grafo
bool grafo::verificaIdExiste(int id)
{
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        if(it->first == id){ //primeiro elemento do pair é o id do vertice.
            return true;
        }
    }
    return false;
}

// FunÁ„o cria uma aresta passando os vertices que se deseja "ligar" e o peso desta "ligaÁ„o"
void grafo::criarAresta(int vet1, int vet2,int peso)
{
    if(verificaIdExiste(vet1))//verifica se o id passo e valido
    {
        if(verificaIdExiste(vet2))
        {
            pair<int, int> aresta = make_pair(vet2,peso);//Um tipo pair aresta È criado recebendo o peso da aresta e um vertice vet2;
            list<pair<int, int> >* adj = getAdj(vet1);
            adj->push_back(aresta); //inclui nova aresta nos adjacentes do vet1
        }
        else
            cout<<"O segundo id passado nao existe  ou foi deletado favor escolher outro: " << vet2;
    }
    else
        cout<<"O primeiro id passado nao existe ou foi deletado favor escolher outro: " << vet1;
}

// Função criar arestas
grafo grafo::copiarGrafo(){

    grafo copia(lista_vertices->size(), direcionado);

    // cria vértices
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        if(!copia.verificaIdExiste(it->first)){
            copia.criarVertice(it->first);
        }
    }

    // criar adjacencias
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        int vet1 = it->first;
        for(list<pair<int, int> >::iterator it2 = it->second.begin(); it2!=it->second.end(); it2++){//percorre adjs de it->first
            int vet2 = it2->first;
            int peso = it2->second;
            copia.criarAresta(vet1, vet2, peso);
        }
    }

    return copia;
}

// FunÁ„o adiciona um vertice no grafo
void grafo::criarVertice(int id)
{
    pair<int, list<pair<int, int> > > vertice = make_pair(id, list<pair<int, int> >());
    lista_vertices->push_back(vertice);
}

// FunÁ„o obtem o grau de um vertice;
int grafo::obterGrau(int id)
{
    return getAdj(id)->size(); //retorna tamanho da lista de adj de no. id verificado se existe anteriormente.
}

//Obtem o grau total do grafo
int grafo::obterGrauGrafo()
{
    int tam = 0;
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        if(tam < it->second.size()){
            tam = it->second.size();
        }
    }
    return tam;
}


//Retorna os elementos que possuem vertice com o id1
void grafo::listarAdjacentes(int id1)
{
    if(verificaIdExiste(id1)) //Verifica se o id passado existe no grafo
    {
        cout << "Vertices adjacentes : " << endl;
        list<pair<int, int> >* adj = getAdj(id1);
        for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){
            cout << it->first << endl;
        }
    }
    else
        cout<<"O id passado nao existe ou foi deletado favor escolher outro";
}

//Verifica se o grafo È k regular
bool grafo::verificaRegular(int regular)
{

    if(regular >= lista_vertices->size())
    {
        for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++) //percorre toda lista
        {
            if(it->second.size() != regular)//Verifica se o grau passado È diferente do grau do vertice
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
    /*for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++) //percorre toda lista
    {
        for(list<pair<int, int> >::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){//it->second é lista de adj do nó
            int id1 = it2->first;
            if(id == it->first || id == id1 )
            {

                lista.push_back(make_pair(it->first,make_pair(it2->first, it2->second)));

            }

        }
    }*/

    grafo copia = copiarGrafo();

    copia.deletarVertice(id);
    //int temp2 = G.numeroComponeteconexo();
    /*criarVertice(id);
    for(list<pair<int, pair<int, int> > >::iterator it = lista.begin(); it != lista.end(); it++){
        criarAresta(it->first,it->second.first, it->second.second);
    }*/
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

    return verificaRegular(lista_vertices->size()-1);//Passa o quantidade de vertices como parametro para a funÁ„o
}

// Realiza uma busca em profundidade comenÁando a busca apartir do id
int* grafo::buscaProfundidade(int id)
{
    if(verificaIdExiste(id)) //Verifica se o id passado existe no grafo
    {

        int *vetor = new int[lista_vertices->size()] ;// Um ponteiro de int È criado

        for(int i=1; i < lista_vertices->size(); i++)
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
        list<pair<int, int> >*  adj = getAdj(id);
        for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++)//Percorre a lista referente ao id1 pegando cada parametro da lista e colocando-o na variavel pair a
        {

            auxbuscaProfundidade(vetor,it->first,j);//A funcao se chama, fazendo um metodo recursivo,atualizando os parametros da funcao

        }
    }
}

bool grafo::verificaArestaPonte(int id1, int id2)
{

    pair<int, int> *b;
    list<pair<int, int> >* adj = getAdj(id1);
    for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){

        if (it->first == id2)
        {
            //b = it ;
        }
    }
    adj = getAdj(id2);
    for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){

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

    for(int i=1; i<lista_vertices->size(); i++)
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

    for(int i=1; i<lista_vertices->size(); i++)
    {
        if(vetor[i] == 0)//Percorre todo o vetor em busca de algum espaÁo igual a 0
        {

            auxbuscaProfundidade(vetor,i,j);////A funÁ„o auxbuscaProfundidade È chamada comeÁando sua busca apartir do vertice que n„o foi visitado.
            j++;
        }
    }
    return vetor[lista_vertices->size()-1];//Retorna a ultima posiÁao do vetor;
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
        list<pair<int, int> >* adj = getAdj(id);
        for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){//Percorre a lista referente ao id1 pegando cada parametro da lista e colocando-o na variavel pair a
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
        int *vetorBipartido = new int[lista_vertices->size()] ;

        for(int i=1; i < lista_vertices->size(); i++)
        {
            vetorBipartido[i] = 0;//Inicializa todos os valores do vetor com 0;
        }


        int j = 2;

        int id2 = 0;

        auxVerificaBipartido(vetorBipartido,id,&j,id2,&verifica);//Chama a funÁ„o que ira auxiliar a funÁ„o verificaBipartido, usando busca em profundidade

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
        for(lista_adjacencia::reverse_iterator it = lista_vertices->rbegin(); it != lista_vertices->rend(); it++){ //percorre toda lista
            if(it->first == id){ // deleta lista adj de id.
                lista_vertices->erase(--it.base());
                it++;
            } else {
                //deleta todas arestas até id
                for(list<pair<int, int> >::reverse_iterator it2 = it->second.rbegin(); it2!=it->second.rend(); it2++){//percorre adjs de it->first
                    if(it2->first == id){
                        it->second.erase(--it2.base());
                        it2++;
                    }
                }
            }
        }
    } else
        cout<<"O  id passado nao existe ou ja foi deletado favor escolher outro"<<endl;
}

//FunÁ„o deleta uma aresta entre dois vertices
void grafo::deletarAresta(int id,int id2, int peso)
{
    if(verificaIdExiste(id)) //Verifica se o id passado existe no grafo
    {
        if(verificaIdExiste(id2)) //Verifica se o id passado existe no grafo
        {
            list<pair<int, int> >* adj = getAdj(id);
            for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){//Percorre a lista referente ao id1 pegando cada parametro da lista e colocando-o na variavel pair a
                if(it->first == id2 && it->second == peso)//Verifica se o id e o peso da aresta que se deseja remover s„o iguais aos passados como parametro
                {
                    adj->remove(*it);//A aresta desejada È removida
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
grafo grafo::grafoTransposto()
{

    grafo grafoTransposto(0, this->direcionado);//cria um novo grafo
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        grafoTransposto.criarVertice(it->first);
        list<pair<int, int> >* adj = getAdj(it->first);
        for(list<pair<int, int> >::iterator it2 = adj->begin(); it2 != adj->end(); it2++){//Percorre a lista referente ao id1 pegando cada parametro da lista e colocando-o na variavel pair a
            grafoTransposto.criarAresta(it2->first, it->first, 0);//Criar aresta com o sentido inverso ao do vertive com id igual a K,ou seja, pega a o adjacente de k e cirar uma aresta entre o vertice k e o seu adjacente
        }
    }
    return grafoTransposto;//retorna o grafo criado;
}






int* grafo::auxbuscaProfundidadeTransitivo(int* vetor3,int id1,int id2,int* j)
{
    if(vetor3[id1] == 0)
    {
        vetor3[id1] = *j;//Coloca um valor diferente de zero indicando que o vertice igual ao id ja foi consultado;
        list<pair<int, int> >* adj = getAdj(id1);
        for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){//Percorre a lista referente ao id1 pegando cada parametro da lista e colocando-o na variavel pair a
            //{
            if(it->first == id2)
            {
                *j = *j + 1;//altera j caso id seja encontrado
            }

            auxbuscaProfundidadeTransitivo(vetor3,it->first,id2,j);//A funÁ„o se chama, fazendo um metodo recursivo,atualizando os paramtros da funÁ„o

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
            int *vetor3 = new int[lista_vertices->size()] ;// Um vetor È criado

            for(int i=0; i < lista_vertices->size(); i++)
            {
                vetor3[i] = 0;//O vetor È inicializado com todos os seus parametros sendo igual a 0
            }

            int j = 1 ;

            auxbuscaProfundidadeTransitivo(vetor3,id1,id2,&j);//A funÁ„o auxbuscaProfundidade È chamada passando como parametro um vetor e duas variaveis, sendo que os trÍs parametros s„o inteiros

            if(j != 1) //verifica se o j foi alterado, ou seja, se existe um ou mais caminhos entre o id1 e id2
            {
                for(int m=1; m<lista_vertices->size(); m++)
                {


                    if(m >= 1 && m<j)//verifica se o vetor possui um numero entre os intervalos de j, que È incrementado quando encontra o id passado na busca em profundidade
                    {
                        if(m != id1 && m != id2 )
                        {
                            cout << "Vertice" <<  m << endl;
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

    grafos2 = grafos2.grafoTransposto();//cria uma grafo Transposto
    grafos2.fechoTransitivoDireto(id2,id1);//Chama a funÁao que verifica o conjunto vertices que sao transitivos diretos

}

bool grafo::verificaTrivial(){

    if(lista_vertices->size() > 2)
    {
        return false;
    }
    else
    {
        if(obterGrau(lista_vertices->front().first) > 0)
        {
            return false;
        }
        else
        {
            return true;
        }



    }




    return false;
}

bool grafo::verificaNulo(){

    if(lista_vertices->size() > 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}


void grafo::calculaCaminhoDijkstra(int no1, int no2){
    bool incluidos[lista_vertices->size()]; //Lista de nós já incluídos no caminho mínimo até no1.
    long int dist[lista_vertices->size()]; //distância provisória de todos até no1
    list<int> caminho[lista_vertices->size()]; //uma lista para cada nó indicando o caminho até ele.
    for(int i = 0; i< lista_vertices->size(); i++){ //inicializa arrays
        dist[i] = numeric_limits<int>::max(); //infinito para todos valores
        incluidos[i] = false;
    }
    dist[no1] = 0;
    incluidos[no1] = true; //no1 já tem menor caminho encontrado
    list<pair<int, int> >* adj = getAdj(no1);
    for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){ //atualiza valores dos adj de no1
        dist[it->first] = it->second;
    }

    int no_aux = -1, min_aux = 0;
    while(no_aux != no2) { //para quando no2 for incluído
        min_aux = numeric_limits<int>::max();
        for(int i=0; i<lista_vertices->size(); i++){ //escolhe menor nó para entrar
            if(!incluidos[i] && dist[i] < min_aux){ //nó não incluido e com menor valor de distancia
                min_aux = dist[i];
                no_aux = i;
            }
        }
        if(min_aux == numeric_limits<int>::max()) {
            break; //caminho não encontrado.
        }
        incluidos[no_aux] = true; //inclui no_aux;
        adj = getAdj(no_aux);
        for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){ //atualiza valores dos adj de no_aux
            if(!incluidos[it->first] && dist[it->first] > dist[no_aux] + it->second){ //se adj ainda não foi incluído e tem distancia maior que a nova
                dist[it->first] = dist[no_aux] + it->second;
                caminho[it->first] = caminho[no_aux];
                caminho[it->first].push_back(no_aux); //novo caminho é caminho até no_aux mais no_aux;
            }
        }
    }
    if(min_aux != numeric_limits<int>::max()) { //caminho encontrado
        cout << "Valor do caminho calculado: " << dist[no2] << endl;
        cout << no1 << "->";
        for(list<int>::iterator it = caminho[no2].begin(); it != caminho[no2].end(); it++){
            cout << *it << "->";
        }
        cout << no2 << endl;
    } else {
        cout << "Caminho entre " << no1 << " e " << no2 << " não encontrado!" << endl;
    }
}

void grafo::calculaCaminhoFloyd(int no1, int no2){
    int tamanho = lista_vertices->size();
    long int dist[tamanho][tamanho]; //matriz contendo as distâncias de i a j;
    list<int> *caminho[tamanho]; //para cada ij, uma lista indicando o caminho entre eles.
    list<pair<int, int> >* adj;
    for(int i=0;i<tamanho;i++){
        caminho[i] = new list<int>[tamanho];
        for(int j=0;j<tamanho;j++){
            if(i==j){
                dist[i][j] = 0;
            } else {
                dist[i][j] = numeric_limits<int>::max();//dist começa com infinito.
            }
        }
        adj = getAdj(i);
        for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){
            //atualiza todos adj de i;
            dist[i][it->first] = it->second;
        }
    }

    for(int k=0;k<tamanho;k++){
        for(int i=0;i<tamanho;i++){
            for(int j=0;j<tamanho;j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    caminho[i][j] = caminho[i][k];
                    caminho[i][j].push_back(k); //caminho de ij passa a ser caminho de i a k mais k mais caminho de k a j;
                    caminho[i][j].insert(caminho[i][j].end(), caminho[k][j].begin(), caminho[k][j].end());
                }
            }
        }
    }
    if(dist[no1][no2] == numeric_limits<int>::max()){
        cout << "Caminho não encontrado!";
    } else {
        cout << "Valor do caminho calculado: " << dist[no1][no2] << endl;
        cout << no1 << "->";
        for(list<int>::iterator it = caminho[no1][no2].begin(); it != caminho[no1][no2].end(); it++){
            cout << *it << "->";
        }
        cout << no2 << endl;
    }
}
void grafo::calcularCaminho(int no1, int no2, int algoritmo){
    //algoritmo define se define o caminho por Floyd(2) ou por Dijkstra(1)
    if(algoritmo == 1) {
        calculaCaminhoDijkstra(no1, no2);
    } else if(algoritmo == 2){
        calculaCaminhoFloyd(no1, no2);
    } else {
        cout << "Algoritmo escolhido inválido." << endl;
    }
}

int grafo::getTamanho(){
    return lista_vertices->size();
}

void grafo::fechoTransitivoIndireto(int id1){

}

void grafo::getSequenciaGraus(){

    int grau;
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++)
    {
        grau = obterGrau(it->first);
        cout << "Vertice " << it->first <<": " << grau << " grau(s)"<< endl;
    }







}

void grafo::getSubgrafoInduzido(list<int> vertices){

}

void grafo::getComplementar(){
    grafo *grafo_aux = new grafo(lista_vertices->size(), direcionado);
    list<pair<int, int> >* adj;
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        if(!grafo_aux->verificaIdExiste(it->first)){
            grafo_aux->criarVertice(it->first);
        }
        for(lista_adjacencia::iterator it2 = lista_vertices->begin(); it2 != lista_vertices->end(); it2++){ //cria um grafo completo com todos vertices do grafo.
            if(!grafo_aux->verificaIdExiste(it2->first)){
                grafo_aux->criarVertice(it2->first);
            }
            if(it->first != it2->first){
                grafo_aux->criarAresta(it->first, it2->first, 0); //uma aresta para todo par de vertice.
            }
        }

        //percorre arestas que saem de it->first e exclui elas do grafo completo grafo_aux
        adj = getAdj(it->first);
        for(list<pair<int, int> >::iterator it2 = adj->begin(); it2 != adj->end(); it2++){
            grafo_aux->deletarAresta(it->first, it2->first, 0); //exclui as arestas
        }
    }
    //sobra grafo complementar.

    //imprime grafo no arquivo
    grafo_aux->imprimirGrafo();

}

void grafo::getComponentes(){

}

bool grafo::verificaEuriliano(){
    return false;
}

void grafo::getArticulacoes(){

    for(lista_adjacencia::reverse_iterator it = lista_vertices->rbegin(); it != lista_vertices->rend(); it++){

        if(verificaVerticeArticulacao(it->first)){
            cout << it->first << endl;

        }
    }

}

void grafo::getPontes(){

}

void grafo::getRaioDiametroCentroPeriferia(){

}

void grafo::getAGM(){

}

void grafo::imprimirGrafo() {
    cout << lista_vertices->size();
    list<pair<int,int> >* adj;
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        adj = getAdj(it->first);
        for(list<pair<int, int> >::iterator it2 = adj->begin(); it2 != adj->end(); it2++){
            cout << endl;
            cout <<it->first << " " << it2->first << " " << it2->second;
        }
    }
}

void grafo::salvarArquivo(ofstream& arquivo) {
    arquivo << lista_vertices->size();
    list<pair<int,int> >* adj;
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        adj = getAdj(it->first);
        for(list<pair<int, int> >::iterator it2 = adj->begin(); it2 != adj->end(); it2++){
            arquivo << endl;
            arquivo << it->first << " " << it2->first << " " << it2->second;
        }
    }
}

grafo::~grafo()
{
    //dtor
}
