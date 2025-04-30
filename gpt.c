#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Função para ordenar um array usando QuickSort (para ordenação interna)
void quickSort(int arr[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = arr[fim];
        int i = inicio - 1;
        
        for (int j = inicio; j < fim; j++) {
            if (arr[j] <= pivo) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        
        int temp = arr[i + 1];
        arr[i + 1] = arr[fim];
        arr[fim] = temp;
        
        int pi = i + 1;
        
        quickSort(arr, inicio, pi - 1);
        quickSort(arr, pi + 1, fim);
    }
}

// Função para mesclar dois arquivos em um terceiro
void intercalarArquivos(FILE *f1, FILE *f2, FILE *fout) {
    int num1, num2;
    int tem1 = 0, tem2 = 0;
    char c;
    
    // Lê o primeiro valor de cada arquivo
    if (fscanf(f1, "%d%c", &num1, &c) == 2) {
        tem1 = 1;
    }
    
    if (fscanf(f2, "%d%c", &num2, &c) == 2) {
        tem2 = 1;
    }
    
    // Intercala os valores
    while (tem1 && tem2) {
        if (num1 <= num2) {
            fprintf(fout, "%d;", num1);
            if (fscanf(f1, "%d%c", &num1, &c) != 2) {
                tem1 = 0;
            }
        } else {
            fprintf(fout, "%d;", num2);
            if (fscanf(f2, "%d%c", &num2, &c) != 2) {
                tem2 = 0;
            }
        }
    }
    
    // Escreve os valores restantes do arquivo 1
    while (tem1) {
        fprintf(fout, "%d;", num1);
        if (fscanf(f1, "%d%c", &num1, &c) != 2) {
            tem1 = 0;
        }
    }
    
    // Escreve os valores restantes do arquivo 2
    while (tem2) {
        fprintf(fout, "%d;", num2);
        if (fscanf(f2, "%d%c", &num2, &c) != 2) {
            tem2 = 0;
        }
    }
    
    // Adiciona um espaço para separar blocos
    fprintf(fout, " ");
}

// Função para intercalar blocos de dois arquivos
void intercalarBlocos(char *arqEntrada1, char *arqEntrada2, char *arqSaida, int numBlocos) {
    FILE *f1, *f2, *fout;
    
    f1 = fopen(arqEntrada1, "r");
    f2 = fopen(arqEntrada2, "r");
    fout = fopen(arqSaida, "w");
    
    if (!f1 || !f2 || !fout) {
        printf("Erro ao abrir arquivos para intercalação.\n");
        exit(1);
    }
    
    // Intercala os blocos
    for (int i = 0; i < numBlocos; i++) {
        intercalarArquivos(f1, f2, fout);
    }
    
    fclose(f1);
    fclose(f2);
    fclose(fout);
}

// Função para contar o número de blocos em um arquivo
int contarBlocos(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo %s para contar blocos.\n", nomeArquivo);
        exit(1);
    }
    
    int contagem = 0;
    char c;
    int espacoAnterior = 1; // Considera que há um "espaço" antes do primeiro caractere
    
    while ((c = fgetc(arquivo)) != EOF) {
        if (c == ' ') {
            contagem++;
        }
    }
    
    fclose(arquivo);
    return contagem;
}

