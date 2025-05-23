#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "auxiliar.h"

int main(){
    int M, tipo;
    FILE *entrada = fopen("dados.txt", "r");
    
    fscanf(entrada, "%d", &M);
    fscanf(entrada, "%d", &tipo);
    
    
    if(tipo == 0){
        Slista hash[M];
        hash_fechado(M, entrada, hash);
        print_hash_fechado(M, hash);
    }
    else{
        int hash[M];
        hash_aberto(M, hash, entrada);
        print_hash_aberto(M, hash);
    }

    return 0;    
}
