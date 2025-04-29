#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUM_LENGTH 12
#define MAX_TEMP_FILES 100

// Função de comparação para qsort
int comparar(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Função para extrair números do arquivo dados.txt
int carregar_numeros(FILE* arquivo, int* buffer, int M) {
    char ch, num_str[MAX_NUM_LENGTH];
    int i = 0, k = 0;

    while ((ch = fgetc(arquivo)) != EOF && i < M) {
        if (isdigit(ch)) {
            num_str[k++] = ch;
        } else if (ch == ';' || ch == ' ' || ch == '\n') {
            if (k > 0) {
                num_str[k] = '\0';
                buffer[i++] = atoi(num_str);
                k = 0;
            }
        }
    }

    // Último número, caso o arquivo não termine com ; ou espaço
    if (k > 0 && i < M) {
        num_str[k] = '\0';
        buffer[i++] = atoi(num_str);
    }

    return i; // quantidade de números lidos
}

// Função para salvar um bloco ordenado em arquivo temporário
void salvar_bloco_ordenado(int* buffer, int tam, int indice) {
    char nome_arquivo[20];
    sprintf(nome_arquivo, "temp%d.txt", indice);

    FILE* f = fopen(nome_arquivo, "w");
    if (!f) {
        perror("Erro ao criar arquivo temporário");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < tam; i++) {
        fprintf(f, "%d", buffer[i]);
        if (i != tam - 1)
            fprintf(f, ";");
    }
    fclose(f);
}

// Lê próximo número de um arquivo já aberto (com ponteiro de arquivo)
int ler_proximo(FILE* f, int* valor) {
    char ch;
    char num_str[MAX_NUM_LENGTH];
    int k = 0;

    while ((ch = fgetc(f)) != EOF) {
        if (isdigit(ch)) {
            num_str[k++] = ch;
        } else if (ch == ';' || ch == '\n') {
            if (k > 0) {
                num_str[k] = '\0';
                *valor = atoi(num_str);
                return 1;
            }
        }
    }

    if (k > 0) {
        num_str[k] = '\0';
        *valor = atoi(num_str);
        return 1;
    }

    return 0;
}

// Função para mesclar arquivos temporários em um final
void mesclar_blocos(int total_blocos, const char* arquivo_saida) {
    FILE* fontes[MAX_TEMP_FILES];
    int valores[MAX_TEMP_FILES];
    int ativos[MAX_TEMP_FILES] = {0};

    // Abre arquivos e carrega primeiro número
    for (int i = 0; i < total_blocos; i++) {
        char nome_arquivo[20];
        sprintf(nome_arquivo, "temp%d.txt", i);
        fontes[i] = fopen(nome_arquivo, "r");
        if (!fontes[i]) {
            perror("Erro ao abrir arquivo temporário");
            exit(EXIT_FAILURE);
        }
        if (ler_proximo(fontes[i], &valores[i])) {
            ativos[i] = 1;
        }
    }

    FILE* saida = fopen(arquivo_saida, "w");
    if (!saida) {
        perror("Erro ao criar arquivo de saída");
        exit(EXIT_FAILURE);
    }

    int primeiro = 1;
    while (1) {
        int menor = -1;
        for (int i = 0; i < total_blocos; i++) {
            if (ativos[i]) {
                if (menor == -1 || valores[i] < valores[menor]) {
                    menor = i;
                }
            }
        }
        if (menor == -1)
            break; // todos os arquivos terminaram

        if (!primeiro) fprintf(saida, ";");
        fprintf(saida, "%d", valores[menor]);
        primeiro = 0;

        if (!ler_proximo(fontes[menor], &valores[menor])) {
            ativos[menor] = 0;
            fclose(fontes[menor]);
            char nome_arquivo[20];
            sprintf(nome_arquivo, "temp%d.txt", menor);
            remove(nome_arquivo);
        }
    }

    fclose(saida);
    printf("Arquivo ordenado: %s\n", arquivo_saida);
}

// Função principal
int main() {
    int M;
    printf("Informe o número máximo de elementos a serem carregados na memória (M): ");
    scanf("%d", &M);

    FILE* dados = fopen("dados.txt", "r");
    if (!dados) {
        perror("Erro ao abrir 'dados.txt'");
        return 1;
    }

    int* buffer = malloc(M * sizeof(int));
    if (!buffer) {
        perror("Erro de alocação");
        return 1;
    }

    int total_blocos = 0;

    while (!feof(dados)) {
        int lidos = carregar_numeros(dados, buffer, M);
        if (lidos == 0) break;

        qsort(buffer, lidos, sizeof(int), comparar);
        salvar_bloco_ordenado(buffer, lidos, total_blocos++);
    }

    fclose(dados);
    free(buffer);

    mesclar_blocos(total_blocos, "resultado.txt");
    return 0;
}
