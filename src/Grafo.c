//
// Created by fernando,igor,vitor on 28/03/2021.
//
#include "Grafo.h"
#include "Vertice.h"
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

//Estrutura para armazenamento do grafo e suas componentes.
struct grafo{
    int qtdServidor, qtdCliente, qtdMonitor;
    int* Servidores, *Clientes, *Monitores;
    ListaAresta** arestas; // Lista de adjacencias
    Vertice** vertices;
    int nVertices;
};

Grafo* inicializaGrafo(int nVertices, int qtdServidor, int qtdCliente, int qtdMonitor) {

    Grafo *novo = malloc(sizeof(*novo));

    //Aresta é uma matriz de adjacências.
    novo->arestas = malloc(nVertices * sizeof(ListaAresta *));
    novo->nVertices = nVertices;

    novo->vertices = malloc(sizeof(Vertice*) * nVertices);

    for (int i = 0; i < nVertices; i++){
        novo->arestas[i] = iniciaListaAresta();
        novo->vertices[i] = inicializaVertice(i);
    }

    novo->qtdServidor = qtdServidor;
    novo->qtdCliente  = qtdCliente;
    novo->qtdMonitor  = qtdMonitor;

    novo->Servidores = malloc(qtdServidor * sizeof(int));
    novo->Clientes   = malloc(qtdCliente * sizeof(int));
    novo->Monitores  = malloc(qtdMonitor * sizeof(int));

    return novo;

}

//Retorna o vértice de um Id específico.
Vertice* retornaVerticeId(Grafo* g,int id){ return g->vertices[id]; }

//Retorna a quantidade de vértices do grafo.
int retornaNumVertices(Grafo* g) { return g->nVertices; }

//Retorna a quantidade de servidores do grafo.
int retornaQtdServidor(Grafo* g) { return g->qtdServidor; }
//Retorna o servidor de um id específico.
int retornaServidor(Grafo* g, int i) { return g->Servidores[i]; }

//Retorna a quantidade de clientes do grafo.
int retornaQtdCliente(Grafo* g) { return g->qtdCliente; }
//Retorna o cliente de um id específico.
int retornaCliente(Grafo* g, int i) { return g->Clientes[i]; }

//Retorna a quantidade de monitores do grafo.
int retornaQtdMonitor(Grafo* g) { return g->qtdMonitor; }
//Retorna o monitor de um id específico.
int retornaMonitor(Grafo* g, int i) { return g->Monitores[i]; }

//Adiciona um servidor, em um determinado indice, no vetor de servidores.
void adicionaServidor(Grafo * g, int servidor, int indice){
    g->Servidores[indice] = servidor;
}

//Adiciona um cliente, em um determinado indice, no vetor de clientes.
void adicionaCliente(Grafo * g, int cliente, int indice){
    g->Clientes[indice] = cliente;
}

//Adiciona um monitor, em um determinado indice, no vetor de monitores.
void adicionaMonitor(Grafo * g, int monitor, int indice){
    g->Monitores[indice] = monitor;
}

//Adiciona uma aresta, na lista de arestas de um determinado vertice, cujo indice é passado como parâmetro (fonte).
void grafoAdicionaAresta(Grafo* grafo, int fonte, Aresta* aresta){
    grafo->arestas[fonte] = adicionaAresta(grafo->arestas[fonte], aresta);
}

//Libera a parte do grafo que armazena os vértices e as arestas.
//Afim de poupar memória na alocação do vetor de RTT's.
void liberaGrafo1(Grafo* grafo){

    for(int i = 0; i < grafo->nVertices; i++)
        liberaListaAresta(grafo->arestas[i]);

    free(grafo->arestas);

    for (int i=0; i < grafo->nVertices; i++) liberaVertice(grafo->vertices[i]);
    free(grafo->vertices);

}

//Libera as estruturas relativas aos servidores, clientes e monitores, finalizando a estrutura grafo.
void liberaGrafo2(Grafo* grafo){

    free(grafo->Servidores);
    free(grafo->Clientes);
    free(grafo->Monitores);

    free(grafo);

}

//
//FUNÇÕES DE DIJKSTRA
//

//Inicializa as distâncias de todos os vértices do grafo para infinito, menos a fonte.
static void inicializa_single_sorce(Grafo* g, int fonte){
    for(int i = 0;i < g->nVertices; i++){
        inicializaDistancia(g->vertices[i], INF);
    }

    inicializaDistancia(g->vertices[fonte],0);
}

//Função para relaxar uma aresta.
static void relax(Vertice * u, Vertice * v, double dist, Heap* heap,Grafo *g){
    if(retornaDistancia(v) > (retornaDistancia(u) + dist)) {
        inicializaDistancia(v, (retornaDistancia(u) + dist));
        heap_insert(heap,g->vertices[retornaId(v)]);
    }
}

double* dijkstra(Grafo* g,int fonte){

    //Inicializa os vértices.
    inicializa_single_sorce(g,fonte);

    //Cria a heap do tamanho adequado.
    Heap* h = inicializaHeap(g->nVertices);

    //Insere na heap a fonte onde começa a ordenação.
    heap_insert(h,g->vertices[fonte]);

    while(!heap_isEmpty(h)){

        //Remove da heap o vértice com a menor distância.
        Vertice* u = heap_delmin(h);

        //Pega a lista de adjacências do vértice selecionado.
        ListaAresta* listaAdjU = g->arestas[retornaId(u)];

        //Relaxa as arestas.
        for(; listaAdjU != NULL; listaAdjU = retornaListaAresta(listaAdjU)){
            Aresta* ar = retornaAresta(listaAdjU);
            relax(u, retornaVerticeDaAresta(ar), retornaPesoDaAresta(ar), h, g);
        }
    }
    freeHeap(h);

    //Cria um vetor de doubles para armazenar as menores distâncias.
    double* distancias = malloc(g->nVertices * sizeof(double));

    for(int i=0; i<g->nVertices; i++) {
        distancias[i] = retornaDistancia(g->vertices[i]);
    }

    //Retorna o vetor de menor distância.
    return distancias;

}