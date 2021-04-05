//
// Created by fernando on 28/03/2021.
//

#include "Aresta.h"
#include <stdlib.h>
#include <stdio.h>
#include "Corzinha.h"

struct aresta{
    Vertice* destino;
    double peso;
};

// Inicia Aresta direcionada com peso
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

void imprimeAresta(Aresta* aresta){
    printf(NORMAL VERDE "Aresta:\n" RESET);
    imprimeVertice(aresta->destino);
    //printf("Vertice id= %d\n", retornaId(aresta->destino));
    printf("Peso: %lf\n", aresta->peso);
}
