//
// Created by fernando,igor,vitor on 28/03/2021.
//
#include "Grafo.h"
#include "Vertice.h"
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

struct grafo{
    int qtdServidor, qtdCliente, qtdMonitor;
    int* Servidores, *Clientes, *Monitores;
    ListaAresta** arestas; // Lista de adjacencias
    Vertice** vertices;
    int nVertices;
};

Grafo* inicializaGrafo(int nVertices,int qtdServidor,int qtdCliente, int qtdMonitor) {

    Grafo *novo = malloc(sizeof(*novo));

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

Vertice* retornaVerticeId(Grafo* g,int id){ return g->vertices[id]; }

int retornaNumVertices(Grafo* g) { return g->nVertices; }

int retornaQtdServidor(Grafo* g) { return g->qtdServidor; }
int retornaServidor(Grafo* g, int i) { return g->Servidores[i]; }

int retornaQtdCliente(Grafo* g) { return g->qtdCliente; }
int retornaCliente(Grafo* g, int i) { return g->Clientes[i]; }

int retornaQtdMonitor(Grafo* g) { return g->qtdMonitor; }
int retornaMonitor(Grafo* g, int i) { return g->Monitores[i]; }

void adicionaServidor(Grafo * g, int servidor, int indice){

    g->Servidores[indice] = servidor;

}

void adicionaCliente(Grafo * g, int cliente, int indice){

    g->Clientes[indice] = cliente;

}

void adicionaMonitor(Grafo * g, int monitor, int indice){

    g->Monitores[indice] = monitor;

}

void grafoAdicionaAresta(Grafo* grafo, int fonte, Aresta* aresta){

    grafo->arestas[fonte] = adicionaAresta(grafo->arestas[fonte], aresta);

}

void imprimeGrafo(Grafo* grafo){

    printf("QTD servidor = %d\n", grafo->qtdServidor);
    for(int i = 0; i < grafo->qtdServidor; i++)
        printf("Servidor = %d\n", grafo->Servidores[i]);

    printf("QTD cliente = %d\n",grafo->qtdCliente);
    for(int i = 0;i< grafo->qtdCliente;i++){
        printf("Cliente = %d\n",grafo->Clientes[i]);
    }

    printf("QTD monitor = %d\n", grafo->qtdMonitor);
    for (int i=0; i < grafo->qtdMonitor; i++) printf("Monitor: %d\n", grafo->Monitores[i]);

    printf("\n");
    for(int i = 0; i < grafo->nVertices; i++){
        printf("Vertice %d:\n", i);
        imprimeLista(grafo->arestas[i]);
        printf("\n");
    }
}

void liberaGrafo(Grafo* grafo){

    for(int i = 0; i < grafo->nVertices; i++)
        liberaListaAresta(grafo->arestas[i]);

    free(grafo->arestas);

    free(grafo->Servidores);
    free(grafo->Clientes);
    free(grafo->Monitores);

    for (int i=0; i < grafo->nVertices; i++) liberaVertice(grafo->vertices[i]);
    free(grafo->vertices);
    free(grafo);

}

//
//FUNÇÕES DE DIJKSTRA
//

static void inicializa_single_sorce(Grafo* g, int fonte){
    for(int i = 0;i < g->nVertices; i++){
        inicializaDistancia(g->vertices[i], INF);
    }

    inicializaDistancia(g->vertices[fonte],0);
}

static void relax(Vertice * u, Vertice * v, double dist, Heap* heap,Grafo *g){
    if(retornaDistancia(v) > (retornaDistancia(u) + dist)) {
        inicializaDistancia(v, (retornaDistancia(u) + dist));
        heap_insert(heap,g->vertices[retornaId(v)]);
    }
}

double* dijkstra(Grafo* g,int fonte){

    inicializa_single_sorce(g,fonte);

    Heap* h = inicializaHeap(g->nVertices);

    heap_insert(h,g->vertices[fonte]);

    while(!heap_isEmpty(h)){

        Vertice* u = heap_delmin(h);
        ListaAresta* listaAdjU = g->arestas[retornaId(u)];

        for(listaAdjU ; listaAdjU != NULL; listaAdjU = retornaListaAresta(listaAdjU)){
            Aresta* ar = retornaAresta(listaAdjU);
            relax(u, retornaVerticeDaAresta(ar), retornaPesoDaAresta(ar), h, g);
        }
    }
    freeHeap(h);

    double* distancias = malloc(g->nVertices * sizeof(double));

    for(int i=0; i<g->nVertices; i++) {
        distancias[i] = retornaDistancia(g->vertices[i]);
    }

    return distancias;

}