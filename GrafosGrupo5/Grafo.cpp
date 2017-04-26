#include "Grafo.h"
#include <limits>
#include <fstream>
#include <queue>
//Construtor do grafo, orientação do grafo deve ser passada
Grafo::Grafo(int direcionado)
{
    this->direcionado = direcionado;
}

// Função para adicionar um vértice id no grafo
// retorna false em caso de falha
bool Grafo::criarVertice(int id)
{
    Vertice* v = getVertice(id);
    if(v == NULL){
        Vertice v(id);
        lista_vertices.push_back(v);
        return true;
    }
    else
        return false;
}

//Verifica se o id passado existe no grafo
// retorna false em caso de falha
bool Grafo::verificaIdExiste(int id)
{
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++){
        if(v->id == id){
            return true;
        }
    }
    return false;
}

//Deleta um vertice selecionado
// retorna false em caso de falha
bool Grafo::deletarVertice(int id)
{

     Vertice* v = getVertice(id);
     if(v != NULL){
        for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++){
            // encontrou o vértice id
            if(v->id == id){
                v = --lista_vertices.erase(v);

            }
            else{
                for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++){
                    cout << "-Aresta: " << a->id << ", peso: " << a->peso << endl;
                    if(a->id == id){
                        a = --v->lista_arestas.erase(a);
                    }
                }
            }
        }
        return true;
     }
     else
        return false;

}

//Função para deletar uma aresta entre dois vertices
// retorna false em caso de falha
bool Grafo::deletarAresta(int id,int id2, int peso)
{
    Vertice* v = getVertice(id);
    Vertice* u = getVertice(id2);
    bool found = false;

    if(v != NULL && u != NULL){

        // busca a aresta entre v e u e apaga
        for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++){
            if(a->id == id2 && a->peso == peso){
                a = --v->lista_arestas.erase(a);
                found = true;
                break;
            }
        }

        // se for não direcionado, apagamos a aresta entre u e v também
        if(direcionado == false && found == true){
            for(listaArestas::iterator a = u->lista_arestas.begin(); a != u->lista_arestas.end(); a++){
                if(a->id == id && a->peso == peso){
                    a = --u->lista_arestas.erase(a);
                    break;
                }
            }
        }
    }

    return found;
}

// Função para a criação de uma aresta entre u e v com peso p
// retorna false em caso de falha
bool Grafo::criarAresta(int u, int v, int p)
{
    Vertice* vertice_v = getVertice(u);
    Vertice* vertice_u = getVertice(v);

    // ambos vértices devem estar presentes no grafo
    if(vertice_v != NULL && vertice_u != NULL){
        vertice_v->adicionaAresta(v, p);
        return true;
    }
    else{
        return false;
    }
}

// Obtém o grau do grafo dado que ele é não-orientado
// retorna -1 em caso de falha
int Grafo::getGrau(int id)
{
    Vertice* v = getVertice(id);
    if(v == NULL || direcionado == true)
        return -1;

    return v->lista_arestas.size();
}

// Obtém o grau de entrada do grafo dado que ele é orientado
// retorna -1 em caso de falha
int Grafo::getGrauEntrada(int id){
    Vertice* v = getVertice(id);
    if(v == NULL || direcionado == false)
        return -1;

    int grau_entrada = 0;

    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++){
        for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++){
            if(a->id == id){
                grau_entrada += 1;
            }
        }
    }

    return grau_entrada;
}

// Obtém o grau de saída do grafo dado que ele é orientado
// retorna -1 em caso de falha
int Grafo::getGrauSaida(int id){
    Vertice* v = getVertice(id);
    if(v == NULL || direcionado == false)
        return -1;

    return v->lista_arestas.size();
}

//Obtem o grau do grafo
int Grafo::getGrauGrafo()
{
    int maior_grau = 0;
    if(direcionado == false){
        for(listaVertices::iterator v = lista_vertices.begin(); v!= lista_vertices.end(); v++){
            int grau = getGrau(v->id);
            if(grau > maior_grau)
                maior_grau = grau;
        }
    }
    else{
        cout << "Como o calcula grau de um grafo direcionado?? Adicione aqui!" << endl;
        return -1;
    }

    return maior_grau;
}


