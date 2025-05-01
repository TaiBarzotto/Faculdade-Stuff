#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ordem.h"
#define MEMORIA_MAX 1000000

int carregar_dados(int M, char arquivos[M*2][20]) {
    int c, contador = 0;
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
            i++;
        } while (fgetc(entrada) != EOF && contador<M);

        // Ordenar os M elementos lidos
        quickSort(aux_arr, 0, M-1);

        // Escrever os M elementos ordenados nos arquivos
        for (j = 0; j < M; j++) {
            if (aux_arr[j] != -1){
                fprintf(writting_file, "%d;", aux_arr[j]);
                contador++;
            }
        }   
            fprintf(writting_file, "|", aux_arr[j]);

   
        fclose(writting_file);
    }
    fclose(entrada);
    return contador;
}

int ler_numero(FILE *arquivo, int *fim_bloco, int *valor, int *fim_arquivo) {
    int ch;
    int result = fscanf(arquivo, "%d;", valor);
    if ( result == EOF || *fim_bloco != 0) {
        if (result == EOF) {
            printf("EOF\n");
            *fim_arquivo = 1;
            *fim_bloco = 1;
        }
        return 0; // Fim do arquivo
    }
    
    *fim_bloco = 0;
    ch = fgetc(arquivo);
    if (ch == '|') {
        *fim_bloco = 1;
    } else{
        ungetc(ch, arquivo);
    }
    return 1;
}

