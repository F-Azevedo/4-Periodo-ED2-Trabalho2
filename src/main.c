#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
//
// Created by Fernando,Igor,Vitor on 23/03/2021.
//
#include <stdio.h>
#include "Grafo.h"
#include "RTT.h"

Grafo* leitura(char* nomeArquivo);
void calculaDistancias(Atalhos* at, Grafo* g);

int main(int argc, char* argv[]){

    Grafo* grafo;
    grafo = leitura(argv[1]);
    Atalhos* at = inicializaAtalhos(grafo);
    calculaDistancias(at, grafo);
    liberaGrafo1(grafo);
    //imprimeAtalhos(at);
    calculaTodosRTTFinal(at, grafo);
    //printf("\n\n");
    //imprimeGrafo(grafo);
    liberaGrafo2(grafo);
    liberaAtalhos(at);

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
        double peso;
        fscanf(f, "%d %d %lf",&fonte, &destino, &peso);
        aresta = iniciaAresta(retornaVerticeId(grafo, destino), peso);
        grafoAdicionaAresta(grafo, fonte, aresta);
    }

    fclose(f);
    return grafo;
}

void calculaDistancias(Atalhos* atalhos, Grafo* grafo){

    //Calcular para as fontes
    for(int j=0; j < retornaQtdServidor(grafo); j++){
        insereLinhaAtalho(atalhos, dijkstra(grafo, retornaServidor(grafo, j)), retornaServidor(grafo, j));
    }
    //Calcular para os clientes
    for(int j=0; j < retornaQtdCliente(grafo); j++){
        insereLinhaAtalho(atalhos, dijkstra(grafo, retornaCliente(grafo, j)), retornaCliente(grafo, j));
    }
    //Calcular para os monitores
    for(int j=0; j < retornaQtdMonitor(grafo); j++){
        insereLinhaAtalho(atalhos, dijkstra(grafo, retornaMonitor(grafo, j)), retornaMonitor(grafo, j));
    }
}

#pragma clang diagnostic pop