//Verifica se o grafo é k regular
bool Grafo::verificaRegular(int regular)
{
    if(regular >= getGrauGrafo()){
        return false;
    }

    if(direcionado == false){
        for(listaVertices::iterator v = lista_vertices.begin(); v!= lista_vertices.end(); v++){
            if(getGrau(v->id) != regular)
                return false;
        }
    }
    else{
        for(listaVertices::iterator v = lista_vertices.begin(); v!= lista_vertices.end(); v++){
            if(getGrauEntrada(v->id) != regular || getGrauSaida(v->id) != regular)
                return false;
        }
    }

    return true;
}

int Grafo::getOrdemGrafo(){
    return lista_vertices.size();
}

bool Grafo::verificaTrivial(){
    if(lista_vertices.size() > 1)
        return false;
    else
        return true;
}

bool Grafo::verificaNulo(){

    for(listaVertices::iterator v = lista_vertices.begin(); v!= lista_vertices.end(); v++){
        if(v->lista_arestas.size() > 0)
            return false;
    }
    return true;
}


/*bool grafo::verificaVerticeArticulacao(int id)
{
    //cout << "Verificando articulacao id " << id << endl;
    //cout << "Grafo 1: " << endl;
    //imprimirGrafo();
    //cout << endl;

    list<pair<int,pair<int,int> > > lista;
    int comp1 = getComponentesConexas();
    //cout << "Componentes conexas do grafo 1: "<< comp1 << endl;

    grafo copia = copiarGrafo();
    copia.deletarVertice(id);
    //cout << "Grafo 2: " << endl;
    //copia.imprimirGrafo();
    //cout << endl;
    int comp2 = copia.getComponentesConexas();
    //cout << "Componente conexas do grafo 2: "<< comp2 << endl;
    if(comp2!=comp1)
    {
        return true;
    }
    else
        return false;

}
//Verifica se o grafo é completo
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

        for(int i=0; i < (int)lista_vertices->size(); i++)
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

    //cout << "profundidade id " << id << endl;
    int i = 0;
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        int id_2 = it->first;
        if(id_2 == id){
            //cout << "found id " << id_2 << endl;
            break;
        }
        i++;
    }

    if(vetor[i] == 0)
    {
        //cout << "d" << endl;
        vetor[i] = j;//Coloca um valor diferente de zero indicando que o vertice igual ao id ja foi consultado;
        list<pair<int, int> >*  adj = getAdj(id);
        //cout << "g" << endl;
        for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++)//Percorre a lista referente ao id1 pegando cada parametro da lista e colocando-o na variavel pair a
        {
            //cout << "ID: " << it->first << endl;
            auxbuscaProfundidade(vetor,it->first,j);//A funcao se chama, fazendo um metodo recursivo,atualizando os parametros da funcao

        }
    }
}

bool grafo::verificaArestaPonte(int id1, int id2, int peso)
{
    int componentes = getComponentesConexas();
    grafo copia = copiarGrafo();
    //cout << "ID2: " << id2 << ", Peso: " << peso << endl;
    copia.deletarAresta(id1, id2, peso);
    if(direcionado == false)
        copia.deletarAresta(id2, id1, peso);
    int componentes2 = copia.getComponentesConexas();
    return componentes != componentes2;
}

//Verifica se o grafo È conexo
bool grafo::verificaConexo()
{
    int* vetor = buscaProfundidade(1);//Variavel vetor ira receber o vetor retornado pela funÁ„o buscaProfundidade;

    for(int i=1; i<(int)lista_vertices->size(); i++)
    {
        if(vetor[i]==0)//Percorre todo o vetor em busca de algum espaÁo igual a 0
            return false;
    }

    return true;
}

//Verifica a quantidade de numeros conexos
int grafo::getComponentesConexas()
{
    if(lista_vertices->size() == 0)
        return 0;

    int primeiro_id = lista_vertices->front().first;

    int *vetor = buscaProfundidade(primeiro_id);//Variavel vetor ira receber o vetor retornado pela funÁ„o buscaProfundidade;

    //cout << "Resultado da busca Profundidade: " << endl;
    //for(int i = 0; i < lista_vertices->size(); i++){
    //cout << vetor[i] << ", ";
    //}
    //cout << endl;

    int j = 2;

    int i = 0;
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++)
    {

        if(vetor[i] == 0)//Percorre todo o vetor em busca de algum espaÁo igual a 0
        {

            auxbuscaProfundidade(vetor,it->first,j);////A funÁ„o auxbuscaProfundidade È chamada comeÁando sua busca apartir do vertice que n„o foi visitado.
            j++;
            //cout << "Resultado da auxBuscaProfundidade para id "<< it->first << ": " << endl;
            //for(int i = 0; i < lista_vertices->size(); i++){
            //cout << vetor[i] << ", ";
            //}
            //cout << endl;
        }

        i++;
    }

    j = -1;
    for(int i = 0; i < (int)lista_vertices->size(); i++){
        if(vetor[i] > j)
            j = vetor[i];
    }

    return j;//Retorna a ultima posiÁao do vetor;
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

        for(int i=1; i < (int)lista_vertices->size(); i++)
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

// Verifica o conjunto vertices que sao transitivos indiretos
void grafo::fechoTransitivoIndireto(int id1){
    double ** matrizFloyd;
    matrizFloyd = retornaMatrizFloyd();
    cout << " O conjunto de nós é: {";
    for(int i=0;i< (int)lista_vertices->size();i++)
    {
        //cout << i << ' --> '<< matrizFloyd[i][id1-1] << endl;
        if(matrizFloyd[i][id1-1] != numeric_limits<int>::max())
        {
            cout << i+1 << " ";
        }

    }
    cout << "}"<< endl;

}





void grafo::calculaCaminhoDijkstra(int no1, int no2){
    bool incluidos[lista_vertices->size()]; //Lista de nós já incluídos no caminho mínimo até no1.
    double dist[lista_vertices->size()]; //distância provisória de todos até no1
    list<int> caminho[lista_vertices->size()]; //uma lista para cada nó indicando o caminho até ele.
    for(int i = 0; i< (int)lista_vertices->size(); i++){ //inicializa arrays
        dist[i] = numeric_limits<int>::max(); //infinito para todos valores
        incluidos[i] = false;
    }
    dist[no1-1] = 0;
    incluidos[no1-1] = true; //no1 já tem menor caminho encontrado
    list<pair<int, int> >* adj = getAdj(no1);
    for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){ //atualiza valores dos adj de no1
        dist[it->first-1] = it->second;
    }

    int no_aux = -1, min_aux = 0;
    while(no_aux != no2-1) { //para quando no2 for incluído
        min_aux = numeric_limits<int>::max();
        for(int i=0; i<(int)lista_vertices->size(); i++){ //escolhe menor nó para entrar
            if(!incluidos[i] && dist[i] < min_aux){ //nó não incluido e com menor valor de distancia
                min_aux = dist[i];
                no_aux = i;
            }
        }
        if(min_aux == numeric_limits<int>::max()) {
            break; //caminho não encontrado.
        }
        incluidos[no_aux] = true; //inclui no_aux;
        adj = getAdj(no_aux+1);
        for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){ //atualiza valores dos adj de no_aux
            if(!incluidos[it->first-1] && dist[it->first-1] > dist[no_aux] + it->second){ //se adj ainda não foi incluído e tem distancia maior que a nova
                dist[it->first-1] = dist[no_aux] + it->second;
                caminho[it->first-1] = caminho[no_aux];
                caminho[it->first-1].push_back(no_aux+1); //novo caminho é caminho até no_aux mais no_aux;
            }
        }
    }
    if(min_aux != numeric_limits<int>::max()) { //caminho encontrado
        cout << "Valor do caminho calculado: " << dist[no2-1] << endl;
        cout << no1 << "->";
        for(list<int>::iterator it = caminho[no2-1].begin(); it != caminho[no2-1].end(); it++){
            cout << *it << "->";
        }
        cout << no2 << endl;
    } else {
        cout << "Caminho entre " << no1 << " e " << no2 << " não encontrado!" << endl;
    }
}

void grafo::calculaCaminhoFloyd(int no1, int no2){
    int tamanho = lista_vertices->size();
    double **dist = new double*[tamanho]; //matriz contendo as distâncias de i a j;
    list<int> *caminho[tamanho]; //para cada ij, uma lista indicando o caminho entre eles.
    list<pair<int, int> >* adj;
    for(int i=0;i<tamanho;i++){
        dist[i] = new double[tamanho];//cria variável dist[tamanho][tamanho] dinamicamente
        caminho[i] = new list<int>[tamanho];
        for(int j=0;j<tamanho;j++){
            if(i==j){
                dist[i][j] = 0;
            } else {
                dist[i][j] = numeric_limits<int>::max();//dist começa com infinito.
            }
        }
        adj = getAdj(i+1);
        for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){
            //atualiza todos adj de i;
            dist[i][it->first-1] = it->second;
        }
    }

    for(int k=0;k<tamanho;k++){
        for(int i=0;i<tamanho;i++){
            for(int j=0;j<tamanho;j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    caminho[i][j] = caminho[i][k];
                    caminho[i][j].push_back(k+1); //caminho de ij passa a ser caminho de i a k mais k mais caminho de k a j;
                    caminho[i][j].insert(caminho[i][j].end(), caminho[k][j].begin(), caminho[k][j].end());
                }
            }
        }
    }
    if(dist[no1-1][no2-1] == numeric_limits<int>::max()){
        cout << "Caminho não encontrado!";
    } else {
        cout << "Valor do caminho calculado: " << dist[no1-1][no2-1] << endl;
        cout << no1 << "->";
        for(list<int>::iterator it = caminho[no1-1][no2-1].begin(); it != caminho[no1-1][no2-1].end(); it++){
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



void grafo::fechoTransitivoDireto(int id)
{
    int tam = lista_vertices->size();
    int* arrayDijkstra;
    arrayDijkstra = retornaVetorDijkstra(id);
    cout<<"O conjunto de vértices é : {";
    for(int i =0;i<tam ; i++)
    {
        //cout<< arrayDijkstra[i] << " ";
        if(arrayDijkstra[i] != numeric_limits<int>::max())//se nao for infinito
        {
            cout<< i+1 << " ";
        }
    }
    cout<<"}"<<endl;
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
    grafo g(0, direcionado);

    for(list<int>::iterator it = vertices.begin(); it != vertices.end(); it++){
        //cout << "Vertice: " << *it << endl;
        g.criarVertice(*it);
    }

    for(list<int>::iterator it = vertices.begin(); it != vertices.end(); it++){
        for(lista_adjacencia::iterator no = lista_vertices->begin(); no != lista_vertices->end(); no++){
            if(no->first == *it){
                int id1 = no->first;
                //cout << "Verificando arestas do vertice "<< id1 << endl;
                for(list<pair<int, int> >::iterator adj = no->second.begin(); adj != no->second.end(); adj++){
                    int id2 = adj->first;
                    int peso = adj->second;
                    //cout << "Aresta: " << id2 << ", peso " << peso << endl;
                    if(g.verificaIdExiste(id2)){
                        g.criarAresta(id1, id2, peso);
                    }
                }
            }
        }
    }

    g.imprimirGrafo();
    cout << endl;
}


void grafo::getComponentesFortementeConexas(){
    list<list<int> >* lista_componentes = new list<list<int> >(); //lista contendo as componentes conexas
    grafo copia = copiarGrafo(); //usa uma copia para excluir nós já inseridos numa componente conexa.
    double **dist = retornaMatrizFloyd(); //Gera matriz de distancias entre todos pares de nó. paramentros não interferem.
    int vertice_aux;
    cout << string(80, '\n'); //'limpa' console.
    for(lista_adjacencia::iterator it = copia.lista_vertices->begin(); it != copia.lista_vertices->end(); it++){
        if(it->first != -1){ //-1 define vertice que já entrou
            lista_componentes->push_back(list<int>());
            vertice_aux = it->first;
            for(lista_adjacencia::iterator it2 = copia.lista_vertices->begin(); it2 != copia.lista_vertices->end(); it2++){ //busca para todos vertices.
                if(it2->first != -1){
                    if(dist[vertice_aux-1][it2->first-1] < numeric_limits<int>::max() && dist[it2->first-1][vertice_aux-1] < numeric_limits<int>::max()){
                        //existe caminho de ida e volta entre os dois vertices
                        lista_componentes->back().push_back(it2->first);//inclui na componente o vertice.
                        it2->first = -1;
                    }
                }
            }
        }
    }

    //imprime as componentes
    int componente_index = 1;
    for(list<list<int> >::iterator it = lista_componentes->begin(); it != lista_componentes->end(); it++){
        cout << "Componente " << componente_index << ":" << endl;
        for(list<int>::iterator it2 = it->begin(); it2 != it->end(); it2++){
            cout << *it2 << endl;
        }
        componente_index++;
        cout << endl << endl;
    }

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

bool grafo::verificaEuleriano(){
    bool grauPar = true;//bool que guarda se todos os nós tem grau par
    int noGrau;
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++)
    {
        noGrau = obterGrau(it->first);
        if(noGrau % 2 != 0)//caso haja algum nó de grau ímpar
        {
            grauPar = false;
        }
    }
    if(grauPar && verificaConexo())//se o grafo possui todos os vertices de grau par e é conexo
    {
        return true;
    }
    else
    {
        return false;
    }
}

void grafo::getArticulacoes(){

    for(lista_adjacencia::reverse_iterator it = lista_vertices->rbegin(); it != lista_vertices->rend(); it++){
        if(verificaVerticeArticulacao(it->first)){
            cout << it->first << " ";
        }
    }
    cout << endl;

}

void grafo::getPontes(){

    if(direcionado == false)
    {
        for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
            int id1 = it->first;
            for(list<pair<int, int> >::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
                int id2 = it2->first;
                int peso = it2->second;
                if(verificaArestaPonte(id1, id2, peso))
                    cout << id1 << "-" << id2 << " " << peso << endl;
            }
        }
    }
    else{
        cout << "Para o cálculo de pontes, o grafo deve ser não-orientado" << endl;
    }
}

void grafo::getRaioDiametroCentroPeriferia(){
    queue<int> centro;
    queue<int> periferia;
    int tam = lista_vertices->size();
    int diametro = 0;//maior valor da matriz
    int raio = numeric_limits<int>::max();//menor valor da matriz
    double **matFloyd;
    matFloyd = retornaMatrizFloyd();
    for(int i=0;i< tam ;i++)//procura o maior caminho mais curto (diametro) do grafo
    {
        for(int j=0;j< tam ;j++)
        {

            if(raio > matFloyd[i][j] && matFloyd[i][j] != 0)
            {
                raio = matFloyd[i][j];
            }

            if(diametro < matFloyd[i][j] && matFloyd[i][j] != numeric_limits<int>::max())
            {
                diametro = matFloyd[i][j];
            }
        }
    }


    for(int l=0;l<tam;l++)
    {
        for(int c=0;c<tam;c++)
        {
            if(matFloyd[l][c] == raio)
            {
                centro.push(l+1);
                centro.push(c+1);
            }
             if(matFloyd[l][c] == diametro)
            {
                periferia.push(l+1);
                periferia.push(c+1);
            }
        }
    }

    cout << "Raio :"<<raio<<endl;
    cout <<"Diâmetro :"<<diametro<<endl;
    cout << "Centro :{";
    for(int i = 0;i< (int)centro.size();i ++)
    {
        cout << centro.front()<<" ";
        centro.pop();
    }
    cout<<"}"<<endl;

    cout << "Periferia :{";
    for(int i = 0;i< (int)periferia.size();i ++)
    {
        cout << periferia.front()<<" ";
        periferia.pop();
    }
    cout<<"}"<<endl;

}

void grafo::getAGM(){

    if(direcionado == true){
        cout << "O grafo deve ser não-direcionado para o cálculo da AGM" << endl;
        return;
    }

    grafo g(0, false); // grafo AGM
    grafo copia = copiarGrafo(); // copia do grafo original para calcular AGM

    // Faz uma copia da lista de adjacencias para execucao do algoritmo de Kruskal
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        int id = it->first;
        g.criarVertice(id); // cria os vertices da AGM
    }

    int componentes = getComponentesConexas();
    if(componentes == 1){
        // cout << "Possui somente 1 componente" << endl;

        // Executando algoritmo de Kruskal
        while(copia.numeroArestas() > 0){
            int menor_peso = numeric_limits<int>::max();
            int id1_escolhido = -1;
            int id2_escolhido = -1;
            for(lista_adjacencia::iterator it = copia.lista_vertices->begin(); it != copia.lista_vertices->end(); it++){
                int id1 = it->first;
                //cout << "ID1: " << id1 << endl;
                for(list<pair<int, int> >::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){

                    int id2 = it2->first;
                    int peso = it2->second;
                    //cout << "ID2: " << id2 << ", peso: " << peso <<endl;
                    if(peso < menor_peso){
                        id1_escolhido = id1;
                        id2_escolhido = id2;
                        menor_peso = peso;
                    }
                }
            }
            // adiciona aresta de menor peso no grafo
            //cout << "Menor aresta ID1: " << id1_escolhido << ", ID2: "<< id2_escolhido << ", Peso: "<< menor_peso << endl;
            g.criarAresta(id1_escolhido, id2_escolhido, menor_peso);
            g.criarAresta(id2_escolhido, id1_escolhido, menor_peso);

            // caso a aresta gere ciclo, remova
            if(g.possuiCiclo()){
                // cout << "Gerou novo ciclo, excluindo aresta" << endl;
                g.deletarAresta(id1_escolhido, id2_escolhido, menor_peso);
                g.deletarAresta(id2_escolhido, id1_escolhido, menor_peso);
            }else{
                //cout << "Aresta não adicionou ciclo, mantendo..." << endl;
            }

            //remover aresta escolhida da copia de arestas
            copia.deletarAresta(id1_escolhido, id2_escolhido, menor_peso);
            copia.deletarAresta(id2_escolhido, id1_escolhido, menor_peso);
        }
        g.imprimirGrafo();
        cout << endl;

    }
    else{
        cout << "AGM de grafos com mais de 1 componente ainda não implmementado" << endl;
    }
}
*/
void Grafo::imprimirGrafo() {
    cout << lista_vertices.size();
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++){
        for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++){
            cout << endl;
            cout << v->id << " " << a->id << " " << a->peso;
        }
    }
}
/*
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

// Função auxiliar para calcular numero de arestas
int grafo::numeroArestas(){
    int n = 0;
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        n += it->second.size();
    }
    if(direcionado == true)
        return n;
    else
        return n/2;
}

// Função auxiliar para detectar ciclos em um grafo
bool grafo::buscaProfundidadeCiclo()
{
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        list<int> visitados;
        bool ciclo = auxbuscaProfundidadeCiclo(visitados, it->first, -1);
        if(ciclo == true)
            return ciclo;
    }

    return false;
}

bool grafo::auxbuscaProfundidadeCiclo(list<int> visitados,int id, int pai)
{

    //cout << "Visitando ID " << id << " a partir do nó " << pai << endl;
    list<pair<int, int> >*  adj = getAdj(id);
    list<int> visitados_2;
    bool ciclo = false;
    for(list<int>::iterator it = visitados.begin(); it != visitados.end(); it++){
        visitados_2.push_back(*it);
    }
    for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++)
    {
        //cout << "Aresta ID2: " << it->first << endl;
        bool found = (std::find(visitados_2.begin(), visitados_2.end(), it->first) != visitados_2.end());
        if(it->first == pai){
            //cout << "Nó pai, ignorando... " << endl;
            continue;
        }

        if(!found){
            //cout << "Não visitado ainda. Adicionando a visitados" << endl;
            visitados_2.push_back(it->first);
            ciclo = auxbuscaProfundidadeCiclo(visitados_2, it->first, id);
            if(ciclo == true)
                break;
        }
        else{
            //cout << "Nó já visitado" << endl;
            ciclo = true;
            break;
        }

    }
    return ciclo;
}

//Função que retorna a lista de adjacência do nó no
list<pair<int, int> >* grafo::getAdj(int no){
    for(lista_adjacencia::iterator it = lista_vertices->begin(); it != lista_vertices->end(); it++){
        if(it->first == no)
            return &(it->second);
    }
    return NULL;
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

bool grafo::possuiCiclo(){
    if(direcionado == false){
        return buscaProfundidadeCiclo();
    }
    else{
        return false;
    }
}

int* grafo::retornaVetorDijkstra(int no1)
{
    int tamanho = lista_vertices->size();
    bool incluidos[lista_vertices->size()]; //Lista de nós já incluídos no caminho mínimo até no1.
    //int *dist[lista_vertices->size()]; //distância provisória de todos até no1
    int *dist = new  int[tamanho];
    list<int> caminho[lista_vertices->size()]; //uma lista para cada nó indicando o caminho até ele.
    for(int i = 0; i< (int)lista_vertices->size(); i++){ //inicializa arrays
        dist[i] = numeric_limits<int>::max(); //infinito para todos valores
        incluidos[i] = false;
    }
    dist[no1-1] = 0;
    incluidos[no1-1] = true; //no1 já tem menor caminho encontrado
    list<pair<int, int> >* adj = getAdj(no1);
    for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){ //atualiza valores dos adj de no1
        dist[it->first-1] = it->second;
    }

    int no_aux = -1, min_aux = 0;
    //while(no_aux != NULL) {
    for(int g = 0 ;g <tamanho ;g++)
    {
        min_aux = numeric_limits<int>::max();
        for(int i=0; i<(int)lista_vertices->size(); i++){ //escolhe menor nó para entrar
            if(!incluidos[i] && dist[i] < min_aux){ //nó não incluido e com menor valor de distancia
                min_aux = dist[i];
                no_aux = i;
            }
        }
        incluidos[no_aux] = true; //inclui no_aux;
        adj = getAdj(no_aux+1);
        for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){ //atualiza valores dos adj de no_aux
            if(!incluidos[it->first-1] && dist[it->first-1] > dist[no_aux] + it->second){ //se adj ainda não foi incluído e tem distancia maior que a nova
                dist[it->first-1] = dist[no_aux] + it->second;
                caminho[it->first-1] = caminho[no_aux];
                caminho[it->first-1].push_back(no_aux+1); //novo caminho é caminho até no_aux mais no_aux;
            }
        }
    }

    return dist;

}

double** grafo::retornaMatrizFloyd()
{
    int tamanho = lista_vertices->size();
    double **dist = new double*[tamanho]; //matriz contendo as distâncias de i a j;
    list<int> *caminho[tamanho]; //para cada ij, uma lista indicando o caminho entre eles.
    list<pair<int, int> >* adj;
    for(int i=0;i<tamanho;i++){
        dist[i] = new double[tamanho];//cria variável dist[tamanho][tamanho] dinamicamente
        caminho[i] = new list<int>[tamanho];
        for(int j=0;j<tamanho;j++){
            if(i==j){
                dist[i][j] = 0;
            } else {
                dist[i][j] = numeric_limits<int>::max();//dist começa com infinito.
            }
        }
        adj = getAdj(i+1);
        for(list<pair<int, int> >::iterator it = adj->begin(); it != adj->end(); it++){
            //atualiza todos adj de i;
            dist[i][it->first-1] = it->second;
        }
    }

    for(int k=0;k<tamanho;k++){
        for(int i=0;i<tamanho;i++){
            for(int j=0;j<tamanho;j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    caminho[i][j] = caminho[i][k];
                    caminho[i][j].push_back(k+1); //caminho de ij passa a ser caminho de i a k mais k mais caminho de k a j;
                    caminho[i][j].insert(caminho[i][j].end(), caminho[k][j].begin(), caminho[k][j].end());
                }
            }
        }
    }

    return dist;

}*/

Vertice* Grafo::getVertice(int id){
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++){
        if(v->id == id){
            return &(*v);
        }
    }
    return NULL;
}

Grafo::~Grafo()
{
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++){
        cout << "Cleaning object " << v->id << endl;
    }
    lista_vertices.clear();
}
