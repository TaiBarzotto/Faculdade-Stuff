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
    char c;
    vector<char> estados;
    while (!feof(tokens))
    {
        c = fgetc(tokens);
        if (c!=' ' && c!=EOF && c!= '\n')
        {
            
            simbolos.insert(c);
        }
        
    }
    pair<char, int> dict_simbolos;

    int i = 0;
    for (char s : simbolos) {
        cout << s <<"-"<<i<< " ";
        dict_simbolos.first = s;
        dict_simbolos.second = i;
        i++;
    }

    fclose(tokens);
    return 0;
}