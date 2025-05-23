#include <stdio.h>
#ifndef AUXILIAR_H
#define AUXILIAR_H
typedef struct lista
{
    int valor;
    struct lista *next;
} Lista;

typedef struct sentinela
{
    Lista *head;
    Lista *tail;
} Slista;

void insere_lista(Slista *s, int value);
void hash_fechado(int M, FILE *entrada, Slista *hash);
void print_hash_fechado(int M, Slista *hash);
void hash_aberto(int M, int *hash, FILE *entrada);
void print_hash_aberto(int M, int *hash);
#endif
