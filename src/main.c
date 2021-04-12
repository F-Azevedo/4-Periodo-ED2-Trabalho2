//
// Created by Fernando,Igor,Vitor on 23/03/2021.
//
#include <stdio.h>
#include "Grafo.h"
#include "RTT.h"

Grafo* leitura(char* nomeArquivo);
void calculaDistancias(Atalhos* at, Grafo* g);

int main(int argc, char* argv[]){

    //Faz a leitura do grafo do arquivo passado como parâmetro.
    Grafo* grafo = leitura(argv[1]);

    //Inicializa nossa matriz de atalhos com NULL.
    Atalhos* at = inicializaAtalhos(grafo);

    //Faz o Dijkstra para os Servidores, Clientes e Monitores e os insere na matriz de atalhos.
    calculaDistancias(at, grafo);

    //Libera as partes relacionadas ao armazenamento dos vértices e arestas para otimizar o espaço utilizado.
    liberaGrafo1(grafo);

    //Calcula e imprime os RTT's finais.
    calculaTodosRTTFinal(at, grafo);

    //Libera as partes de grafo que identifica quem é Servidor, Monitor e Cliente.
    liberaGrafo2(grafo);

    //Libera a matriz degenerada de atalhos.
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
    //Insere as arestas de cada vértice do grafo.
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

    //Calcular para os Servidores.
    for(int j=0; j < retornaQtdServidor(grafo); j++){
        insereLinhaAtalho(atalhos, dijkstra(grafo, retornaServidor(grafo, j)), retornaServidor(grafo, j));
    }
    //Calcular para os Clientes.
    for(int j=0; j < retornaQtdCliente(grafo); j++){
        insereLinhaAtalho(atalhos, dijkstra(grafo, retornaCliente(grafo, j)), retornaCliente(grafo, j));
    }
    //Calcular para os Monitores.
    for(int j=0; j < retornaQtdMonitor(grafo); j++){
        insereLinhaAtalho(atalhos, dijkstra(grafo, retornaMonitor(grafo, j)), retornaMonitor(grafo, j));
    }
}