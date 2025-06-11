#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ordem.h"
#define MEMORIA_MAX 1000000

int carregar_dados(int M, char arquivos[M][20]) {
    int c, contador = 0;
    int aux_arr[M];
    int file_flag = 0, percorrer = 0;
    
    FILE *entrada = fopen("dados.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }

    // Abre os arquivos de escrita e coloca no vetor de escrita
    FILE **escrita = malloc(M * sizeof(FILE*));
    for (int i = 0; i < M; i++) {
        escrita[i] = fopen(arquivos[i], "w");
        if (escrita[i] == NULL) {
            printf("Erro ao abrir o arquivo %s.\n", arquivos[i + M]);
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
        fprintf(writting_file, " ", aux_arr[j]);

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
    int result = fscanf(arquivo, "%d;", valor); // Pegar o número até o ';'
    if (result == EOF || *fim_bloco != 0) { // verifica se chegou ao fim do arquivo ou se o bloco já acabou
        if (result == EOF) { // Fim de arquivo
            *fim_arquivo = 1;
            *fim_bloco = 1;
        }
        return 0; 
    }
    
    *fim_bloco = 0;
    ch = fgetc(arquivo);
    if (ch == ' ') { // Separador de fim de bloco
        *fim_bloco = 1;
    } else{
        ungetc(ch, arquivo); // Devolve o caractere lido para o arquivo (volta o cursor para o caractere lido)
    }
    return 1;
}

void intercala_arquivos(int M, FILE **leitura, FILE **escrita) {
    int escrita_atual = 0;
    int valores[M]; // Vetor para armazenar um valor de cada arquivo os quais estão sendo lidos e ordenados
    int ativos[M]; // indica se o arquivo ainda tem dados no bloco atual que ira passar pela ordenação
    int fim_bloco[M]; // indica se o arquivo chegou ao fim do bloco
    int fim_arquivo[M]; // indica se o arquivo chegou ao fim do arquivo
    int arquivos_completos = 0;

    // Inicializa os valores com o primeiro valor de cada bloco, e as respectivas flags    
    for (int i = 0; i < M; i++) {
        fim_bloco[i] = 0;
        fim_arquivo[i] = 0;
        ativos[i]=1;
        ler_numero(leitura[i], &fim_bloco[i], &valores[i], &fim_arquivo[i]);
    }

    // Loop para intercalar os aquivos até que todos os arquivos de leitura estejam em EOF
    while (arquivos_completos < M){

        // Loop que intercala os arquivos de leitura até o fim do respectivo bloco
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
    
            // Lê o próximo número apenas do arquivo que forneceu o menor valor
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
        fprintf(escrita[escrita_atual], " ");
        escrita_atual = (escrita_atual + 1) % M;
        
        // Le os primeiros valores do proximo bloco de leitura e verifica se os arquivos chegaram ao fim
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
    int flag_vez = 0; // 0 == estou lendo a 1° metade e escrevendo na 2° 1 == estou lendo a 2° metade e escrevendo na 1°
    int M;
    int contador_eof = 0; // contador de EOF para saber se só tem um arquivo com dados (Fim da ordenação)
    char c;
    printf("Digite a quantidade de elementos a serem carregados por vez em memória (M): ");
    scanf("%d", &M);
    
    // Armazenar os nomes dos arquivos em dois blocos para poder abrir com leitura ou escrita quando necessário
    // M*2 arquivos, M para leitura e M para escrita
    char bloco_arquivos1[M][20];
    char bloco_arquivos2[M][20];
    if (M <= 0 || M > MEMORIA_MAX) {
        printf("Valor de M inválido. Deve ser entre 1 e %d.\n", MEMORIA_MAX);
        return 0;
    }
   
    // Abrir os M*2 arquivos
    for (int i = 0; i < M; i++) {
        char nome_arquivo1[20];
        char nome_arquivo2[20];
        sprintf(nome_arquivo1, "F%d.txt", i+1);
        sprintf(nome_arquivo2, "F%d.txt", i+1+M);
        strcpy(bloco_arquivos1[i], nome_arquivo1);
        strcpy(bloco_arquivos2[i], nome_arquivo2);
    }

    carregar_dados(M, bloco_arquivos1); // Carregar os dados do arquivo dados.txt para os arquivos do bloco_arquivos1 (primeira metade)
    FILE *check_ordenado = fopen(bloco_arquivos1[1], "r"); // Verifica se tem outros blocos para serem ordenados
    if (feof(check_ordenado) == 0) { // Se o arquivo estiver vazio, não tem nada para ordenar
        printf("Foi ordenado.\nArquivo resultante: %s\n", bloco_arquivos1[0]);
        return 0;
    }
    // Ponteiros para armazenar as referências dos arquivos abertos
    FILE **escrita = malloc(M * sizeof(FILE*));
    FILE **leitura = malloc(M * sizeof(FILE*));

    while (contador_eof < M-1){
        if(flag_vez == 0){
            for (int i = 0; i < M; i++) {
                leitura[i] = fopen(bloco_arquivos1[i], "r");
                if (leitura[i] == NULL) {
                    printf("Erro ao abrir o arquivo %s.\n", bloco_arquivos1[i]);
                    return 1;
                }
                escrita[i] = fopen(bloco_arquivos2[i], "w");
                if (escrita[i] == NULL) {
                    printf("Erro ao abrir o arquivo %s.\n", bloco_arquivos2[i]);
                    return 1;
                }
            } 
        }else
        {
            for (int i = 0; i < M; i++) {
                leitura[i] = fopen(bloco_arquivos2[i], "r");
                if (leitura[i] == NULL) {
                    printf("Erro ao abrir o arquivo %s.\n", bloco_arquivos2[i]);
                    return 1;
                }
                escrita[i] = fopen(bloco_arquivos1[i], "w");
                if (escrita[i] == NULL) {
                    printf("Erro ao abrir o arquivo %s.\n", bloco_arquivos1[i]);
                    return 1;
                }
            } 
        }
        
        intercala_arquivos(M, leitura, escrita); // Passar os dados ordenando para os respectivos arquivos de escrita (intercalação)

        if(flag_vez == 0){
            for (int i = 0; i < M; i++) {
                escrita[i] = fopen(bloco_arquivos2[i], "r"); //Abrir os arquivos de escrita para ver oq escreveu em cada
                if (escrita[i] == NULL) {
                    printf("Erro ao abrir o arquivo %s.\n", bloco_arquivos2[i]);
                    return 1;
                }
                c = fgetc(escrita[i]);
                if (c == EOF || c == ' ') { // Se o arquivo estiver vazio ou se for só uma marca de fim do bloco
                    contador_eof++;
                } 
                fclose(escrita[i]);
            }
            if (contador_eof == M-1) {
                printf("Foi ordenado.\nArquivo resultante: %s\n", bloco_arquivos2[0]);
            } else {
                contador_eof = 0;
            }
        }else{
            for (int i = 0; i < M; i++) {
                escrita[i] = fopen(bloco_arquivos1[i], "r"); //Abrir os arquivos de escrita para ver oq escreveu em cada
                if (escrita[i] == NULL) {
                    printf("Erro ao abrir o arquivo %s.\n", bloco_arquivos1[i]);
                    return 1;
                }
                c = fgetc(escrita[i]);
                if (c == EOF || c == ' ') { // Se o arquivo estiver vazio ou se for só uma marca de fim do bloco
                    contador_eof++;
                } 
                fclose(escrita[i]);
            }

            if (contador_eof == M-1) {                
                printf("Foi ordenado.\nArquivo resultante: %s\n", bloco_arquivos1[0]);
            } else {
                contador_eof = 0;
            }
        }
        flag_vez = (flag_vez + 1) % 2;
    }
    
    


    return 0;
}