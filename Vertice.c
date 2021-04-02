//
// Created by fernando on 02/04/2021.
//

#include "Vertice.h"
#include <stdio.h>
#include <stdlib.h>

struct vertice{
    double distancia;
    int id;
};

Vertice* inicializaVertice(int id){
    Vertice* novo = malloc(sizeof(*novo));
    novo->id = id;
    return novo;
}

int retornaId(Vertice* v){ return v->id; }

double retornaDistancia(Vertice* v){ return v->distancia; }

void inicializaDistancia(Vertice* v, double dis){ v->distancia = dis; }

void liberaVertice(Vertice* v){ free(v); }

void imprimeVertice(Vertice * v){
    printf("\033[94mVertice:\033[0m id = %d // distância %lf\n", v->id, v->distancia);
}