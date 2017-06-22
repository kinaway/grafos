#include "Grafo.h"
#include <limits>
#include <fstream>
#include <queue>
#include <tr1/tuple>
//Construtor do grafo, orientação do grafo deve ser passada
Grafo::Grafo(int direcionado)
{
    this->direcionado = direcionado;
}

//Construtor do grafo, orientação e tamanho do grafo devem ser passados
Grafo::Grafo(int direcionado, int tamanho, vector<int>* p)
{
    this->direcionado = direcionado;
    for(int i = 1; i < tamanho+1; i++)
    {
        criarVertice(i);
    }
    if(p != NULL){
        for(int i = 0; i < p->size(); i++){
            particoes.push_back((*p)[i]);
        }
    }

}

// Função para adicionar um vértice id no grafo
// retorna false em caso de falha
bool Grafo::criarVertice(int id)
{
    Vertice* v = getVertice(id);
    if(v == NULL)
    {
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
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        if(v->id == id)
        {
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
    if(v != NULL)
    {
        for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
        {
            // encontrou o vértice id
            if(v->id == id)
            {
                v = --lista_vertices.erase(v);

            }
            else
            {
                for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
                {
                    if(a->id == id)
                    {
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
// O parâmetro peso pode ser ignorado passando-se -1
// retorna false em caso de falha
bool Grafo::deletarAresta(int id,int id2, int peso)
{
    Vertice* v = getVertice(id);
    Vertice* u = getVertice(id2);
    bool found = false;
    //cout << "Deletando " << id << "-" << id2 << ", peso: " << peso << endl;

    if(v != NULL && u != NULL)
    {
        //cout << "Buscando arestas em " << id << endl;

        // busca a aresta entre v e u e apaga
        for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
        {
            if(a->id == id2)
            {
                //cout << "Found id " << id2 << ", peso: " << a->peso << endl;
                if(a->peso == peso || peso == -1)
                {
                    a = --v->lista_arestas.erase(a);
                    found = true;
                    //cout << "Deletado" << endl;
                    break;
                }
            }
        }

        //cout << "Buscando arestas em " << id2 << endl;
        // se for não direcionado, apagamos a aresta entre u e v também
        if(direcionado == false && found == true)
        {
            for(listaArestas::iterator a = u->lista_arestas.begin(); a != u->lista_arestas.end(); a++)
            {
                if(a->id == id)
                {
                    if(a->peso == peso || peso == -1)
                    {
                        a = --u->lista_arestas.erase(a);
                        break;
                    }
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
    if(vertice_v != NULL && vertice_u != NULL)
    {
        vertice_v->adicionaAresta(v, p);
        return true;
    }
    else
    {
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
int Grafo::getGrauEntrada(int id)
{
    Vertice* v = getVertice(id);
    if(v == NULL || direcionado == false)
        return -1;

    int grau_entrada = 0;

    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
        {
            if(a->id == id)
            {
                grau_entrada += 1;
            }
        }
    }

    return grau_entrada;
}

// Obtém o grau de saída do grafo dado que ele é orientado
// retorna -1 em caso de falha
int Grafo::getGrauSaida(int id)
{
    Vertice* v = getVertice(id);
    if(v == NULL || direcionado == false)
        return -1;

    return v->lista_arestas.size();
}

//Obtem o grau do grafo dado que ele é não orientado
int Grafo::getGrauGrafo()
{
    int maior_grau = 0;
    if(direcionado == false)
    {
        for(listaVertices::iterator v = lista_vertices.begin(); v!= lista_vertices.end(); v++)
        {
            int grau = getGrau(v->id);
            if(grau > maior_grau)
                maior_grau = grau;
        }
    }
    else
    {
        cout << "Como o calcula grau de um grafo direcionado?? Adicione aqui!" << endl;
        return -1;
    }

    return maior_grau;
}


//Verifica se o grafo é k regular
bool Grafo::verificaRegular(int regular)
{
    if(regular >= getGrauGrafo())
    {
        return false;
    }

    if(direcionado == false)
    {
        for(listaVertices::iterator v = lista_vertices.begin(); v!= lista_vertices.end(); v++)
        {
            if(getGrau(v->id) != regular)
                return false;
        }
    }
    else
    {
        for(listaVertices::iterator v = lista_vertices.begin(); v!= lista_vertices.end(); v++)
        {
            if(getGrauEntrada(v->id) != regular || getGrauSaida(v->id) != regular)
                return false;
        }
    }

    return true;
}
//Retorna a ordem do Grafo
int Grafo::getOrdemGrafo()
{
    return lista_vertices.size();
}
//Retorna true ou false se o grafo é ou não trivial
bool Grafo::verificaTrivial()
{
    if(lista_vertices.size() > 1)
        return false;
    else
        return true;
}
//Retorna true ou false se o grafo é ou não nulo
bool Grafo::verificaNulo()
{

    for(listaVertices::iterator v = lista_vertices.begin(); v!= lista_vertices.end(); v++)
    {
        if(v->lista_arestas.size() > 0)
            return false;
    }
    return true;
}
//Verifica se um vertice é de articulação
bool Grafo::verificaVerticeArticulacao(int id)
{

    int comp1 = getComponentesConexas();//Recebe a quantidade de componentes conexas do grafo
    Grafo copia = copiarGrafo();
    copia.deletarVertice(id);//Deleta o id passado na copia do grafo original
    int comp2 = copia.getComponentesConexas();
    if(comp2!=comp1)//Verefica se o número de componentes conexas foi alterado após a remoção do id
        return true;
    else
        return false;
}
// Realiza uma busca em profundidade no grafo
// retorna um vetor onde cada posição representa um vértice, e cada valor, o id de uma componente conexa
int* Grafo::buscaProfundidade()
{
    int *vetor = new int[lista_vertices.size()];

    for(int i=0; i < (int)lista_vertices.size(); i++)
    {
        vetor[i] = 0;// vetor é inicializado com todos os seus parametros sendo igual a 0
    }

    int j = 1;
    int vetor_id = 0;

    for(listaVertices::iterator v = lista_vertices.begin(); v!= lista_vertices.end(); v++)
    {
        if(vetor[vetor_id] == 0)
        {
            auxbuscaProfundidade(vetor,v->id,j);
            j += 1;
            v = --lista_vertices.begin();
            vetor_id = 0;
            continue;
        }
        vetor_id +=1;
    }

    return vetor;
}

//Função auxiliar da busca em profundidade
void Grafo::auxbuscaProfundidade(int* vetor, int id_vertice, int j)
{
    int id_vetor = 0;
    for(listaVertices::iterator v = lista_vertices.begin(); v!= lista_vertices.end(); v++)
    {
        if(v->id == id_vertice)
        {
            break;
        }
        id_vetor++;
    }

    if(vetor[id_vetor] == 0)
    {
        vetor[id_vetor] = j;//Coloca um valor diferente de zero indicando que o vertice igual ao id ja foi consultado;
        Vertice* v = getVertice(id_vertice);
        for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)//Percorre os adjacentes do vertice
        {
            auxbuscaProfundidade(vetor,a->id,j);
        }

    }
}

//Verifica se o grafo È conexo
bool Grafo::verificaConexo()
{
    int* vetor = buscaProfundidade();//Variavel vetor ira receber o vetor retornado pela funÁ„o buscaProfundidade;

    for(int i=1; i<(int)lista_vertices.size(); i++)
    {
        if(vetor[i] != 1)//Percorre todo o vetor em busca de algum espaÁo igual a 0
            return false;
    }

    return true;
}

//Verifica a quantidade de componentes conexos
int Grafo::getComponentesConexas()
{
    if(lista_vertices.size() == 0)
        return 0;

    int *vetor = buscaProfundidade();

    int j = -1;

    for(int i = 0; i < (int)lista_vertices.size(); i++)
    {
        if(vetor[i] > j)
            j = vetor[i];
    }

    return j; //Retorna a ultima posiÁao do vetor;*/
}

//Verifica o conjunto vertices que sao transitivos indiretos
void Grafo::fechoTransitivoIndireto(int id1)
{
    double ** matrizFloyd;
    matrizFloyd = retornaMatrizFloyd(true);
    cout << " O conjunto de nós é: {";
    for(int i=0; i< (int)lista_vertices.size(); i++)
    {

        if(matrizFloyd[i][id1-1] != numeric_limits<int>::max())
        {
            cout << i+1 << " ";
        }

    }
    cout << "}"<< endl;

    for(int i = 0; i < (int)lista_vertices.size(); i++)
    {
        delete matrizFloyd[i];
    }
    delete matrizFloyd;

}

void Grafo::calculaCaminhoDijkstra(int no1, int no2)
{
    bool incluidos[lista_vertices.size()]; //Lista de nós já incluídos no caminho mínimo até no1.
    double dist[lista_vertices.size()]; //distância provisória de todos até no1
    list<int> caminho[lista_vertices.size()]; //uma lista para cada nó indicando o caminho até ele.
    for(int i = 0; i< (int)lista_vertices.size(); i++)  //inicializa arrays
    {
        dist[i] = numeric_limits<int>::max(); //infinito para todos valores
        incluidos[i] = false;
    }
    dist[no1-1] = 0;
    incluidos[no1-1] = true; //no1 já tem menor caminho encontrado
    listaArestas adj = getAdj(no1);
    for(listaArestas::iterator it = adj.begin(); it != adj.end(); it++)  //atualiza valores dos adj de no1
    {
        dist[it->id-1] = it->peso;
    }

    int no_aux = -1, min_aux = 0;
    while(no_aux != no2-1)   //para quando no2 for incluído
    {
        min_aux = numeric_limits<int>::max();
        for(int i=0; i<(int)lista_vertices.size(); i++)  //escolhe menor nó para entrar
        {
            if(!incluidos[i] && dist[i] < min_aux)  //nó não incluido e com menor valor de distancia
            {
                min_aux = dist[i];
                no_aux = i;
            }
        }
        if(min_aux == numeric_limits<int>::max())
        {
            break; //caminho não encontrado.
        }
        incluidos[no_aux] = true; //inclui no_aux;
        adj = getAdj(no_aux+1);
        for(listaArestas::iterator it = adj.begin(); it != adj.end(); it++)  //atualiza valores dos adj de no_aux
        {
            if(!incluidos[it->id-1] && dist[it->id-1] > dist[no_aux] + it->peso)  //se adj ainda não foi incluído e tem distancia maior que a nova
            {
                dist[it->id-1] = dist[no_aux] + it->peso;
                caminho[it->id-1] = caminho[no_aux];
                caminho[it->id-1].push_back(no_aux+1); //novo caminho é caminho até no_aux mais no_aux;
            }
        }
    }
    if(min_aux != numeric_limits<int>::max())   //caminho encontrado
    {
        cout << "Valor do caminho calculado: " << dist[no2-1] << endl;
        cout << no1 << "->";
        for(list<int>::iterator it = caminho[no2-1].begin(); it != caminho[no2-1].end(); it++)
        {
            cout << *it << "->";
        }
        cout << no2 << endl;
    }
    else
    {
        cout << "Caminho entre " << no1 << " e " << no2 << " não encontrado!" << endl;
    }
}

void Grafo::calculaCaminhoFloyd(int no1, int no2)
{
    int tamanho = lista_vertices.size();
    double **dist = new double*[tamanho]; //matriz contendo as distâncias de i a j;
    list<int> *caminho[tamanho]; //para cada ij, uma lista indicando o caminho entre eles.
    listaArestas adj;
    for(int i=0; i<tamanho; i++)
    {
        dist[i] = new double[tamanho];//cria variável dist[tamanho][tamanho] dinamicamente
        caminho[i] = new list<int>[tamanho];
        for(int j=0; j<tamanho; j++)
        {
            if(i==j)
            {
                dist[i][j] = 0;
            }
            else
            {
                dist[i][j] = numeric_limits<int>::max();//dist começa com infinito.
            }
        }
        adj = getAdj(i+1);
        for(listaArestas::iterator it = adj.begin(); it != adj.end(); it++)
        {
            //atualiza todos adj de i;
            dist[i][it->id-1] = it->peso;
        }
    }

    for(int k=0; k<tamanho; k++)
    {
        for(int i=0; i<tamanho; i++)
        {
            for(int j=0; j<tamanho; j++)
            {
                if(dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    caminho[i][j] = caminho[i][k];
                    caminho[i][j].push_back(k+1); //caminho de ij passa a ser caminho de i a k mais k mais caminho de k a j;
                    caminho[i][j].insert(caminho[i][j].end(), caminho[k][j].begin(), caminho[k][j].end());
                }
            }
        }
    }
    if(dist[no1-1][no2-1] == numeric_limits<int>::max())
    {
        cout << "Caminho não encontrado!";
    }
    else
    {
        cout << "Valor do caminho calculado: " << dist[no1-1][no2-1] << endl;
        cout << no1 << "->";
        for(list<int>::iterator it = caminho[no1-1][no2-1].begin(); it != caminho[no1-1][no2-1].end(); it++)
        {
            cout << *it << "->";
        }
        cout << no2 << endl;
    }
}

void Grafo::fechoTransitivoDireto(int id)
{
    int tam = lista_vertices.size();
    int* arrayDijkstra;
    arrayDijkstra = retornaVetorDijkstra(id);
    cout<<"O conjunto de vértices é : {";
    for(int i =0; i<tam ; i++)
    {
        if(arrayDijkstra[i] != numeric_limits<int>::max())//se nao for infinito
        {
            cout<< i+1 << " ";
        }
    }
    cout<<"}"<<endl;
    delete arrayDijkstra;
}

void Grafo::getSequenciaGraus()
{
  for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        int id = v->id;
        int grau = v->lista_arestas.size();
        cout << "Vertice " << id <<": " << grau << endl;
    }
}

void Grafo::getSubgrafoInduzido(list<int> vertices)
{

    Grafo g(direcionado);

    for(list<int>::iterator v = vertices.begin(); v != vertices.end(); v++)
    {
        g.criarVertice(*v);
    }

    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        if(g.verificaIdExiste(v->id) == true)
        {
            for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
            {
                if(g.verificaIdExiste(a->id) == true)
                {
                    g.criarAresta(v->id, a->id, a->peso);
                }
            }
        }
    }

    g.imprimirGrafo();
    cout << endl;

}


void Grafo::getComponentesFortementeConexas()
{
    list<list<int> > lista_componentes = list<list<int> >(); //lista contendo as componentes conexas
    Grafo copia = copiarGrafo(); //usa uma copia para excluir nós já inseridos numa componente conexa.
    double **dist = retornaMatrizFloyd(true); //Gera matriz de distancias entre todos pares de nó. paramentros não interferem.
    int vertice_aux;
    cout << string(80, '\n'); //'limpa' console.
    for(listaVertices::iterator it = copia.lista_vertices.begin(); it != copia.lista_vertices.end(); it++)
    {
        if(it->id != -1)  //-1 define vertice que já entrou
        {
            lista_componentes.push_back(list<int>());
            vertice_aux = it->id;
            for(listaVertices::iterator it2 = copia.lista_vertices.begin(); it2 != copia.lista_vertices.end(); it2++)  //busca para todos vertices.
            {
                if(it2->id != -1)
                {
                    if(dist[vertice_aux-1][it2->id-1] < numeric_limits<int>::max() && dist[it2->id-1][vertice_aux-1] < numeric_limits<int>::max())
                    {
                        //existe caminho de ida e volta entre os dois vertices
                        lista_componentes.back().push_back(it2->id);//inclui na componente o vertice.
                        it2->id = -1;
                    }
                }
            }
        }
    }

    //imprime as componentes
    int componente_index = 1;
    for(list<list<int> >::iterator it = lista_componentes.begin(); it != lista_componentes.end(); it++)
    {
        cout << "Componente " << componente_index << ":" << endl;
        for(list<int>::iterator it2 = it->begin(); it2 != it->end(); it2++)
        {
            cout << *it2 << endl;
        }
        componente_index++;
        cout << endl << endl;
    }

    for(int i=0; i < (int)lista_vertices.size(); i++)
    {
        delete dist[i];
    }
    delete dist;
}

void Grafo::getComplementar()
{
    Grafo g (direcionado);

    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        g.criarVertice(v->id);
    }

    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        for(listaVertices::iterator v_2 = lista_vertices.begin(); v_2 != lista_vertices.end(); v_2++)
        {
            if(v->id != v_2->id)
            {
                g.criarAresta(v->id, v_2->id, 0);
            }
        }
    }

    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
        {
            if(g.possuiAresta(v->id, a->id))
            {
                g.deletarAresta(v->id, a->id, 0);
            }
        }
    }
    cout << "Grafo complementar: " << endl;
    g.imprimirGrafo();
    cout << endl;

}

bool Grafo::verificaEuleriano()
{
    bool grauPar = true;//bool que guarda se todos os nós tem grau par
    int noGrau;
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        noGrau = v->lista_arestas.size();
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

int j = 1;
void Grafo::auxbuscaProfundidadeArticulacao(tuple<int, int,int>* vetor, int id_vertice)
{
    int id_vetor = 0;
    for(listaVertices::iterator v = lista_vertices.begin(); v!= lista_vertices.end(); v++)
    {
        if(v->id == id_vertice)
        {
            break;
        }
        id_vetor++;
    }
    if(get<0>(vetor[id_vetor]) == 0)
    {
        get<0>(vetor[id_vetor]) = j;//Coloca a ordem de consulta(prenum[])
        get<1>(vetor[id_vetor]) = j;//Valor relacionado ao vertice que esta ligado(menor[])

        j++;

        Vertice* v = getVertice(id_vertice);
        for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
        {
            if(get<0>(vetor[a->id - 1]) == 0)
            {
                auxbuscaProfundidadeArticulacao(vetor,a->id);

                if(get<0>(vetor[a->id-1]) > get<0>(vetor[id_vetor]))//Verifica se a posição dos adjacente de id_vetor são menores que a posição do id_vetor
                {

                    listaArestas adj = getAdj(a->id);//Recupera a lista de adjacentes
                    for(listaArestas::iterator it = adj.begin(); it != adj.end(); it++)
                    {

                        if(it->id-1 != id_vetor)
                        {
                            if(get<0>(vetor[a->id-1]) > get<0>(vetor[it->id-1]))//prenum[vertice] para cada vertice tal que existe uma aresta(v,vertice)em G(grafo original) que não aparece em T(arvore gerada pela busca em profundidade).
                            {
                                int salva =  get<1>(vetor[a->id-1]);
                                if(get<0>(vetor[it->id-1]) < salva)
                                {
                                    get<1>(vetor[a->id-1]) = get<0>(vetor[it->id-1]);//menor[] recebe prenum[]
                                }

                            }
                        }
                    }
                    get<2>(vetor[id_vetor]) = get<2>(vetor[id_vetor])+1;//Verifica quantos filhos tem um vertice;
                    if(get<1>(vetor[id_vetor]) > get<1>(vetor[a->id-1]))
                    {
                        get<1>(vetor[id_vetor]) = get<1>(vetor[a->id-1]);//menor[] do id_vetor recebe o menor valor dos menor[] valores dos filhos de id_vetor
                    }

                    if(get<1>(vetor[a->id-1]) >= get<0>(vetor[id_vetor]))
                    {

                        if(id_vetor != 0)
                        {
                            cout << "No de articulação: " << id_vetor+1;
                            cout<< endl;
                        }
                    }
                    if( get<2>(vetor[0]) > 1)//Verifica se a raiz tem mais de um filho
                    {
                        cout << "No de articulação: " << id_vetor;
                        cout<< endl;
                    }

                }

            }
        }

    }
}


void Grafo::getArticulacoes()
{
    j = 1;
    tuple <int,int,int> vetor[lista_vertices.size()];
    for(int i = 0; i < (int)lista_vertices.size(); i++)
    {
        get<0>(vetor[i]) =0;
        get<1>(vetor[i]) =0;
        get<2>(vetor[i]) = 0;
    }
    for(int i = 0; i < (int)lista_vertices.size(); i++)
    {
        if(get<0>(vetor[i]) == 0)
        {
            for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
            {
                if(v->id == i -1)
                {
                    auxbuscaProfundidadeArticulacao(vetor, 1);
                    break;
                }
            }
        }
    }
}
void Grafo::getPontes()
{

    if(direcionado == false)
    {
        buscaPontes();
    }
    else
    {
        cout << "Para o cálculo de pontes, o grafo deve ser não-orientado" << endl;
    }
}

void Grafo::getRaioDiametroCentroPeriferia(){
    queue<int> centro;
    queue<int> periferia;
    int tam = lista_vertices.size();
    int listaExcentricidade[tam];
    double diametro = 0;//maior valor da matriz
    double raio = numeric_limits<int>::max();//menor valor da matriz
    double **matFloyd;
    matFloyd = retornaMatrizFloyd(false);
    for(int i=0;i< tam ;i++)//procura o maior caminho mais curto (diametro) do grafo
    {
        int maior = 0;
        //int menor = numeric_limits<int>::max();
        for(int j=0;j< tam ;j++)
        {
//            if(diametro < matFloyd[i][j] && matFloyd[i][j] != numeric_limits<int>::max())
//            {
//                diametro = matFloyd[i][j];
//            }
            if(maior < matFloyd[i][j] && matFloyd[i][j] != numeric_limits<int>::max())
            {
                maior = matFloyd[i][j];
                listaExcentricidade[i] = matFloyd[i][j];
            }
        }
    }
    for(int l = 0;l<tam;l++)
    {
        if(listaExcentricidade[l] < raio)
        {
            raio = listaExcentricidade[l];
        }
        if(listaExcentricidade[l] > diametro)
        {
            diametro = listaExcentricidade[l];
        }
    }

    for(int k=0;k<tam;k++)
    {
        if(listaExcentricidade[k] == raio)
        {
            centro.push(k+1);
        }
        if(listaExcentricidade[k] == diametro)
        {
            periferia.push(k+1);
        }
    }


    cout << "Raio :"<<raio<<endl;
    cout <<"Diâmetro :"<<diametro<<endl;
    cout << "Centro :{";
    while(!centro.empty())
    {
        cout << centro.front()<<" ";
        centro.pop();
    }
    cout<<"}"<<endl;

    cout << "Periferia :{";
    //for(int i = 0;i< (int)periferia.size();i ++)
    while(!periferia.empty())
    {
        cout << periferia.front()<<" ";
        periferia.pop();
    }
    cout<<"}"<<endl;

    for(int i = 0; i < (int)lista_vertices.size(); i++){
        delete matFloyd[i];
    }
    delete matFloyd;
}

// Imprime o a árvore geradora mínima ou floresta mínima
void Grafo::getAGM()
{

    if(direcionado == true)
    {
        cout << "O grafo deve ser não-direcionado para o cálculo da AGM" << endl;
        return;
    }
    Grafo g(direcionado);
    Grafo copia = copiarGrafo();

    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        g.criarVertice(v->id);
    }

    // Executando algoritmo de Kruskal
    while(copia.numeroArestas() > 0)
    {
        int menor_peso = numeric_limits<int>::max();
        int id1_escolhido = -1;
        int id2_escolhido = -1;

        for(listaVertices::iterator v = copia.lista_vertices.begin(); v != copia.lista_vertices.end(); v++)
        {
            int id1 = v->id;
            for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
            {
                int id2 = a->id;
                int peso = a->peso;
                if(peso < menor_peso)
                {
                    id1_escolhido = id1;
                    id2_escolhido = id2;
                    menor_peso = peso;
                }
            }
        }

        // adiciona aresta de menor peso no grafo
        g.criarAresta(id1_escolhido, id2_escolhido, menor_peso);
        g.criarAresta(id2_escolhido, id1_escolhido, menor_peso);

        // caso a aresta gere ciclo, remova
        if(g.possuiCiclo(id1_escolhido))
        {
            g.deletarAresta(id1_escolhido, id2_escolhido, menor_peso);
            g.deletarAresta(id2_escolhido, id1_escolhido, menor_peso);
        }

        //remover aresta escolhida da copia de arestas
        copia.deletarAresta(id1_escolhido, id2_escolhido, menor_peso);
        copia.deletarAresta(id2_escolhido, id1_escolhido, menor_peso);

    }
    g.imprimirGrafo();
    cout << endl;

}

// Função auxiliar para imprimir grafo
void Grafo::imprimirGrafo()
{
    cout << lista_vertices.size();
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
        {
            cout << endl;
            cout << v->id << " " << a->id << " " << a->peso;
        }
    }
}

// Função auxiliar para salvar um grafo em memória no arquivo
void Grafo::salvarArquivo(ofstream& arquivo)
{
    arquivo << lista_vertices.size();

    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
        {
            arquivo << endl;
            arquivo << v->id << " " << a->id << " " << a->peso;
        }
    }

}

// Função auxiliar para calcular numero de arestas
int Grafo::numeroArestas()
{
    int n = 0;
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        n += v->lista_arestas.size();
    }
    if(direcionado == true)
        return n;
    else
        return n/2;
}

// Função auxiliar para detectar ciclos em um grafo
bool Grafo::possuiCiclo(int id)
{

    list<int> visitados;
    visitados.push_back(id);
    bool ciclo = buscaCicloAux(visitados, id, -1);
    if(ciclo == true)
        return ciclo;


    return false;
}

bool Grafo::buscaCicloAux(list<int> visitados,int id, int pai)
{
    list<int> visitados_2;

    for(list<int>::iterator it = visitados.begin(); it != visitados.end(); it++)
    {
        visitados_2.push_back(*it);
    }

    Vertice* v = getVertice(id);
    bool ciclo = false;

    for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
    {

        if(a->id == pai)
        {

            continue;
        }
        bool found = (std::find(visitados_2.begin(), visitados_2.end(), a->id) != visitados_2.end());

        if(!found)
        {

            visitados_2.push_back(a->id);
            ciclo = buscaCicloAux(visitados_2, a->id, id);
            if(ciclo == true)
                break;
        }
        else
        {
            ciclo = true;
            break;
        }

    }

    return ciclo;

}

//Função que retorna a lista de adjacência do vértice v
listaArestas Grafo::getAdj(int v)
{
    for(listaVertices::iterator it = lista_vertices.begin(); it != lista_vertices.end(); it++)
    {
        if(it->id == v)
            return (it->lista_arestas);
    }
    return listaArestas();
}

// Retorna uma cópia do grafo atual
Grafo Grafo::copiarGrafo()
{

    Grafo copia(direcionado);

    // cria vértices
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        if(!copia.verificaIdExiste(v->id))
        {
            copia.criarVertice(v->id);
        }
    }

    // criar adjacencias
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
        {
            copia.criarAresta(v->id, a->id, a->peso);
        }
    }

    return copia;
}

int* Grafo::retornaVetorDijkstra(int no1)
{
    int tamanho = lista_vertices.size();
    bool incluidos[lista_vertices.size()]; //Lista de nós já incluídos no caminho mínimo até no1.
    //int *dist[lista_vertices->size()]; //distância provisória de todos até no1
    int *dist = new  int[tamanho];
    list<int> caminho[lista_vertices.size()]; //uma lista para cada nó indicando o caminho até ele.
    for(int i = 0; i< (int)lista_vertices.size(); i++)  //inicializa arrays
    {
        dist[i] = numeric_limits<int>::max(); //infinito para todos valores
        incluidos[i] = false;
    }
    dist[no1-1] = 0;
    incluidos[no1-1] = true; //no1 já tem menor caminho encontrado
    listaArestas adj = getAdj(no1);
    for(listaArestas::iterator it = adj.begin(); it != adj.end(); it++)  //atualiza valores dos adj de no1
    {
        dist[it->id-1] = it->peso;
    }

    int no_aux = -1, min_aux = 0;
    //while(no_aux != NULL) {
    for(int g = 0 ; g <tamanho ; g++)
    {
        min_aux = numeric_limits<int>::max();
        for(int i=0; i<(int)lista_vertices.size(); i++)  //escolhe menor nó para entrar
        {
            if(!incluidos[i] && dist[i] < min_aux)  //nó não incluido e com menor valor de distancia
            {
                min_aux = dist[i];
                no_aux = i;
            }
        }
        incluidos[no_aux] = true; //inclui no_aux;
        adj = getAdj(no_aux+1);
        for(listaArestas::iterator it = adj.begin(); it != adj.end(); it++)  //atualiza valores dos adj de no_aux
        {
            if(!incluidos[it->id-1] && dist[it->id-1] > dist[no_aux] + it->peso)  //se adj ainda não foi incluído e tem distancia maior que a nova
            {
                dist[it->id-1] = dist[no_aux] + it->peso;
                caminho[it->id-1] = caminho[no_aux];
                caminho[it->id-1].push_back(no_aux+1); //novo caminho é caminho até no_aux mais no_aux;
            }
        }
    }

    return dist;

}

double** Grafo::retornaMatrizFloyd(bool ponderado)
{
    int tamanho = lista_vertices.size();
    double **dist = new double*[tamanho]; //matriz contendo as distâncias de i a j;
    list<int> *caminho[tamanho]; //para cada ij, uma lista indicando o caminho entre eles.
    listaArestas adj;
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
        for(listaArestas::iterator it = adj.begin(); it != adj.end(); it++){
            //atualiza todos adj de i;
            if(ponderado)
            {
                dist[i][it->id-1] = it->peso;
            }else{
                if(i != it->id-1)
                {
                    dist[i][it->id-1] = 1;
                }
            }
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

}

// Implementação do algoritmo de Tarjan para a busca de arestas pontes
// utiliza uma busca em profundidade para busca de arestas não abraçadas por nehuma outra
// conforme descrito em ime.usp.br/~pf/algoritmos_para_grafos/aulas/bridges.html
void Grafo::buscaPontes()
{
    list<pair<int,int> > pontes;
    int* pre = new int[lista_vertices.size()];
    int* parent = new int[lista_vertices.size()];
    int* low = new int[lista_vertices.size()];
    int cnt = 0;

    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        pre[v->id-1] = parent[v->id-1] =  -1;
        low[v->id-1] = -1;
    }

    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        if (pre[v->id-1] == -1)
        {
            parent[v->id-1] = v->id;

            buscaPontesAux(*v, pre, parent, low, &cnt, &pontes);
        }
    }

    if(pontes.size() == 0)
    {
        cout << "Não existem pontes neste grafo" << endl;
        return;
    }

    for(list<pair<int,int> >::iterator it = pontes.begin(); it != pontes.end(); it++)
    {
        cout << it->first << "-" << it->second << endl;
    }

}

void Grafo::buscaPontesAux(Vertice v, int* pre, int* parent, int* low, int* cnt, list<pair<int,int> >* bridges)
{
    int minn;

    pre[v.id-1] = *cnt;
    *cnt = *cnt + 1;

    minn = pre[v.id-1];
    for(listaArestas::iterator a = v.lista_arestas.begin(); a != v.lista_arestas.end(); a++)
    {
        int incidente_id = a->id;
        if(pre[incidente_id-1] == -1)
        {
            parent[incidente_id-1] = v.id;
            Vertice *u = getVertice(incidente_id);
            buscaPontesAux(*u, pre, parent, low, cnt, bridges);
            if (low[incidente_id-1] < minn) /*A*/
                minn = low[incidente_id-1];
        }

        else
        {
            if (pre[incidente_id-1] < minn && incidente_id != parent[v.id-1]) /*B*/
                minn = pre[incidente_id-1];
        }
    }
    low[v.id-1] = minn;
    for(listaVertices::iterator vertice = lista_vertices.begin(); vertice != lista_vertices.end(); vertice++)
    {
        if(parent[vertice->id-1] != -1)
            if (low[vertice->id-1] == pre[vertice->id-1] && parent[vertice->id-1] != vertice->id)
            {
                bool already_in = false;
                for(list<pair<int,int> >::iterator it = bridges->begin(); it != bridges->end(); it++)
                {
                    if((it->first == parent[vertice->id-1] && it->second == vertice->id) ||
                            (it->first == vertice->id && it->second == parent[vertice->id-1]))
                    {
                        already_in = true;
                        break;
                    }
                }
                if(already_in == false)
                {
                    bridges->push_back(make_pair(parent[vertice->id-1], vertice->id));
                }

            }
    }

}

// Função auxiliar para verificar se existe uma aresta entre o vértice id1 e id2
bool Grafo::possuiAresta(int id1, int id2)
{
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        if(v->id == id1)
        {
            for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
            {
                if(a->id == id2)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// Função auxiliar para objter um objeto vértice
// retorna nulo em caso de falha
Vertice* Grafo::getVertice(int id)
{
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        if(v->id == id)
        {
            return &(*v);
        }
    }
    return NULL;
}

Grafo::~Grafo()
{
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        //cout << "Cleaning object " << v->id << endl;
    }
    lista_vertices.clear();
}
