#include "auxiliar.h"
#include <stdio.h>
#include <stdlib.h>

void insere_lista(Slista *s, int value){
    Lista *aux = malloc(sizeof(Lista));
    aux->valor = value;
    aux->next = NULL;

    if (s->tail == NULL){
        s->head = aux;
        s->tail = aux;
    }
    else{
        s->tail->next = aux;
        s->tail = aux;
    }
}
void hash_fechado(int M, FILE *entrada, Slista *hash){
    int c;
    int mod, result;
    for (int i = 0; i < M; i++) {
        hash[i].head = NULL;
        hash[i].tail = NULL;
    }
    while (1)
    {
        result = fscanf(entrada, "%d;", &c);
        if (result == EOF) break;
        mod = c%M;
        insere_lista(&hash[mod],c);
    }
}

void print_hash_fechado(int M, Slista *hash){
    for (int i = 0; i < M; i++)
    {
        printf("%d: ", i);
        while (hash[i].head!=NULL)
        {
            printf("%d", hash[i].head->valor);
            hash[i].head = hash[i].head->next;
            if (hash[i].head != NULL) printf("->");
        }
        printf("\n");
    }

}

void hash_aberto(int M, int *hash, FILE *entrada){
    int value, mod, cont=0;
    for (int i = 0; i < M; i++)
    {
        hash[i] = -1;
    }

    while (fscanf(entrada, "%d;", &value)!=EOF)
    {
        mod = value%M;
        if (cont == M) break;
        
        while (hash[mod]!=-1)
        {
            if(hash[mod]==-1)break;
            mod = (mod + 1)%M;
        }
        cont++;
        hash[mod] = value;
    }
}

void print_hash_aberto(int M, int *hash){
    for (int i = 0; i < M; i++)
    {
        printf("%d: ", i);
        if (hash[i]!=-1)
        {
            printf("%d", hash[i]);
        }
        printf("\n");
    }
}
