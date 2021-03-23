# Trabalho 2 de ED II
### Integrantes:
+ Fernando Azevedo Peres
+ Igor Mattos dos Santos Varejão
+ Vitor Berger Bonella

### Resumo:
```graphviz

   node [label="Servidor", shape=circle]; S;
   node [label="Cliente-1", shape=doublecircle]; C1;
   node [label="Cliente-2", shape=doublecircle]; C2;
   node [label="Cliente-3", shape=doublecircle]; C3;
   node [label="Monitor-1", shape=square]; M1;
   node [label="Monitor-2", shape=square]; M2;
   
   S -> M1 [label=10]
   S -> M2 [label=3]
   M1 -> C1 [label=14]
   M2 -> C2 [label=4]
   M2 -> C3 [label=23]

```
