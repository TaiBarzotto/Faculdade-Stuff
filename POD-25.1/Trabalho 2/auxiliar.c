#include "auxiliar.h"
#include <stdio.h>
#include <stdlib.h>

void insere_lista(Slista *s, int value)
{
    Lista *aux = malloc(sizeof(Lista)); // aloca memória
    // atribui valores
    aux->valor = value;
    aux->next = NULL;

    // encadeia, adicionado no final da lista
    if (s->tail == NULL)
    {
        s->head = aux;
        s->tail = aux;
    }
    else
    {
        s->tail->next = aux;
        s->tail = aux;
    }
}

void hash_fechado(int M, FILE *entrada, Slista *hash)
{
    int c;
    int mod, result;

    // Inicializa valores dos sentinelas de cada posição da tabela hash
    for (int i = 0; i < M; i++)
    {
        hash[i].head = NULL;
        hash[i].tail = NULL;
    }

    // Le e insere na tabela hash os valores, na sua lista correspondente
    while (fscanf(entrada, "%d;", &c) != EOF)
    {
        mod = c % M;
        insere_lista(&hash[mod], c);
    }
}

void print_hash_fechado(int M, Slista *hash)
{
    Lista *aux; // cria um auxiliar para liberar memória

    // Percorre as posições da tabela hash
    for (int i = 0; i < M; i++)
    {
        printf("%d: ", i);
        // Percorre até que chegue no fim da lista
        while (hash[i].head != NULL)
        {
            // printa o valor
            printf("%d", hash[i].head->valor);

            aux = hash[i].head; // valor a ser excluido

            hash[i].head = hash[i].head->next; // atualiza o head
            if (hash[i].head != NULL)
                printf("->"); // printar a setinha -> =)
            free(aux);        // libera memória
        }
        printf("\n");
    }
}

void hash_aberto(int M, int *hash, FILE *entrada)
{
    int value, mod, cont = 0;
    // inicializa a tabela hash, com -1
    for (int i = 0; i < M; i++)
    {
        hash[i] = -1;
    }

    while (fscanf(entrada, "%d;", &value) != EOF) // Ler os valores
    {
        mod = value % M;
        if (cont == M)
            break; // Se a tabela hash ta preenchida, para de ler e printa como tá

        // verifica se o espaço está vazio, se não, percorre a tabela até encontrar um espaço vazio
        while (hash[mod] != -1)
        {
            if (hash[mod] == -1)
                break;
            mod = (mod + 1) % M;
        }

        cont++; // conta quantos foram inseridos
        hash[mod] = value;
    }
}

void print_hash_aberto(int M, int *hash)
{
    // Percorre a tabela hash de encadeamento aberto e printa seus valores, no formato exigido pelo professor
    for (int i = 0; i < M; i++)
    {
        printf("%d: ", i);
        if (hash[i] != -1)
        {
            printf("%d", hash[i]);
        }
        printf("\n");
    }
}