// Função principal para realizar a ordenação externa
void ordenacaoExterna(char *nomeArquivoEntrada, int M) {
    FILE *entrada, *temp;
    int num, contador = 0;
    int *buffer = (int*)malloc(M * sizeof(int));
    char c;
    
    // Fase 1: Dividir o arquivo em blocos ordenados
    entrada = fopen(nomeArquivoEntrada, "r");
    if (!entrada) {
        printf("Erro ao abrir arquivo de entrada.\n");
        exit(1);
    }
    
    temp = fopen("temp0.txt", "w");
    if (!temp) {
        printf("Erro ao criar arquivo temporário.\n");
        exit(1);
    }
    
    // Lê M elementos, ordena e escreve no arquivo temporário
    while (1) {
        int i = 0;
        
        // Lê M elementos ou até o fim do arquivo
        while (i < M && fscanf(entrada, "%d%c", &num, &c) == 2) {
            buffer[i++] = num;
        }
        
        if (i == 0) break; // Não leu nenhum elemento
        
        // Ordena os elementos lidos
        quickSort(buffer, 0, i - 1);
        
        // Escreve os elementos ordenados no arquivo temporário
        for (int j = 0; j < i; j++) {
            fprintf(temp, "%d;", buffer[j]);
        }
        
        // Separa os blocos com espaço
        fprintf(temp, " ");
        contador++;
    }
    
    fclose(entrada);
    fclose(temp);
    
    // Fase 2: Intercalação dos blocos
    int fase = 0;
    char arqEntrada1[20], arqEntrada2[20], arqSaida[20];
    int numBlocos = contador;
    
    while (numBlocos > 1) {
        sprintf(arqEntrada1, "temp%d.txt", fase);
        sprintf(arqSaida, "temp%d.txt", fase + 1);
        
        FILE *entrada = fopen(arqEntrada1, "r");
        FILE *saida = fopen(arqSaida, "w");
        
        if (!entrada || !saida) {
            printf("Erro ao abrir arquivos para intercalação.\n");
            exit(1);
        }
        
        int numBlocosNovos = 0;
        
        while (numBlocos > 1) {
            // Cria dois arquivos temporários para dividir os blocos
            FILE *temp1 = fopen("tempA.txt", "w");
            FILE *temp2 = fopen("tempB.txt", "w");
            
            if (!temp1 || !temp2) {
                printf("Erro ao criar arquivos temporários.\n");
                exit(1);
            }
            
            // Distribui os blocos entre os dois arquivos temporários
            int metade = (numBlocos + 1) / 2;
            char bufferLeitura[1024];
            int contBloco = 0;
            
            while (fgets(bufferLeitura, sizeof(bufferLeitura), entrada)) {
                if (contBloco < metade) {
                    fputs(bufferLeitura, temp1);
                } else {
                    fputs(bufferLeitura, temp2);
                }
                contBloco++;
                
                if (contBloco >= numBlocos) break;
            }
            
            fclose(temp1);
            fclose(temp2);
            
            // Intercala os blocos dos dois arquivos
            intercalarBlocos("tempA.txt", "tempB.txt", arqSaida, metade);
            
            numBlocosNovos += 1;
            numBlocos -= 2;
        }
        
        // Se sobrar um bloco, copia para o arquivo de saída
        if (numBlocos == 1) {
            char c;
            while ((c = fgetc(entrada)) != EOF) {
                fputc(c, saida);
            }
            numBlocosNovos++;
        }
        
        fclose(entrada);
        fclose(saida);
        
        // Atualiza para a próxima fase
        numBlocos = numBlocosNovos;
        fase++;
        
        // Remove arquivos temporários que não serão mais usados
        if (fase > 1) {
            sprintf(arqEntrada1, "temp%d.txt", fase - 2);
            remove(arqEntrada1);
        }
    }
    
    // Gera nome do arquivo de saída baseado no timestamp
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char nomeArquivoSaida[50];
    sprintf(nomeArquivoSaida, "ordenado_%d%02d%02d_%02d%02d%02d.txt", 
           tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
           tm->tm_hour, tm->tm_min, tm->tm_sec);
    
    // Copia o último arquivo temporário para o arquivo de saída
    sprintf(arqEntrada1, "temp%d.txt", fase);
    FILE *ultimoTemp = fopen(arqEntrada1, "r");
    FILE *arquivoFinal = fopen(nomeArquivoSaida, "w");
    
    if (!ultimoTemp || !arquivoFinal) {
        printf("Erro ao criar arquivo final.\n");
        exit(1);
    }
    
    // Remove o espaço final do arquivo
    char bufferArquivo[1024];
    while (fgets(bufferArquivo, sizeof(bufferArquivo), ultimoTemp)) {
        // Remove o espaço em branco no final do último bloco
        int len = strlen(bufferArquivo);
        if (len > 0 && bufferArquivo[len - 1] == ' ') {
            bufferArquivo[len - 1] = '\0';
        }
        fputs(bufferArquivo, arquivoFinal);
    }
    
    fclose(ultimoTemp);
    fclose(arquivoFinal);
    
    // Remove arquivos temporários
    for (int i = 0; i <= fase; i++) {
        sprintf(arqEntrada1, "temp%d.txt", i);
        remove(arqEntrada1);
    }
    remove("tempA.txt");
    remove("tempB.txt");
    
    free(buffer);
    
    printf("Ordenação concluída! Resultado salvo em: %s\n", nomeArquivoSaida);
}

int main() {
    int M;
    printf("Digite a quantidade de elementos a serem carregados por vez em memória (M): ");
    scanf("%d", &M);
    
    if (M <= 0) {
        printf("O valor de M deve ser positivo.\n");
        return 1;
    }
    
    ordenacaoExterna("dados.txt", M);
    
    return 0;
}