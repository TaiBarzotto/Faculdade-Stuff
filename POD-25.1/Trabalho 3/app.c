#include <stdio.h>
#include <stdlib.h>
#define NUMERO_PONT_ARV 5

typedef struct node {
    int is_leaf; // 1 se for folha, 0 se for nó
    int num_chaves; // número de chaves atualmente no nó
    int num_ponteiro; // número de ponteiros no nó

    // chaves e ponteiros são arrays de tamanho num_ponteiros-1 e num_ponteiros, respectivamente
    int chaves[NUMERO_PONT_ARV-1];
    struct node *ponteiros[NUMERO_PONT_ARV];
    struct node *next; // próximo nó (usado para folhas)
    struct node *parent; // nó pai (usado para nós)
} Node;

typedef struct BTree {
    Node *raiz;
} BTree;

// Cria uma arvore B vazia
BTree *criar_arvore() {
    BTree *arvore = malloc(sizeof(BTree));
    arvore->raiz = NULL;
    return arvore;
}

Node *criar_no(int is_leaf) {
    Node *no = malloc(sizeof(Node));
    no->is_leaf = is_leaf;
    no->num_chaves = 0;
    no->num_ponteiro = 0;
    no->next = NULL;
    no->parent = NULL;

    for (int i = 0; i < NUMERO_PONT_ARV - 1; i++) no->chaves[i] = 0;
    for (int i = 0; i < NUMERO_PONT_ARV; i++) no->ponteiros[i] = NULL;
    return no;
}

Node *buscar_no(Node *no, int value) {
    if (no == NULL) return NULL;

    // Percorrer as chaves do nó para encontrar a posição correta
    int i = 0;
    while (i < no->num_chaves && value >= no->chaves[i]) {
        i++;
        printf("Comparando %d com %d\n", value, no->chaves[i-1]);
    }

    if (no->is_leaf == 1) {
        printf("Chave %d chegou na folha certa\n", value);
        return no; // Encontrou o nó para inserir
    } else {
        return buscar_no(no->ponteiros[i], value); // Busca recursivamente no filho
    }
}

void printArray(int *array, int size) {
    printf("\nDEBUG - PRINT CHAVES\n");
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void insertOrdered(int *array, int *size, int key) {
    int i = *size - 1;

    while (i >= 0 && array[i] > key) {
        array[i + 1] = array[i];
        i--;
    }
    array[i + 1] = key;

    (*size)++;
}

void dividir_vetor(int *metade1, int *metade2, int new_key){
    int j = 0;
    int k = 0;
    for (k = 0; k < NUMERO_PONT_ARV; k++)
    {
        if (metade1[k]<new_key) break;
    }
    
    for (int i = NUMERO_PONT_ARV/2; i < NUMERO_PONT_ARV - 1; i++)
    {
        printf("DEBUG - Metade1[%d] = %d\n", i, metade1[i]);
        metade2[j++]=metade1[i];
        metade1[i]=0;
    }

    if (k>NUMERO_PONT_ARV/2)
    {
        int tamanho = 0;
        if (NUMERO_PONT_ARV%2==0){
            tamanho = NUMERO_PONT_ARV/2;
        } else{ 
            tamanho = NUMERO_PONT_ARV/2+1;
        }
        insertOrdered(metade2, &tamanho, new_key);
    }
    
    
}

void inserir_no(BTree *arvore, int value) {
    if (arvore->raiz == NULL) {
        arvore->raiz = criar_no(1); // Cria a raiz como um nó folha
        arvore->raiz->chaves[0] = value;
        arvore->raiz->num_chaves = 1;
        return;
    }

    Node *no_inserir = buscar_no(arvore->raiz, value);
    if (no_inserir != NULL) {
        if (no_inserir->num_chaves >= NUMERO_PONT_ARV-1){
            int values[NUMERO_PONT_ARV];
            dividir_vetor(no_inserir->chaves, values, value);
            return;
        }
        int i = 0;
        while (value > no_inserir->chaves[i]) {
            i++;
            if (i >= no_inserir->num_chaves) break; 
        }
        printf("DEBUG: inserindo %d em chaves[%d]\n", value, i);
        insertOrdered(no_inserir->chaves, &no_inserir->num_chaves, value);
        printArray(no_inserir->chaves, no_inserir->num_chaves);
    }
    return;
    
}



int main(){
    BTree *arvore = criar_arvore();

    // Inserir manualmente algumas chaves na folha
    inserir_no(arvore, 5);
    inserir_no(arvore, 20);
    inserir_no(arvore, 15);
    inserir_no(arvore, 10);
    inserir_no(arvore, 16);

    printf("\nFIM\n");

    // Libera a memória alocada
    free(arvore->raiz);
    free(arvore);

    return 0;
}