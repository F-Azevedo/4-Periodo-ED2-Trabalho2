//
// Created by fernando on 28/03/2021.
//

#ifndef TRABED2___2020_2_ARESTA_H
#define TRABED2___2020_2_ARESTA_H

typedef struct aresta Aresta;

Aresta* iniciaAresta(int destino, double peso);
void liberaAresta(Aresta* aresta);
void imprimeAresta(Aresta* aresta);

#endif //TRABED2___2020_2_ARESTA_H
