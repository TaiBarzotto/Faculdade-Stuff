#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ordem.h"
#define MEMORIA_MAX 1000000

void carregar_dados(int M, char arquivos[M*2][20]) {
    int c;
    int aux_arr[M];
    int file_flag = 0, percorrer = 0;
    
    FILE *entrada = fopen("dados.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }

    while(!feof(entrada)) {
        int i = 0, j =0; 
        FILE *writting_file = fopen(arquivos[percorrer], "a+");
        if (writting_file == NULL){
            printf("Erro ao abrir o arquivo.\n");
        }
        
        if (percorrer >= M-1) {
            percorrer = 0;
        } else {
            percorrer++;
        }

        // Ler M elementos do arquivo de entrada
        for (i = 0; i < M; i++) {
            fscanf(entrada, "%d;", &aux_arr[i]);
        }

        // Ordenar os M elementos lidos
        quickSort(aux_arr, 0, M-1);

        // Escrever os M elementos ordenados nos arquivos
        for (j = 0; j < M-1; j++) {
                fprintf(writting_file, "%d;", aux_arr[j]);
        
        }
            fprintf(writting_file, "%d ", aux_arr[j]);

   
        fclose(writting_file);
    }
    fclose(entrada);
}


int ler_numero(FILE *arquivo, int *fim_bloco, int *valor) {
    int ch;
    *fim_bloco = 0;

    if (fscanf(arquivo, "%d", valor) != 1) {
        return 0; // Fim do arquivo
    }

    ch = fgetc(arquivo);
    if (ch == ' ') {
        *fim_bloco = 1;
    } else if (ch != ';' && ch != EOF) {
        ungetc(ch, arquivo);  // devolve o caractere não previsto
    }

    printf("Valor: %d\n", *valor);
    return 1;
}




int main() {
    
    int M;
    char c;
    printf("Digite a quantidade de elementos a serem carregados por vez em memória (M): ");
    scanf("%d", &M);
    
    char arquivos[M*2][20];
    if (M <= 0 || M > MEMORIA_MAX) {
        printf("Valor de M inválido. Deve ser entre 1 e %d.\n", MEMORIA_MAX);
        return 0;
    }
   
    // Abrir os M*2 arquivos
    for (int i = 0; i < M*2; i++) {
        char nome_arquivo[20];
        sprintf(nome_arquivo, "F%d.txt", i+1);
        strcpy(arquivos[i], nome_arquivo);
        printf("Arquivo %d: %s\n", i+1, arquivos[i]);
    }

    carregar_dados(M, arquivos);
    
    FILE **escrita = malloc(M * sizeof(FILE*));
    FILE **leitura = malloc(M * sizeof(FILE*));

    for (int i = 0; i < M; i++) {
        leitura[i] = fopen(arquivos[i], "r");
        if (leitura[i] == NULL) {
            printf("Erro ao abrir o arquivo %s.\n", arquivos[i]);
            return 1;
        }
    }
    
    for (int i = 0; i < M; i++) {
        escrita[i] = fopen(arquivos[i + M], "w");
        if (escrita[i] == NULL) {
            printf("Erro ao abrir o arquivo %s.\n", arquivos[i + M]);
            return 1;
        }
    } 
    
    int escrita_atual = 0;
    int valores[M];
    int ativos[M];      // indica se o arquivo ainda tem dados no bloco atual
    int fim_bloco[M];   // indica se o arquivo chegou ao fim do bloco
    
    // Loop de intercalação por blocos
    int blocos_ativos = 0;

    // Inicializa os buffers com o primeiro valor de cada bloco
    for (int i = 0; i < M; i++) {
        fim_bloco[i] = 0;
        if (ler_numero(leitura[i], &fim_bloco[i], &valores[i])) {
            ativos[i] = 1;
            blocos_ativos++;
        } else {
            ativos[i] = 0;
            fim_bloco[i] = 1;
        }
    }

    while (1) {
        int blocos_ativos = 0;
        
        for (int i = 0; i < M; i++) {
            fim_bloco[i] = 0;
            if (ativos[i]) {
                blocos_ativos++;
            } 
        }

        if (blocos_ativos == 0) break;
    
        // Intercala os blocos até todos terminarem
        while (1) {
            int minimo_valor = MEMORIA_MAX;
            int minimo_idx = -1;
    
            // Encontra o menor valor entre os arquivos ainda ativos
            for (int i = 0; i < M; i++) {
                if (ativos[i] && !fim_bloco[i] && valores[i] < minimo_valor) {
                    minimo_valor = valores[i];
                    minimo_idx = i;
                }
            }
    
            // Todos os blocos chegaram ao fim?
            if (minimo_idx == -1) break;
    
            // Escreve no arquivo de saída
            fprintf(escrita[escrita_atual], "%d;", minimo_valor);
            printf("MINIMO: %d\n", minimo_valor);
    
            // Lê o próximo número apenas do arquivo que forneceu o menor
            if (ler_numero(leitura[minimo_idx], &fim_bloco[minimo_idx], &valores[minimo_idx])) {
                ativos[minimo_idx] = 1;
            } else {
                ativos[minimo_idx] = 0;
            }

            printf("Ativo: %d, Valor: %d, Arquivo: %d\n", ativos[minimo_idx], valores[minimo_idx], leitura[minimo_idx]);
        }
    
        // Marca fim de bloco na saída
        fprintf(escrita[escrita_atual], " ");
        escrita_atual = (escrita_atual + 1) % M;
    }
    


    return 0;
}