void ler_primer_parte(int M, FILE **leitura, FILE **escrita, char arquivos[M*2][20]) {
    for (int i = 0; i < M; i++) {
        leitura[i] = fopen(arquivos[i], "r");
        if (leitura[i] == NULL) {
            printf("Erro ao abrir o arquivo %s.\n", arquivos[i]);
        }
    }
    
    for (int i = 0; i < M; i++) {
        escrita[i] = fopen(arquivos[i + M], "w");
        if (escrita[i] == NULL) {
            printf("Erro ao abrir o arquivo %s.\n", arquivos[i + M]);
        }
    } 
    
    int escrita_atual = 0;
    int valores[M];
    int ativos[M];      // indica se o arquivo ainda tem dados no bloco atual
    int fim_bloco[M];   // indica se o arquivo chegou ao fim do bloco
    int fim_arquivo[M]; // indica se o arquivo chegou ao fim do arquivo
    
    // Loop de intercalação por blocos
    int arquivos_completos = 0;

    // Inicializa os buffers com o primeiro valor de cada bloco
    
    
    while (arquivos_completos < M){
        for (int i = 0; i < M; i++) {
            fim_bloco[i] = 0;
            ativos[i]=1;
            ler_numero(leitura[i], &fim_bloco[i], &valores[i], &fim_arquivo[i]);
            if (fim_bloco[i] == 1) {
                ativos[i] = 0;
                arquivos_completos++;
            } 
        }
        printf("Arquivos completos: %d\n", arquivos_completos);
        // Intercala os blocos até todos terminarem
        while (1) {
            int minimo_valor = MEMORIA_MAX;
            int minimo_idx = -1;

            // Encontra o menor valor entre os arquivos ainda ativos
            for (int i = 0; i < M; i++) {
                if (ativos[i]==1 && valores[i] < minimo_valor) {
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
            printf("ANTES: Ativo: %d, FIM: %d, Valor: %d, Arquivo: %d\n", ativos[minimo_idx], fim_bloco[minimo_idx], valores[minimo_idx], leitura[minimo_idx]);
            printf("MINIMO: %d\n", minimo_valor);
    
            // Lê o próximo número apenas do arquivo que forneceu o menor
            if (fim_bloco[minimo_idx] == 0) {
                if (ler_numero(leitura[minimo_idx], &fim_bloco[minimo_idx], &valores[minimo_idx], &fim_arquivo[minimo_idx]) == 1) {
                    ativos[minimo_idx] = 1;
                } else {
                    ativos[minimo_idx] = 0;
                }
                printf("DEPOIS: Ativo: %d, FIM: %d, Valor: %d, Arquivo: %d\n", ativos[minimo_idx], fim_bloco[minimo_idx], valores[minimo_idx], leitura[minimo_idx]);
            } else {
                ativos[minimo_idx] = 0;
            }
        }
    
        // Marca fim de bloco na saída
        fprintf(escrita[escrita_atual], "|");
        escrita_atual = (escrita_atual + 1) % M;
    }

    for (int i = 0; i < M; i++) {
        fclose(leitura[i]);
        fclose(escrita[i]);
        
    }
}

void ler_seg_parte(int M, FILE **leitura, FILE **escrita, char arquivos[M*2][20]) {
    for (int i = 0; i < M; i++) {
        leitura[i] = fopen(arquivos[i+M], "r");
        if (leitura[i] == NULL) {
            printf("Erro ao abrir o arquivo %s.\n", arquivos[i]);
        }
    }
    
    for (int i = 0; i < M; i++) {
        escrita[i] = fopen(arquivos[i], "w");
        if (escrita[i] == NULL) {
            printf("Erro ao abrir o arquivo %s.\n", arquivos[i + M]);
        }
    } 
    
    int escrita_atual = 0;
    int valores[M];
    int ativos[M];      // indica se o arquivo ainda tem dados no bloco atual
    int fim_bloco[M];   // indica se o arquivo chegou ao fim do bloco
    int fim_arquivo[M]; // indica se o arquivo chegou ao fim do arquivo
    
    // Loop de intercalação por blocos
    int arquivos_completos = 0;

    // Inicializa os buffers com o primeiro valor de cada bloco
    
    
    while (arquivos_completos < M){
        for (int i = 0; i < M; i++) {
            fim_bloco[i] = 0;
            ativos[i]=1;
            ler_numero(leitura[i], &fim_bloco[i], &valores[i], &fim_arquivo[i]);
            if (fim_bloco[i] == 1) {
                ativos[i] = 0;
                arquivos_completos++;
            } 
        }
        printf("Arquivos completos: %d\n", arquivos_completos);
        // Intercala os blocos até todos terminarem
        while (1) {
            int minimo_valor = MEMORIA_MAX;
            int minimo_idx = -1;

            // Encontra o menor valor entre os arquivos ainda ativos
            for (int i = 0; i < M; i++) {
                if (ativos[i]==1 && valores[i] < minimo_valor) {
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
            printf("ANTES: Ativo: %d, FIM: %d, Valor: %d, Arquivo: %d\n", ativos[minimo_idx], fim_bloco[minimo_idx], valores[minimo_idx], leitura[minimo_idx]);
            printf("MINIMO: %d\n", minimo_valor);
    
            // Lê o próximo número apenas do arquivo que forneceu o menor
            if (fim_bloco[minimo_idx] == 0) {
                if (ler_numero(leitura[minimo_idx], &fim_bloco[minimo_idx], &valores[minimo_idx], &fim_arquivo[minimo_idx]) == 1) {
                    ativos[minimo_idx] = 1;
                } else {
                    ativos[minimo_idx] = 0;
                }
                printf("DEPOIS: Ativo: %d, FIM: %d, Valor: %d, Arquivo: %d\n", ativos[minimo_idx], fim_bloco[minimo_idx], valores[minimo_idx], leitura[minimo_idx]);
            } else {
                ativos[minimo_idx] = 0;
            }
        }
    
        // Marca fim de bloco na saída
        fprintf(escrita[escrita_atual], "|");
        escrita_atual = (escrita_atual + 1) % M;
    }
    for (int i = 0; i < M; i++) {
        fclose(leitura[i]);
        fclose(escrita[i]);
        
    }

}


int main() {

    int val_ini;
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
    }

    carregar_dados(M, arquivos);
    
    FILE **escrita = malloc(M * sizeof(FILE*));
    FILE **leitura = malloc(M * sizeof(FILE*));

    ler_primer_parte(M, leitura, escrita, arquivos);
    ler_seg_parte(M, leitura, escrita, arquivos);


    return 0;
}
