//
// Created by fernando on 28/03/2021.
//

#include "Aresta.h"
#include <stdlib.h>
#include <stdio.h>

struct aresta{
    int destino;
    double peso;
};

// Inicia Aresta direcionada com peso
Aresta* iniciaAresta(int destino, double peso){

    Aresta* novo = (Aresta*) malloc(sizeof(Aresta));

    novo->destino = destino;
    novo->peso = peso;

    return novo;

}

void liberaAresta(Aresta* aresta) {
    free(aresta);
}

void imprimeAresta(Aresta* aresta){
    printf("%d %lf\n", aresta->destino, aresta->peso);
}
