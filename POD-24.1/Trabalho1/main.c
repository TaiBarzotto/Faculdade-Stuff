#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ordem.h"
#define MEMORIA_MAX 1000000

int main() {
    
    int M;
    char c;
    printf("Digite a quantidade de elementos a serem carregados por vez em memória (M): ");
    scanf("%d", &M);
    
    int aux_arr[M];
    char arquivos[M*2][20];
    if (M <= 0 || M > MEMORIA_MAX) {
        printf("Valor de M inválido. Deve ser entre 1 e %d.\n", MEMORIA_MAX);
        return 0;
    }
    FILE *entrada = fopen("dados.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 0;
    }
    // Abrir os M*2 arquivos
    for (int i = 0; i < M*2; i++) {
        char nome_arquivo[20];
        sprintf(nome_arquivo, "F%d.txt", i+1);
        strcpy(arquivos[i], nome_arquivo);
        printf("Arquivo %d: %s\n", i+1, arquivos[i]);
    }

    int file_flag = 0, percorrer = 0;

    while(!feof(entrada)) {
        int i = 0, j =0;
        FILE *writting_file = fopen(arquivos[percorrer], "a+");
        
        if (percorrer >= M-1) {
            percorrer = 0;
        } else {
            percorrer++;
        }

        // Ler M elementos do arquivo de entrada
        while (i < M) {
            c = fgetc(entrada);
            if (c == ';'){
                continue;
            }
            aux_arr[i] = (int) c;
            i++;
        }

        // Ordenar os M elementos lidos
        quickSort(aux_arr, 0, M-1);

        // Escrever os M elementos ordenados nos arquivos
        for (j = 0; j < M-1; j++) {
            if (isdigit(aux_arr[j]) != 0) {
                fprintf(writting_file, "%c;", aux_arr[j]);
            }
        }if (isdigit(aux_arr[j]) != 0) {
            fprintf(writting_file, "%c ", aux_arr[j]);
        }

        printf("Lidos %d elementos:\n", M);
        for (i = 0; i < M; i++) {
            printf("%c ", aux_arr[i]);
        }
        printf("\n");
        fclose(writting_file);
    }
    fclose(entrada);
    
    int leitura = 0, escrita = 0;
    if (file_flag == 0) {
        leitura = 0;
        escrita = M;
        file_flag = 1;
    } else {
        leitura = M;
        escrita = 0;
        file_flag = 0;
    }
    
    FILE *todos_arquivos_leitura[M*2];
    FILE *todos_arquivos_escrita[M*2];

    for (int i = 0; i < M*2; i++) {
        todos_arquivos_leitura[i] = NULL;
        todos_arquivos_escrita[i] = NULL;
    }


    for (int i = 0; i < M*2; i++) {
        *todos_arquivos_leitura[i] = fopen(arquivos[i], "r+");
        if (todos_arquivos_leitura[i] == NULL) {
            printf("Erro ao abrir o arquivo %s.\n", arquivos[i]);
            return 0;
        }
    }

    for (int i = 0; i < M*2; i++) {
        *todos_arquivos_escrita[i] = fopen(arquivos[i], "w+");
        if (todos_arquivos_escrita[i] == NULL) {
            printf("Erro ao abrir o arquivo %s.\n", arquivos[i]);
            return 0;
        }
    }

    int fim = 1;
    while(fim != 0) {
        int temp_values_int[M], flags[M], flags_bloco[M], minimum = 0;
        char c;

        for (int i = 0; i < M; i++) {
            flags[i] = 0;
            flags_bloco[i] = 0;
        }
        FILE *writting_file = *todos_arquivos_escrita[escrita];
        printf("AA");
        int fim_bloco = 1;
        while (fim_bloco != 0) {
            int i = leitura;
            for (i = leitura; i < escrita; i++) {
                FILE *reading_file = *todos_arquivos_leitura[i];
                if (reading_file == NULL) {
                    printf("Erro ao abrir o arquivo %s.\n", arquivos[i]);
                    return 0;
                }

                c = fgetc(reading_file);
                temp_values_int[i] = (int) c;
                printf("Temp INT %d: %c\n", i, temp_values_int[i]);


                if (temp_values_int[i] < temp_values_int[minimum]){
                    minimum = i;
                } else minimum;

                printf("Min: %d\n", temp_values_int[minimum]);

                if (c == EOF) {
                    flags[i] = 1; 
                }else if (c != ' ') {
                    flags_bloco[i] = 1;
                }
            }
            FILE *subs_min = *todos_arquivos_leitura[minimum];
            if (subs_min == NULL) {
                printf("Erro ao abrir o arquivo %s.\n", arquivos[minimum]);
                return 0;
            }
            c = fgetc(subs_min);
            printf("Substituindo o valor %c do arquivo %s\n", c, arquivos[minimum]);
            if (c == EOF) {
                flags[i] = 1;
            }else if (c != ' ') {
                flags_bloco[i] = 1;
            }
            temp_values_int[minimum] = (int) c;
            printf ("Debug: min:%d, value:%d, c:%d\n", minimum, temp_values_int[minimum], c);
            fim_bloco = 0;
            if (minimum - 1!=0 && (temp_values_int[minimum] < temp_values_int[minimum-1])){
                minimum = i;
            } else continue;
            fprintf(writting_file, "%c;", temp_values_int[minimum]);

        }
        

        for (int i = 0; i < M; i++) {
            if (flags[i] == 1) {
                fim = 0;
                continue;
            }else{
                fim = 1;
                break;
            }
        }
        fim = 0;
    }


    return 0;
}

