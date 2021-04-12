//
// Created by fernando on 28/03/2021.
//

#include "Aresta.h"
#include <stdlib.h>

//Aresta só tem o vértice de destino pois ela estara na lista de arestas relativa ao vértice de origem.
struct aresta{
    Vertice* destino;
    double peso;
};

// Inicia Aresta direcionada com peso.
Aresta* iniciaAresta(Vertice* destino, double peso){
    Aresta* novo = (Aresta*) malloc(sizeof(Aresta));

    novo->destino = destino;
    novo->peso = peso;

    return novo;
}

Vertice* retornaVerticeDaAresta(Aresta * a){ return a->destino; }

double retornaPesoDaAresta(Aresta * a){ return a->peso; }

void liberaAresta(Aresta* aresta) {
    free(aresta);
}