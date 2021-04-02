#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
//
// Created by Fernando,Igor,Vitor on 23/03/2021.
//
#include <stdio.h>
#include "Grafo.h"
#include "RTT.h"



Grafo* leitura(char* nomeArquivo);

int main(int argc, char* argv[]){

    Grafo* grafo;

    grafo = leitura(argv[1]);

    Atalhos* at = inicializaAtalhos(grafo);

    int i=0;

    //Calcular para as fontes
    for(int j=0; j < retornaQtdServidor(grafo); j++){
        insereLinhaAtalho(at, dijkstra(grafo, retornaServidor(grafo, j)), retornaServidor(grafo, j));
    }
    //Calcular para os clientes
    for(int j=0; j < retornaQtdCliente(grafo); j++){
        insereLinhaAtalho(at, dijkstra(grafo, retornaCliente(grafo, j)), retornaCliente(grafo, j));
    }
    //Calcular para os monitores
    for(int j=0; j < retornaQtdMonitor(grafo); j++){
        insereLinhaAtalho(at, dijkstra(grafo, retornaMonitor(grafo, j)), retornaMonitor(grafo, j));
    }

    imprimeAtalhos(at);

    //Calcula rtt real
    double RTT_FINAL = 0;
    for(i = 0; i < retornaQtdServidor(grafo); i++){
        for(int j = 0; j < retornaQtdCliente(grafo); j++) {
            RTT_FINAL = RTT_Final(at, retornaServidor(grafo,i), retornaCliente(grafo,j), grafo);
            printf("%d %d %.16lf\n", retornaServidor(grafo,i), retornaCliente(grafo,j), RTT_FINAL);
        }
    }
    printf("\n\n");

    //imprimeGrafo(grafo);
    liberaGrafo(grafo);

    return 0;
}

Grafo* leitura(char* nomeArquivo){

    FILE* f = fopen(nomeArquivo,"r");
    if (!f){ perror("Erro ao abrir arquivo de entrada"); exit(1); }

    int nVertices, nArestas;
    int qtdServidor, qtdCliente, qtdMonitor;

    //Lê quantidade de vértices e arestas.
    fscanf(f, "%d %d", &nVertices, &nArestas);
    //Lê quantidade de vértices servidores, clientes e monitores.
    fscanf(f, "%d %d %d", &qtdServidor, &qtdCliente, &qtdMonitor);

    //Inicializa o grafo vazio.
    Grafo* grafo = inicializaGrafo(nVertices, qtdServidor, qtdCliente, qtdMonitor);

    //Insere os vértices servidores.
    for(int i = 0; i < qtdServidor; i++){
        int servidor;
        fscanf(f, "%d", &servidor);
        adicionaServidor(grafo, servidor, i);
    }
    //Insere os vértices clientes.
    for(int i = 0; i < qtdCliente; i++){
        int cliente;
        fscanf(f, "%d", &cliente);
        adicionaCliente(grafo, cliente, i);
    }
    //Insere os vértices monitores.
    for(int i = 0; i < qtdMonitor; i++){
        int monitor;
        fscanf(f, "%d", &monitor);
        adicionaMonitor(grafo, monitor, i);
    }

    Aresta* aresta;

    for(int i=0; i < nArestas; i++){
        int fonte, destino;
        long double peso;
        fscanf(f, "%d %d %LF",&fonte, &destino, &peso);
        aresta = iniciaAresta(retornaVerticeId(grafo, destino), peso);
        grafoAdicionaAresta(grafo, fonte, aresta);
    }

    fclose(f);
    return grafo;
}
/*

[   Servidor = 0
    Cliente = 4;
    Monitor = 1, 2;

    QtdLinhas = 4;
    QtdColunas = vertices = 5;

    matriz[QtdLInhas][QtdColunas];

    matriz[0] = dijkstra(grafo, fonte(0));
    matriz[1] = dijkstra(grafo, fonte(1));
    matriz[2] = dijkstra(grafo, fonte(2));
    matriz[3] = dijkstra(grafo, fonte(3));


    RTT(0, 4) return matriz[0, 4] + matriz[4, 0];

    RTT*(0, 4) retrun( MIN(RTT(0, 1) + RTT(1, 4), RTT(0, 2) + RTT(2, 4)))
        matriz{
        vertice 0 = [0, 1, 2, 3, 4],
        vertice 1 = [0, 1, 2, 3, 4],
        vertice 2 = [0, 1, 2, 3, 4],
        vertice 4 = [0, 1, 2, 3, 4]
                }
]
*/
#pragma clang diagnostic pop