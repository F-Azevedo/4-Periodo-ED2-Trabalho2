//
// Created by fernando,igor,vitor on 28/03/2021.
//
#ifndef TRABED2_2020_2_GRAFO_H
#define TRABED2_2020_2_GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include "ListaAresta.h"
#include "Heap.h"

typedef struct grafo Grafo;
typedef struct vertice Vertice;

Grafo* inicializaGrafo(int nVertices,int qtdServidor,int qtdCliente, int qtdMonitor);
Vertice* retornaVerticeId(Grafo* g,int id);
int retornaNumVertices(Grafo* g);
int retornaQtdServidor(Grafo* g);
int retornaServidor(Grafo* g, int i);
int retornaQtdCliente(Grafo* g);
int retornaCliente(Grafo* g, int i);
int retornaQtdMonitor(Grafo* g);
int retornaMonitor(Grafo* g, int i);
void grafoAdicionaAresta(Grafo* grafo, int fonte, Aresta* aresta);
void adicionaServidor(Grafo* g, int servidor, int indice);
void adicionaCliente(Grafo* g, int cliente, int indice);
void adicionaMonitor(Grafo* g, int monitor, int indice);
void imprimeGrafo(Grafo* grafo);
void liberaGrafo1(Grafo* grafo);
void liberaGrafo2(Grafo* grafo);

//Funções de Dijkstra
double* dijkstra(Grafo* g,int fonte);

#endif //TRABED2_2020_2_GRAFO_H
