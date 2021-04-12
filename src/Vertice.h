//
// Created by fernando on 02/04/2021.
//

#ifndef TRABED2___2020_2_VERTICE_H
#define TRABED2___2020_2_VERTICE_H

typedef struct vertice Vertice;

Vertice* inicializaVertice(int id);
int retornaId(Vertice* v);
double retornaDistancia(Vertice* v);
void liberaVertice(Vertice* v);
void inicializaDistancia(Vertice* v, double dis);


#endif //TRABED2___2020_2_VERTICE_H
