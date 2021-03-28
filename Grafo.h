//
// Created by fernando,igor,vitor on 28/03/2021.
//
#ifndef TRABED2_2020_2_GRAFO_H
#define TRABED2_2020_2_GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include "ListaAresta.h"

typedef struct grafo Grafo;

Grafo* inicializaGrafo(int nVertices,int qtdServidor,int qtdCliente, int qtdMonitor);
void grafoAdicionaAresta(Grafo* grafo, int fonte, Aresta* aresta);
void adicionaServidor(Grafo * g, int servidor, int indice);
void adicionaCliente(Grafo * g, int cliente, int indice);
void adicionaMonitor(Grafo * g, int monitor, int indice);
void imprimeGrafo(Grafo* grafo);


#endif //TRABED2_2020_2_GRAFO_H
