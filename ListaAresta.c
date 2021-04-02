//
// Created by fernando on 28/03/2021.
//

#include "ListaAresta.h"
#include <stdlib.h>

struct listaAresta{
    Aresta* aresta;
    ListaAresta * prox;
};

Aresta* retornaAresta(ListaAresta* lista){
    return lista->aresta;
}

ListaAresta* retornaListaAresta(ListaAresta* lista){
    return lista->prox;
}

ListaAresta* iniciaListaAresta() {
    return NULL;
}
ListaAresta* adicionaAresta(ListaAresta* lista, Aresta* aresta){

    ListaAresta* nova = malloc(sizeof(*nova));

    // Adiciona a nova lista na primeira posição
    nova->aresta = aresta;
    nova->prox = lista;

    return nova;

}

void imprimeLista(ListaAresta* lista){

    if (lista){ imprimeAresta(lista->aresta); imprimeLista(lista->prox); }
}

void liberaListaAresta(ListaAresta* lista){

    if (lista) {
        liberaListaAresta(lista->prox);
        liberaAresta(lista->aresta);
        free(lista);
    }

}