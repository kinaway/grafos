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
    if(p != NULL)
    {
        for(int i = 0; i < p->size(); i++)
        {
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


// Imprime o a árvore geradora mínima ou floresta mínima
void Grafo::getAGM()
{

    if(direcionado == true)
    {
        cout << "O grafo deve ser não-direcionado para o cálculo da AGM" << endl;
        return;
    }
    Grafo copia = copiarGrafo();

    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        v->lista_arestas.clear();
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
        criarAresta(id1_escolhido, id2_escolhido, menor_peso);
        criarAresta(id2_escolhido, id1_escolhido, menor_peso);

        // caso a aresta gere ciclo, remova
        if(possuiCiclo(id1_escolhido))
        {
            deletarAresta(id1_escolhido, id2_escolhido, menor_peso);
            deletarAresta(id2_escolhido, id1_escolhido, menor_peso);
        }

        //remover aresta escolhida da copia de arestas
        copia.deletarAresta(id1_escolhido, id2_escolhido, menor_peso);
        copia.deletarAresta(id2_escolhido, id1_escolhido, menor_peso);

    }
    imprimirGrafo();
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

void Grafo::getPAGMGGuloso()
{

    double grau_aux = numeric_limits<double>::max();
    Vertice *vertice_aux,*vertice_min,*vertice_aux2;
    Aresta *aresta_min;
    int particao_visitada[particoes.size()];
    int vertices_arvore[particoes.size()];
    int peso_arestas[particoes.size()-1];
    int particao1,particao2;

    for(int i = 0; i<particoes.size(); i++)
    {

        particao_visitada[i] = -1;
        vertices_arvore[i] = -1;
    }


    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
        {
            vertice_aux = getVertice(a->id);
            vertice_aux2 = getVertice(v->id);
            particao1 = getParticao(v->id);
            particao2 = getParticao(vertice_aux->id);
            if(particao1 != particao2 && a->peso < grau_aux)
            {
                grau_aux = a->peso;
                //aresta_min = &a;
                vertices_arvore[0] = v->id;
                peso_arestas[0] = a->peso;
            }
        }
    }

    vertices_arvore[1] = vertice_aux->id;
    particao_visitada[getParticao(vertice_aux->id)] = 1;
    particao_visitada[getParticao(vertice_aux2->id)] = 1;

 int  i = 2;
    while(i < particoes.size())
    {
        int j = 0;
        grau_aux = numeric_limits<double>::max();
        while( vertices_arvore[j] != -1 )
        {
            vertice_aux2 = getVertice(vertices_arvore[j]);
            for(listaArestas::iterator a = vertice_aux2->lista_arestas.begin(); a != vertice_aux2->lista_arestas.end(); a++)
            {
                vertice_aux = getVertice(a->id);
                particao1 = getParticao(vertice_aux->id);
                particao2 = getParticao(vertice_aux2->id);
                if(particao1 != particao2 && a->peso < grau_aux && particao_visitada[particao1] != 1 )
                {
                    grau_aux = a->peso;
                    //vertice_min = vertice_aux;
                    //aresta_min = *a;
                    vertices_arvore[i] = vertice_aux->id;
                    peso_arestas[i-1] = aresta_min->peso;
                }
            }

            j++;
        }

        particao_visitada[getParticao(vertices_arvore[i])] = 1;
        i++;
    }

  Grafo arvoreGulosa(this->direcionado, this->lista_vertices.size(), &this->particoes);
    for(int i = 0; i<particoes.size(); i++)
    {
        arvoreGulosa.criarVertice(vertices_arvore[i]);
        if(i>=1)
        {
            arvoreGulosa.criarAresta(vertices_arvore[i-1],vertices_arvore[i],peso_arestas[i-1]);
        }
    }
}

void Grafo::getPAGMGRandomizado()
{

    vector<Vertice*> selected_nodes;

    int range = 1;

    for(vector<int>::iterator it = particoes.begin(); it != particoes.end(); it++)
    {

        int min_range = range;
        int max_range = *it + range - 1;
        //cout << "Range: " << min_range << ", " << max_range << endl;

        int selected = rand() % (max_range-min_range+1) + min_range;
        //cout << "Nó selecionado:" << selected<< endl;
        Vertice* selected_node = getVertice(selected);
        selected_nodes.push_back(selected_node);

        range += *it;

    }

    Grafo g(this->direcionado, this->lista_vertices.size(), &this->particoes);

    //cout << endl << "Selecionados:"  << endl;
    for(int i = 0; i < selected_nodes.size(); i++)
    {
        //cout << selected_nodes[i]->id << endl;
        //cout << "Arestas: " << endl;
        for(listaArestas::iterator a = selected_nodes[i]->lista_arestas.begin(); a != selected_nodes[i]->lista_arestas.end(); a++)
        {
            //cout << "ID: " << a->id << ", Peso: " << a->peso << endl;
            for(int j = 0; j < selected_nodes.size(); j++)
            {
                if(selected_nodes[j]->id == a->id)
                {
                    g.criarAresta(selected_nodes[i]->id, a->id, a->peso);
                    break;
                }
            }

        }
    }

    //cout<< "Grafo Construido: " << endl;
    //g.imprimirGrafo();

    cout << "Arvore montada com Guloso Randômico: " << endl;
    g.getAGM();


}

void Grafo::getPAGMGReativo()
{

    double alpha = 0.5;

    vector<pair<int, Aresta*> > selected_edges;
    vector<pair<int, Aresta*> > arestasOrdenadas;

    // vetor auxiliar inicializado com -1, indicando qual nó de cada
    // partição já foi inserido no conjunto solução
    int particoesPreenchidas[particoes.size()];
    for(int i = 0; i < particoes.size(); i++)
        particoesPreenchidas[i] = -1;

    // Ordena todas as arestas por peso crescente no vetor arestasOrdenadas
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        for(listaArestas::iterator a = v->lista_arestas.begin(); a != v->lista_arestas.end(); a++)
        {

            int peso_nova_aresta = a->peso;
            int oldSize = arestasOrdenadas.size();

            //cout << "Peso nova aresta: " << peso_nova_aresta << endl;
            vector<pair<int, Aresta*> >::iterator it = arestasOrdenadas.begin();
            while(it != arestasOrdenadas.end())
            {
                int peso_aresta =  it->second->peso;
                //cout << "Peso aresta " << peso_aresta << endl;
                if(peso_nova_aresta < peso_aresta)
                {
                    arestasOrdenadas.insert(it, make_pair(v->id, &(*a)));
                    break;
                }
                it++;
            }

            if(oldSize == arestasOrdenadas.size())
            {
                arestasOrdenadas.push_back(make_pair(v->id, &(*a)));
            }

        }
    }

    //cout << "Arestas ordenadas:" << endl;
    //for(vector<pair<int, Aresta*> >::iterator it = arestasOrdenadas.begin(); it != arestasOrdenadas.end(); it++){
    //    cout << it->first << " " << it->second->id << " " << it->second->peso << endl;
    //}

    // Enquanto não tiver selecionado 1 vértice de cada partição E houverem arestas restantes
    // na lista de candidatos, executa o construtivo com o seguinte algoritmo:
    // 1 - calcula o peso mínimo de acordo com o alfa
    // 2 - obtém um subconjunto (LCR) com arestas com peso <= peso_minimo
    // 3 - seleciona aleatoriamente um candidato do lcr
    //      Se ambas as particoes ainda não foram exploradas
    //            salva esta aresta e volta para 1
    //      Senão
    //          delete esta aresta e volta para o passo 3
    // 4 - Se LCR é igual a vazio, volta para o passo 1
    while(selected_edges.size() < particoes.size()-1 && arestasOrdenadas.size() > 0)
    {

        vector<pair<int, Aresta*> > lcr;
        int menor_peso = arestasOrdenadas[0].second->peso;
        int maior_peso = arestasOrdenadas[arestasOrdenadas.size()-1].second->peso;
        double peso_minimo = menor_peso + alpha * (maior_peso - menor_peso);

        //cout << "Criando LCR..." << endl;
        //cout << "Peso minimo: " << peso_minimo << endl;
        //cout << "arestasOrdenadas.size(): " << arestasOrdenadas.size() << ", lcr.size(): "<< lcr.size() << endl;
        for(int i = 0; i < arestasOrdenadas.size(); i++)
        {
            if(arestasOrdenadas[i].second->peso <= peso_minimo)
            {
                lcr.push_back(arestasOrdenadas[i]);
            }
            else break;
        }

        //cout << "arestasOrdenadas.size(): " << arestasOrdenadas.size() << ", lcr.size(): "<< lcr.size() << endl;
        //cout << "Adicionados ao LCR:" << endl;
        //for(int i = 0; i < lcr.size(); i++){
        //    cout << lcr[i].first <<" "<<lcr[i].second->id << " " << lcr[i].second->peso << endl;
        //}

        int selected = -1;

        while(selected == -1 && lcr.size() > 0)
        {
            int min_range = 0;
            int max_range = lcr.size()-1;
            //cout << "Range: " << min_range << ", " << max_range << endl;

            selected = rand() % (max_range-min_range+1) + min_range;
            //cout << "Aresta selecionada:" << lcr[selected].first <<" "<<lcr[selected].second->id << " " << lcr[selected].second->peso << endl;

            int id_node_1 = lcr[selected].first;
            int id_node_2 = lcr[selected].second->id;
            int peso = lcr[selected].second->peso;

            int part1 = getParticao(id_node_1);
            int part2 = getParticao(id_node_2);

            //cout << "Node 1 (particao "<< part1 <<"): " << id_node_1 << ", Node 2 (particao "<< part2<< "): " << id_node_2 << ", peso: " << peso << endl;

            if(part1 != part2 &&
                    ((particoesPreenchidas[part1] == id_node_1 && particoesPreenchidas[part2] == -1) ||
                     (particoesPreenchidas[part1] == -1 && particoesPreenchidas[part2] == id_node_2) ||
                     (particoesPreenchidas[part1] == -1 && particoesPreenchidas[part2] == -1)))
            {
                //cout << "Adicionado!" << endl;
                selected_edges.push_back(lcr[selected]);
                particoesPreenchidas[part1] = id_node_1;
                particoesPreenchidas[part2] = id_node_2;
                arestasOrdenadas.erase(std::remove(arestasOrdenadas.begin(), arestasOrdenadas.end(), lcr[selected]), arestasOrdenadas.end());
            }
            else
            {
                arestasOrdenadas.erase(std::remove(arestasOrdenadas.begin(), arestasOrdenadas.end(), lcr[selected]), arestasOrdenadas.end());
                //cout << "Não adicionado, nós na mesma partição ou em partição repetida." << endl;
                //cout << "arestasOrdenadas.size(): " << arestasOrdenadas.size() <<  endl;
                lcr.erase(lcr.begin() + selected);

                selected = -1;

            }
        }

        //cout << "Finished iteration. arestasOrdenadas.size(): " << arestasOrdenadas.size() <<  endl;

    }

    cout << "Arvore montada com Guloso Randômico Reativo com alpha " << alpha << endl;
    for(int i = 0; i < selected_edges.size(); i++)
    {
        cout <<  selected_edges[i].first <<" "<< selected_edges[i].second->id << " " << selected_edges[i].second->peso << endl;
    }


}



int Grafo::getParticao(int id)
{
    //cout << "ID: " << id << endl;

    int range = 1;
    int counter = 0;

    for(vector<int>::iterator it = particoes.begin(); it != particoes.end(); it++)
    {

        int min_range = range;
        int max_range = *it + range - 1;

        //cout << "Range: " << min_range << ", " << max_range << endl;

        if(id >= min_range && id <= max_range)
            return counter;

        range += *it;
        counter += 1;
    }

}

Grafo::~Grafo()
{
    for(listaVertices::iterator v = lista_vertices.begin(); v != lista_vertices.end(); v++)
    {
        //cout << "Cleaning object " << v->id << endl;
    }
    lista_vertices.clear();
}
