/*
    Trabalho 1 - Potenciais comparsas
    GEN505 -  Grafos - 2025/02

    Nomes: Tainara, Wemely
    Matriculas: 20240017799, 20240008468
*/
#include "grafo.h"
#include <bits/stdc++.h>

using namespace std;

Grafo::Grafo(int num_vertices){
    num_vertices_ = num_vertices;
    num_aresta_ =0;

    matriz_adj_.resize(num_vertices);

    for (int i = 0; i < num_vertices; i++)
    {
        matriz_adj_[i].resize(num_vertices,0);
    }
    
}

int Grafo::get_aresta(){
    return num_aresta_;
}

int Grafo::get_vertices(){
    return num_vertices_;
}

bool Grafo::tem_aresta(Aresta e){
    if (matriz_adj_[e.v1][e.v2] != 0){
        return true;
    }
    return false;    
}

void Grafo::insere_aresta(Aresta e){
    if (!tem_aresta(e) && (e.v1 != e.v2))
    {
        matriz_adj_[e.v1][e.v2] = 1;
        matriz_adj_[e.v2][e.v1] = 1;
            
        num_aresta_++;
    }
}

void Grafo::remove_aresta(Aresta e){
    if (tem_aresta(e))
    {
        matriz_adj_[e.v1][e.v2] = 0;
        matriz_adj_[e.v2][e.v1] = 0;
        num_aresta_--;
    }
}

void Grafo::imprimir_grafo(){
    for (int i = 0; i < num_vertices_; i++)
    {
        cout << i << ": ";
        for (int j = 0; j < num_vertices_; j++)
        {
            if (matriz_adj_[i][j] == 1)
            {
                cout << matriz_adj_[i][j] << ' '; 
            }
            
        }
        cout << "\n";
    }
}

void Grafo::destruir_grafo(){
    // Não precisa, pois o Vector já tem uma forma que ele se auto libera 
}

bool Grafo::caminho(int v, int w, int marcado[], int nivel) {
    for (int i = 0; i < nivel; i++)
    {
        printf("   ");
    }
    
    printf("caminho %d %d\n", v,w);
    if (v == w) {
        return true;
    }
    marcado[v] = 1;
    for (int u = 0; u < num_vertices_; u++){
        if (matriz_adj_[v][u] != 0){
            if (marcado[u] == 0){
                if (caminho(u, w, marcado, nivel+1)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Grafo::acha_sus(int v, int pai[], int dist[], int marcado[]) {
    queue<int> fila;
    marcado[v] = 1;
    pai[v] = -1;
    dist[v] = 0;
    fila.push(v);

    while (!fila.empty()) {
        int w = fila.front();
        fila.pop();

        for (int u = 0; u < num_vertices_; u++) {
            if (matriz_adj_[w][u] != 0) {
                if (marcado[u] == 0) {
                    marcado[u] = 1;
                    pai[u] = w;
                    dist[u] = dist[w] + 1;
                    fila.push(u);
                }
            }
        }
    }
}
