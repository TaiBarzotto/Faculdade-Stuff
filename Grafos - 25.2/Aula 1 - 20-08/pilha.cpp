#include <bits/stdc++.h>

using namespace std;

int main(){
    stack<int> pilha; // 3.1 - Criando uma pilha cujos elementos são valores inteiros

    // 3.2 - Adicionando elementos na pilha
    // Inserindo valores fixos
    // pilha.push(1); 
    // pilha.push(2); 

    int input;
    for (int i = 0; i < 2; i++)
    {
        cin >> input;
        pilha.push(input);
    }
    
    // 3.3 - Remover imprimindo
    cout << "Imprimindo Pilha: " << "\n";
    while (!pilha.empty())
    {
        cout << pilha.top() << "\n";
        pilha.pop();   
    }
    
    return 0;
}