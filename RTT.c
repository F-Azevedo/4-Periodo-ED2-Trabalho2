//
// Created by fernando on 02/04/2021.
//

#include "RTT.h"
#include "Grafo.h"

#include <limits.h>

#define INF INT_MAX

#define RED "\033[95m"
#define RESET "\033[0m"

struct atalhos{

    double** mat;
    int ncol, nlin;

};

// Inicializa um struct atalhos que basicamente é
// uma matriz de doubles na qual mat[a][b] é a menor distãncia
// entre um vértice a com um vértice b.
Atalhos * inicializaAtalhos(Grafo* g){

    Atalhos * novo = malloc(sizeof(*novo));
    //novo->nlin = retornaQtdCliente(g) + retornaQtdServidor(g) + retornaQtdMonitor(g);
    novo->nlin = retornaNumVertices(g);
    novo->ncol = retornaNumVertices(g);
    novo->mat = malloc(sizeof(double*) * novo->nlin);
    return novo;
}

// Insere um vetor de doubles já alocados nos atalhos
void insereLinhaAtalho(Atalhos* at, double* vet, int i){
    at->mat[i] = vet;
}

// Retorna o RTT padrão entre o vértice p e o vértice q
double RTT(Atalhos * a, int p, int  q){
    return a->mat[p][q] + a->mat[q][p];
}

double RTT_Relativo(Atalhos* a, int p, int q, Grafo* grafo){

    double minimo = INF;

    for(int i = 0; i < retornaQtdMonitor(grafo); i++) {
        int j = retornaMonitor(grafo, i);
        double relativo = (RTT(a, p, j) + RTT(a, j, q));
        if (minimo > relativo) minimo = relativo;
    }

    return minimo;
}

double RTT_Final(Atalhos * at, int p, int q, Grafo * g){

    return RTT_Relativo(at, p, q, g) / RTT(at, p, q);
}

void imprimeAtalhos(Atalhos * at){

    printf(RED "Atalhos:" RESET "\n");
    for (int i=0; i < at->nlin; i++) {
        if(at->mat[i] != NULL) {
            for (int j = 0; j < at->ncol; j++) printf("%.1lf ", at->mat[i][j]);

            printf("\n");
        }
    }

}

void liberaAtalhos(Atalhos * at){

    for (int i=0; i < at->nlin; i++) free(at->mat[i]);
    free(at->mat);
    free(at);
}