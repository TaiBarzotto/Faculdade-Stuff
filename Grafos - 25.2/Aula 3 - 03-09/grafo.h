#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include "aresta.h"
class Grafo
{
private:
    int num_aresta_;
    int num_vertices_;

    std::vector<std::vector<int>> matriz_adj_;
public:
    Grafo(int num_vertices);
    
    int get_vertices();
    int get_aresta();

    bool tem_aresta(Aresta e);
    void insere_aresta(Aresta e);
    void Grafo::remove_aresta(Aresta e);
    void Grafo::imprimir_grafo();
    void Grafo::destruir_grafo();
    bool Grafo::eh_passeio(vector<int> vertices);
    bool Grafo::eh_caminho(vector<int> vertices);
};

#endif