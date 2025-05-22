#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

void insere_pilha(Slista *s, int value){
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
void hash01(int M, FILE *entrada, Slista *hash){
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
        insere_pilha(&hash[mod],c);
    }
}

void print_hash01(int M, Slista *hash){
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
int main(){
    int M, tipo;
    FILE *entrada = fopen("dados.txt", "r");
    
    fscanf(entrada, "%d", &M);
    fscanf(entrada, "%d", &tipo);
    
    
    if(tipo == 0){
        Slista hash1[M];
        hash01(M, entrada, hash1);
        print_hash01(M, hash1);
    }
    else{
        int hash2[M], value, mod;
        for (int i = 0; i < M; i++)
        {
            hash2[i] = -1;
        }

        while (fscanf(entrada, "%d;", &value)!=EOF)
        {
            mod = value%M;
            while (hash2[mod]!=-1)
            {
                printf("Debug1\n");
                if(hash2[mod]==-1)break;
                mod = (mod + 1)%M;
            }
            hash2[mod] = value;
        }

        for (int i = 0; i < M; i++)
        {
            printf("%d: ", i);
            if (hash2[i]!=-1)
            {
                printf("%d", i, hash2[i]);
            }
            printf("\n");
        }
    }

    
    return 0;    
}