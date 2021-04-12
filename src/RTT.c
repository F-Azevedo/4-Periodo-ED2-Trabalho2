//
// Created by fernando on 02/04/2021.
//

#include "RTT.h"
#include "Grafo.h"
#include <limits.h>

#define INF INT_MAX

struct atalhos{
    double** mat;
    int nlin;
};

// Inicializa um struct atalhos que basicamente é
// uma matriz degenerada de doubles na qual mat[a][b] é a menor distãncia
// entre um vértice a com um vértice b.
// Na matriz, só existiram as linhas em que mat[a] seja um Servidor, Cliente ou Monitor.
Atalhos * inicializaAtalhos(Grafo* g){

    Atalhos * novo = malloc(sizeof(*novo));

    novo->nlin = retornaNumVertices(g);

    novo->mat = malloc(sizeof(double*) * novo->nlin);

    // Inicializa todas as linha como NULL
    for (int i=0; i < novo->nlin; i++) novo->mat[i] = NULL;

    return novo;
}

// Insere um vetor de doubles já alocados nos atalhos.
void insereLinhaAtalho(Atalhos* at, double* vet, int i){
    at->mat[i] = vet;
}

// Retorna o RTT real entre o vértice p e o vértice q.
double RTT(Atalhos * a, int p, int  q){
    return a->mat[p][q] + a->mat[q][p];
}

//Função para calcular o RTT_Relativo.
double RTT_Relativo(Atalhos* a, int p, int q, Grafo* grafo){

    //Seta o minimo como infinito para pegar o menor valor.
    double minimo = INF;

    for(int i = 0; i < retornaQtdMonitor(grafo); i++) {
        int j = retornaMonitor(grafo, i);
        //Calcula um RTT relativo passando por um monitor.
        double relativo = (RTT(a, p, j) + RTT(a, j, q));
        //Atribui à minimo o valor do minimo entre minimo e o novo RTT_Relativo.
        if (minimo > relativo) minimo = relativo;
    }

    return minimo;
}

//Função para calcular o RTT_FINAL.
double RTT_Final(Atalhos * at, int p, int q, Grafo * g){

    return RTT_Relativo(at, p, q, g) / RTT(at, p, q);

}

//Função para liberar nossa matriz degenerada de distâncias mínimas.
void liberaAtalhos(Atalhos * at){

    //Se a posição da matriz não é NULL libera a linha.
    for (int i=0; i < at->nlin; i++) if (at->mat[i]) free(at->mat[i]);
    free(at->mat);
    free(at);
}

//Struct para armazenar as informações de um RTT para fazer a ordenação.
typedef struct rtt{
  int orig;
  int dest;
  double info;
}infoRTT;

//Função auxiliar para ordenar a estrutura de RTT's.
int compRTT(const void *a, const void *b){
    infoRTT const* A = a;
    infoRTT const* B = b;

    //Compara o RTT.
    if((*A).info > (*B).info) return 1;
    //Se for igual compara a origem.
    else if((*A).info == (*B).info){
        if((*A).orig > (*B).orig)
            return 1;
        //Se for igual compara o destino.
        else if((*A).orig == (*B).orig) {
            if ((*A).dest > (*B).dest)
                return 1;
        }
        return 0;
    }
    else return -1;
}

//Função para calcular e imprimir os RTT's finais ordenados.
void calculaTodosRTTFinal(Atalhos * at, Grafo * grafo){

    //Cria um vetor de tamanho |S|*|C| de infoRTT.
    infoRTT* listaRTT = malloc(sizeof(infoRTT) * (retornaQtdServidor(grafo) * retornaQtdCliente(grafo)));

    //Calcula rtt real.
    int k = 0;
    for(int i = 0; i < retornaQtdServidor(grafo); i++){
        for(int j = 0; j < retornaQtdCliente(grafo); j++) {
            listaRTT[k].orig = retornaServidor(grafo,i);
            listaRTT[k].dest = retornaCliente(grafo,j);
            listaRTT[k++].info = RTT_Final(at, retornaServidor(grafo,i), retornaCliente(grafo,j), grafo);
        }
    }

    //Ordena o vetor de RTT's.
    qsort(listaRTT, k, sizeof(listaRTT[0]), compRTT);

    //Imprime os RTT's ordenados.
    for(int i=0; i<k; i++) {
        printf("%d %d %.16lf\n", listaRTT[i].orig, listaRTT[i].dest, listaRTT[i].info);
    }

    //Libera os RTT's.
    free(listaRTT);
}