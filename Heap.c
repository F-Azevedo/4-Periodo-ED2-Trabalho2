//
// Created by fernando on 30/03/2021.
//

#include "Heap.h"
#include <stdio.h>
#include <stdlib.h>

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { int t = A; A = B; B = t; }
#define compexch(A, B) if (less(B, A)) exch(A, B)

struct heap{int* vet; int size;};

Heap* inicializaHeap(int tam){
    Heap* heap = malloc(sizeof(*heap));
    heap->vet = (int*) malloc((tam+1) * sizeof(int));
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

void heap_insert(Heap* heap,int chave){
    heap->size++;
    heap->vet[heap->size] = chave;
    fix_up(heap, heap->size);
}

int heap_delmin(Heap* heap){
    int min = heap->vet[1];
    exch(heap->vet[1], heap->vet[heap->size]);
    heap->size--;
    fix_down(heap, 1);
    return min;
}

void freeHeap(Heap* heap){
    free(heap->vet);
    free(heap);
}

void printHeap(Heap* heap){

    printf("\n\nArray look:\n");
    for (int i=1; i <= heap->size; i++) printf("%d, ", heap->vet[i]);
    printf("\n\n");
}

