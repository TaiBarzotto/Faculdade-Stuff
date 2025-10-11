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
    void remove_aresta(Aresta e);
    void imprimir_grafo();
    void destruir_grafo();
    bool caminho(int v, int w, int marcado[], int nivel);
    void acha_sus(int v, int pai[], int dist[], int marcado[]);
};

#endif