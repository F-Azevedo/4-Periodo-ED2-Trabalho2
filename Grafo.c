//
// Created by fernando,igor,vitor on 28/03/2021.
//
#include "Grafo.h"
#include <stdlib.h>

// O vértice terá um vetor de tamanho V que representará

struct grafo{
    int qtdServidor, qtdCliente, qtdMonitor;
    int* Servidores, *Clientes, *Monitores;
    ListaAresta** arestas;
    int nVertices;
};

Grafo* inicializaGrafo(int nVertices,int qtdServidor,int qtdCliente, int qtdMonitor) {

    Grafo *novo = malloc(sizeof(*novo));

    novo->arestas = malloc(nVertices * sizeof(ListaAresta *));
    novo->nVertices = nVertices;

    for (int i = 0; i < nVertices; i++)
        novo->arestas[i] = iniciaListaAresta();

    novo->qtdServidor = qtdServidor;
    novo->qtdCliente  = qtdCliente;
    novo->qtdMonitor  = qtdMonitor;

    novo->Servidores = malloc(qtdServidor * sizeof(int));
    novo->Clientes   = malloc(qtdCliente * sizeof(int));
    novo->Monitores  = malloc(qtdMonitor * sizeof(int));

    return novo;

}

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

    free(grafo);

}

void dijkstra(Grafo* grafo,int dest,int ori){

    Heap* h = inicializaHeap(grafo->nVertices);

    for(int i = 0;i < grafo->nVertices; i++){


    }



}