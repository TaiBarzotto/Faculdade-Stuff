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

bool Grafo::eh_passeio(vector<int> vertices){
    for(auto &i : vertices)
    {
        if (matriz_adj_[i][i+1]==1){
            return false;
        }
    }
    return true;
}

bool Grafo::eh_caminho(vector<int> vertices){
    vector<int> vertices_map(num_vertices_);
    for (int i = 0; i < num_vertices_; i++)
    {
        vertices_map[i]=0;
    }
    
    for(auto &i : vertices)
    {
        if (vertices_map[i]==1){
            return false;
        }

        vertices_map[i]=1;
    }
    return true;
}