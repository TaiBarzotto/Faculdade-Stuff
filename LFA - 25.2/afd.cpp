#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

int main(){
    FILE *tokens = fopen("tokens.txt", "r");
    if (tokens == NULL)
    {
        printf("Erro ao abrir arquivo de tokens");
        return 0;
    }

    set<char> simbolos;
    int count_simbolos =0;
    char c;
    while (!feof(tokens))
    {
        c = fgetc(tokens);
        if (c!=' ' && c!=EOF && c!= '\n')
        {
            simbolos.insert(c);
            count_simbolos++;
        }
        
    }
    
    unordered_map<char,int> dict_simbolos;
    int i = 0;
    for (char s : simbolos) {
        dict_simbolos[s] = i;
        i++;
    }
    
    vector<vector<string>> afnd(count_simbolos, vector<string>(i, ""));
    rewind(tokens);
    int prox_estado_livre = 0;
    int eh_simbolo_inicial = 1;
    int estado_inicial = 0;
    int estado_atual = 0;
    while ((c = fgetc(tokens)) != EOF)
    {
        if (c != ' ')
        {
            if (c!='\n')
            { 
                if (eh_simbolo_inicial)
                {
                    estado_atual = estado_inicial;
                }else
                {
                    estado_atual = prox_estado_livre;
                }
                
                
                auto it = dict_simbolos.find(c);
                if (it != dict_simbolos.end()) {
                    int idx = it->second;
                    afnd[estado_atual][idx] += (afnd[estado_atual][idx].empty() ? to_string(++prox_estado_livre) : ", " + to_string(++prox_estado_livre));
                }
                
                eh_simbolo_inicial=0;
            }else
            {
                eh_simbolo_inicial = 1;
            }
            
        }
    }

    cout<<"\t";
    for (char s : simbolos) {
        cout<<s<<"\t";
    }
    cout<<endl;

    for (int r = 0; r < afnd.size(); ++r) {
        cout << r << "\t";
        for (int col = 0; col < afnd[r].size(); col++) {
            if (afnd[r][col] == "")
                cout << "-\t";
            else
                cout << afnd[r][col] << "\t";
        }
        cout << '\n';
    }


    
    

    fclose(tokens);
    return 0;
}