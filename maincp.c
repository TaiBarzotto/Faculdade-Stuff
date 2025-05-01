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

        for (int j = 0; j < M; j++)
        {
            aux_arr[j]=-1;
        }
        
        
        if (percorrer >= M-1) {
            percorrer = 0;
        } else {
            percorrer++;
        }

        // Ler M elementos do arquivo de entrada
        int contador = 0;
        do {
            contador += fscanf(entrada, "%d", &aux_arr[i]);
            printf("valor lid:%d\n",aux_arr[i]);
            i++;
        } while (fgetc(entrada) != EOF && contador<M);

        // Ordenar os M elementos lidos
        quickSort(aux_arr, 0, M-1);

        // Escrever os M elementos ordenados nos arquivos
        for (j = 0; j < M; j++) {
            if (aux_arr[j] != -1){
                fprintf(writting_file, "%d;", aux_arr[j]);
            }
        }   
            fprintf(writting_file, "|", aux_arr[j]);

   
        fclose(writting_file);
    }
    fclose(entrada);
}


int ler_numero(FILE *arquivo, int *fim_bloco, int *valor, int *fim_file) {
    int ch;
    fscanf(arquivo, "%d;", valor);
    if (*valor == EOF) {
        *fim_file = 1;
        return 1; // Fim do arquivo
    }
    if (*fim_bloco != 0) {
        printf("Valor_scanf: %d\n", *valor);
        return 1; // Fim do arquivo
    }

    ch = fgetc(arquivo);
    if (ch == '|') {
        *fim_bloco = 1;
    } else{
        ungetc(ch, arquivo);
    }
    printf("Valor: %d\n", *valor);
    return 0;
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
    int fim_file[M];    // indica se o arquivo chegou ao fim do arquivo
    
    // Loop de intercalação por blocos
    int arquivos_concluidos = 0;

    // Inicializa os buffers com o primeiro valor de cada bloco
    
    
    while (arquivos_concluidos < M) {
        
        for (int i = 0; i < M; i++) {
            fim_bloco[i] = 0;
            ativos[i]=1;
            ler_numero(leitura[i], &fim_bloco[i], &valores[i], &fim_file[i]);
            if (fim_file[i] == 1) {
                ativos[i] = 0;
                arquivos_concluidos++;
            }
            
        }
        printf("A\n");
        // Intercala os blocos até todos terminarem
        while (1) {
            int minimo_valor = MEMORIA_MAX;
            int minimo_idx = -1;

            // Encontra o menor valor entre os arquivos ainda ativos
            for (int i = 0; i < M; i++) {
                if (ativos[i]==1 && valores[i] < minimo_valor && valores[i]) {
                    minimo_valor = valores[i];
                    minimo_idx = i;
                }
            }
    
            // Todos os blocos chegaram ao fim?
            if (minimo_idx == -1) {
                break;
            }
    
            // Escreve no arquivo de saída
            fprintf(escrita[escrita_atual], "%d;", minimo_valor);
            printf("Ativo: %d, FIM: %d, Valor: %d, Arquivo: %d\n", ativos[minimo_idx], fim_bloco[minimo_idx], valores[minimo_idx], leitura[minimo_idx]);
            printf("MINIMO: %d\n", minimo_valor);
    
            // Lê o próximo número apenas do arquivo que forneceu o menor
            if (fim_bloco[minimo_idx] == 0) {
                if (ler_numero(leitura[minimo_idx], &fim_bloco[minimo_idx], &valores[minimo_idx], &fim_file[minimo_idx]) == 0) {
                    ativos[minimo_idx] = 1;
                } else {
                    ativos[minimo_idx] = 0;
                }
            } else {
                ativos[minimo_idx] = 0;
            }
            printf("Ativo: %d, FIM: %d, Valor: %d, Arquivo: %d\n", ativos[minimo_idx], fim_bloco[minimo_idx], valores[minimo_idx], leitura[minimo_idx]);
        }
    
        // Marca fim de bloco na saída
        fprintf(escrita[escrita_atual], "|");
        escrita_atual = (escrita_atual + 1) % M;
    }
    


    return 0;
}

