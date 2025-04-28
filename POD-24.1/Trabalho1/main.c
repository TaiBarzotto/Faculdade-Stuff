#include <stdio.h>
#include <stdlib.h>
#include "ordem.h"
#define MEMORIA_MAX 1000000

int main() {
    
    int M;
    char c;
    printf("Digite a quantidade de elementos a serem carregados por vez em memória (M): ");
    scanf("%d", &M);
    
    int aux_arr[M];
    if (M <= 0 || M > MEMORIA_MAX) {
        printf("Valor de M inválido. Deve ser entre 1 e %d.\n", MEMORIA_MAX);
        return 0;
    }
    FILE *entrada = fopen("dados.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 0;
    }

    while(!feof(entrada)) {
        int i = 0;
        while (i < M) {
            c = fgetc(entrada);
            if (c == ';'){
                continue;
            }
            aux_arr[i] = (int) c;
            i++;
        }
        quickSort(aux_arr, 0, M-1);
        // até aqui to lendo e ordenando, falta fazer a parte dos arquivos
        printf("Lidos %d elementos:\n", M);
        for (int i = 0; i <= M; i++) {
            printf("%c ", aux_arr[i]);
        }
        printf("\n");
    }

    //ordenacao_externa(M);
    return 0;
}