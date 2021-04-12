//
// Created by fernando on 28/03/2021.
//

#include "ListaAresta.h"
#include <stdlib.h>

//Struct da célula da lista de arestas.
struct listaAresta{
    Aresta* aresta;
    ListaAresta * prox;
};

//Retorna a aresta de uma célula.
Aresta* retornaAresta(ListaAresta* lista){
    return lista->aresta;
}

//Retorna a proxima célula da lista.
ListaAresta* retornaListaAresta(ListaAresta* lista){
    return lista->prox;
}

ListaAresta* iniciaListaAresta() {
    return NULL;
}

//Adiciona uma nova aresta, adiciona no inicio.
ListaAresta* adicionaAresta(ListaAresta* lista, Aresta* aresta){

    ListaAresta* nova = malloc(sizeof(*nova));

    // Adiciona a nova célula na primeira posição da lista.
    nova->aresta = aresta;
    nova->prox = lista;

    return nova;

}

//Libera a lista de arestas recursivamente.
void liberaListaAresta(ListaAresta* lista){

    if (lista) {
        liberaListaAresta(lista->prox);
        liberaAresta(lista->aresta);
        free(lista);
    }

}