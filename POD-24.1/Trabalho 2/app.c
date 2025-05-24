#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "auxiliar.h"

int main()
{
    int M, tipo;
    FILE *entrada = fopen("dados.txt", "r"); // abre o arquivo de entrada (dados.txt)
    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }
    fscanf(entrada, "%d", &M);    // Ler tamanho da tabela hash
    fscanf(entrada, "%d", &tipo); // Ler tipo de encadeamento
    // tipo = 0: Endereçamento fechado (com listas encadeadas)
    // tipo = 1: Endereçamento aberto (sondagem linear)

    if (tipo == 0)
    {
        Slista *hash = malloc(M * sizeof(Slista)); // Inicializa a tabela hash de encadeamento fechado
        hash_fechado(M, entrada, hash);
        print_hash_fechado(M, hash);
        free(hash);
    }
    else
    {
        int hash[M]; // Inicializa a tabela hash de encadeamento aberto
        hash_aberto(M, hash, entrada);
        print_hash_aberto(M, hash);
    }

    return 0;
}
