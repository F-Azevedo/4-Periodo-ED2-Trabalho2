//
// Created by fernando on 30/03/2021.
//

#include "Heap.h"
#include <stdio.h>
#include <stdlib.h>

#define key(A) retornaDistancia(A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { Vertice* t = A; A = B; B = t; }
#define compexch(A, B) if (less(B, A)) exch(A, B)

struct heap{Vertice** vet; int size;};

Heap* inicializaHeap(int tam){
    Heap* heap = malloc(sizeof(*heap));
    heap->vet = malloc((tam+1) * sizeof(Vertice*));
    heap->size = 0;
    return heap;
}

void fix_up(Heap* heap, int k){
    while (k > 1 && less(heap->vet[k], heap->vet[k/2])){
        exch(heap->vet[k/2], heap->vet[k]);
        k /= 2;
    }
}

void fix_down(Heap* heap, int k){
    while(2 * k <= heap->size){
        int j = 2 * k;
        if (j < heap->size && less(heap->vet[j+1], heap->vet[j]))
            j++;
        if(!less(heap->vet[j], heap->vet[k]))
            break;
        exch(heap->vet[j], heap->vet[k]);
        k = j;
    }
}

void heap_insert(Heap* heap, Vertice* chave){
    heap->size++;
    heap->vet[heap->size] = chave;
    fix_up(heap, heap->size);
}

Vertice* heap_delmin(Heap* heap){
    Vertice* min = heap->vet[1];
    exch(heap->vet[1], heap->vet[heap->size]);
    heap->size--;
    fix_down(heap, 1);
    return min;
}

int heap_isEmpty(Heap* heap){ return heap->size == 0 ? 1: 0; }

void freeHeap(Heap* heap){
    free(heap->vet);
    free(heap);
}

void printHeap(Heap* heap){
    printf("\n\nArray look:\n");
    for (int i=1; i <= heap->size; i++) imprimeVertice(heap->vet[i]);
    printf("\n\n");
}

