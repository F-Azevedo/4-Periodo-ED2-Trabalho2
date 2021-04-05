//
// Created by fernando on 30/03/2021.
//

#ifndef TRABED2___2020_2_HEAP_H
#define TRABED2___2020_2_HEAP_H
#include "Vertice.h"
typedef struct heap Heap;


Heap* inicializaHeap(int tam);
void fix_up(Heap* heap,int k);
void fix_down(Heap* heap,int k);
void heap_insert(Heap* heap,Vertice* chave);
Vertice* heap_delmin(Heap* heap);
int heap_isEmpty(Heap* heap);
void printHeap(Heap* heap);
void freeHeap(Heap* heap);

#endif //TRABED2___2020_2_HEAP_H
