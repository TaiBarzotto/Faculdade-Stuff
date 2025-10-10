/*
    Trabalho 1 - Potenciais comparsas
    GEN505 -  Grafos - 2025/02

    Nomes: Tainara, Wemely
    Matriculas: 20240017799, 20240008468
*/

#include "grafo.h"
#include "aresta.h"
#include <iostream>
using namespace std;

int main() {
    int p, l, x,y;
    char t;
    cin >> p >> l;
    Grafo g(p); 

    for (int i = 0; i < l; i++)
    {
        cin >> x >> y >> t;
        if (t == 'W')
        {
            g.insere_aresta({x, y});
        }
        
    }

    int marcado[p];
    int sus[p];
    int dist[p];
    
    int o, input;
    
    cin>>o;
    for (int i = 0; i < o; i++)
    {
        for (int i = 0; i < p; i++)
        {
            marcado[i]=0;
            sus[i]=0;
            dist[i]=0;
        }
        cin>>input;
        g.acha_sus(input,sus, dist, marcado);
    
        cout << input << ": "; 
        for (int i = 0; i < p; i++)
        {
            if (dist[i]<=3 && i !=input && marcado[i]==1)
            {
                cout<<i<<" ";
            }
            
        }
        cout<<"\n";
    }
    
    

    return 0;
}
