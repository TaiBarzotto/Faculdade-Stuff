#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ordem.h"
#define MEMORIA_MAX 1000000

int carregar_dados(int M, char arquivos[M][20]) {
    int contador = 0;
    int aux_arr[M];
    int percorrer = 0;
    
    FILE *entrada = fopen("dados.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }

    FILE **escrita = malloc(M * sizeof(FILE*));
    for (int i = 0; i < M; i++) {
        escrita[i] = fopen(arquivos[i], "w");
        if (escrita[i] == NULL) {
            printf("Erro ao abrir o arquivo %s.\n", arquivos[i]);
            return 1;
        }
    } 
    while(!feof(entrada)) {
        int i = 0, j =0; 
        FILE *writting_file = escrita[percorrer];
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
            fprintf(writting_file,"|");

    }
    for (int i = 0; i < M; i++)
    {
        fclose(escrita[i]);
    }
    
    fclose(entrada);
    return contador;
}

int ler_numero(FILE *arquivo, int *fim_bloco, int *valor, int *fim_arquivo) {
    int ch;
    int result = fscanf(arquivo, "%d;", valor);
    if (result == EOF || *fim_bloco != 0) {
        if (result == EOF) {
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

void intercala_arquivos(int M, FILE **leitura, FILE **escrita) {
    int escrita_atual = 0;
    int valores[M];
    int ativos[M];      // indica se o arquivo ainda tem dados no bloco atual
    int fim_bloco[M];   // indica se o arquivo chegou ao fim do bloco
    int fim_arquivo[M]; // indica se o arquivo chegou ao fim do arquivo
    int arquivos_completos = 0;

    // Inicializa os buffers com o primeiro valor de cada bloco    
    for (int i = 0; i < M; i++) {
        fim_bloco[i] = 0;
        fim_arquivo[i] = 0;
        ativos[i]=1;
        ler_numero(leitura[i], &fim_bloco[i], &valores[i], &fim_arquivo[i]);
    }
    while (arquivos_completos < M){
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
    
            // Lê o próximo número apenas do arquivo que forneceu o menor
            if (fim_bloco[minimo_idx] == 0 ) {
                if (ler_numero(leitura[minimo_idx], &fim_bloco[minimo_idx], &valores[minimo_idx], &fim_arquivo[minimo_idx]) == 1) {
                    ativos[minimo_idx] = 1;
                } else {
                    fim_bloco[minimo_idx] = 1;
                    ativos[minimo_idx] = 0;
                }
            } else {
                fim_bloco[minimo_idx] = 1;
                ativos[minimo_idx] = 0;
            }
        }
    
        // Marca fim de bloco na saída
        fprintf(escrita[escrita_atual], "|");
        escrita_atual = (escrita_atual + 1) % M;
        for (int i = 0; i < M; i++) {
            fim_bloco[i] = 0;
            fim_arquivo[i] = 0;
            ativos[i]=1;
            ler_numero(leitura[i], &fim_bloco[i], &valores[i], &fim_arquivo[i]);
            if (fim_arquivo[i] == 1) {
                ativos[i] = 0;
                fim_bloco[i] = 1;
                arquivos_completos++;
            } 
        }
    }

    for (int i = 0; i < M; i++) {
        fclose(leitura[i]);
        fclose(escrita[i]);
        
    }
}


int main() {
    int flag_vez = 0; // 0- estou lendo a 1° metade e escrevendo na 2°
    int M;
    int contador_eof = 0;
    printf("Digite a quantidade de elementos a serem carregados por vez em memória (M): ");
    scanf("%d", &M);
    
    char arquivos1[M][20];
    char arquivos2[M][20];
    if (M <= 0 || M > MEMORIA_MAX) {
        printf("Valor de M inválido. Deve ser entre 1 e %d.\n", MEMORIA_MAX);
        return 0;
    }
   
    // Abrir os M*2 arquivos
    for (int i = 0; i < M; i++) {
        char nome_arquivo[20];
        sprintf(nome_arquivo, "F%d.txt", i+1);
        strcpy(arquivos1[i], nome_arquivo);
        printf("%s\n", nome_arquivo);
    }
    for (int i = 0; i < M; i++) {
        char nome_arquivo[20];
        sprintf(nome_arquivo, "F%d.txt", i+M+1);
        strcpy(arquivos2[i], nome_arquivo);
        printf("%s\n", nome_arquivo);
    }

    carregar_dados(M, arquivos1);
    
    FILE **escrita = malloc(M * sizeof(FILE*));
    FILE **leitura = malloc(M * sizeof(FILE*));

    while (contador_eof < M-1){
        if(flag_vez == 0){
            for (int i = 0; i < M; i++) {
                leitura[i] = fopen(arquivos1[i], "r");
                if (leitura[i] == NULL) {
                    printf("Erro ao abrir o arquivo %sR1.\n", arquivos1[i]);
                    return 1;
                }
            }
            
            for (int i = 0; i < M; i++) {
                escrita[i] = fopen(arquivos2[i], "w");
                if (escrita[i] == NULL) {
                    printf("Erro ao abrir o arquivo %sw1.\n", arquivos2[i]);
                    return 1;
                }
            } 
        }else
        {
            for (int i = 0; i < M; i++) {
                leitura[i] = fopen(arquivos2[i], "r");
                if (leitura[i] == NULL) {
                    printf("Erro ao abrir o arquivo %sr2.\n", arquivos2[i]);
                    return 1;
                }
            }
            
            for (int i = 0; i < M; i++) {
                escrita[i] = fopen(arquivos1[i], "w");
                if (escrita[i] == NULL) {
                    printf("Erro ao abrir o arquivo %sw2.\n", arquivos2[i]);
                    return 1;
                }
            } 
        }
        
        intercala_arquivos(M, leitura, escrita);

        if(flag_vez == 0){
            for (int i = 0; i < M; i++) {
                escrita[i] = fopen(arquivos2[i], "r"); //Abrir os arquivos de escrita para ver oq escreveu em cada
                if (escrita[i] == NULL) {
                    printf("Erro ao abrir o arquivo %sr3.\n", arquivos2[i]);
                    return 1;
                }
                char c;
                c = fgetc(escrita[i]);
                if (c == EOF || c == '|') {
                    contador_eof++;
                } 
                fclose(escrita[i]);
            }
            if (contador_eof == M-1) {
                printf("Foi ordenado.\nArquivo resultante: %s\n", arquivos2[0]);
            } else {
                contador_eof = 0;
            }
        }else{
            for (int i = 0; i < M; i++) {
                escrita[i] = fopen(arquivos1[i], "r"); //Abrir os arquivos de escrita para ver oq escreveu em cada
                if (escrita[i] == NULL) {
                    printf("Erro ao abrir o arquivo %sr4.\n", arquivos1[i]);
                    return 1;
                }
                char c;
                c = fgetc(escrita[i]);
                if (c == EOF || c == '|') {
                    contador_eof++;
                } 
                fclose(escrita[i]);
            }

            if (contador_eof == M-1) {                
                printf("Foi ordenado.\nArquivo resultante: %s\n", arquivos1[0]);
            } else {
                contador_eof = 0;
            }
        }
        flag_vez = (flag_vez + 1) % 2;
        
    }
    
    


    return 0;
}
