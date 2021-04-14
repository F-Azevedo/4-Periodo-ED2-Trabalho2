# Trabalho 2 - Estrutura de Dados 2
###### Universidade Federal do Espirito Santo

---
### Autores:
* Fernando Azevedo Peres
* Igor Mattos dos Santos Varejão
* Vitor Berger Bonella

### Data:
Abril de 2021 <br>
4° Período (2020/2)

---
### Descrição:
O objetivo deste trabalho e aplicar o algoritmo de Dijkstra em um contexto relacionado a redes de computadores.

RTT é a soma do menor caminho de ida e volta de um determinado vértice a outro.

RTT_real é o RTT entre os vértices (a, b) diretamente.

RTT_relativo é o menor RTT entre os vértices (a, b) passando por algum monitor.

![Erro](https://github.com/F-Azevedo/4-Periodo-ED2-Trabalho2/blob/main/Descrição.png "Descrição")

O objetivo desse trabalho é calcular a inflação nesse RTT, que é calculado dividindo o RTT_relativo pelo RTT_real.

---
### Resolução
Para a execução desse código é necessário que seja passado como parâmetro o arquivo onde se encontra a especificação do grafo, conforme espeficicado no PDF.

Implementamos uma estrutura Grafo.
Essa estrutura contém: um vetor de vértices, uma lista de adjacências (que representa as arestas de cada vértice), e 3 vetores, de servidores, de clientes e monitores.

Armazenado o grafo, calculamos o Dijkstra de todos os vertices que são servidores, clientes ou monitores e os armazenamos em uma matriz degenerada.

Tendo essa matriz, onde cada linha represente o menor caminho de um vértice à todos os outros, só basta calcular os RTT's.