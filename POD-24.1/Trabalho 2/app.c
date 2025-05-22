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
        insere_lista(&hash[mod],c);
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

void hash02(int M, int *hash, FILE *entrada){
    int value, mod;
    for (int i = 0; i < M; i++)
    {
        hash[i] = -1;
    }

    while (fscanf(entrada, "%d;", &value)!=EOF)
    {
        mod = value%M;
        while (hash[mod]!=-1)
        {
            if(hash[mod]==-1)break;
            mod = (mod + 1)%M;
        }
        hash[mod] = value;
    }
}

void print_hash02(int M, int *hash){
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
        int hash2[M];
        hash02(M, hash2, entrada);
        print_hash02(M, hash2);
    }

    return 0;    
}
