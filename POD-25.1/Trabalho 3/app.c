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

void printArray(Node no) {
    printf("\nDEBUG - PRINT CHAVES\n-");

  for (int i = 0; i < no.num_chaves; i++) {
    printf(" %d -", no.chaves[i]);
  }

  for (int i = 0; i < no.num_chaves; i++) {
    printf(" %d -", no.ponteiros[i]);
  }
  printf("\n");
}

void insertOrdered(Node *no, int key) {
    int i = no->num_chaves - 1;
    
    while (i >= 0 && no->chaves[i] > key) {
        no->chaves[i + 1] = no->chaves[i];
        i--;
    }
    no->chaves[i + 1] = key;
    
    no->num_chaves++;
}

void dividir_vetor(Node *metade1, Node *metade2, int new_key){
    int j = 0;
    int k = 0;
    while (metade1->chaves[k]<new_key)
    {
        k++;
    }
    
    for (int i = NUMERO_PONT_ARV/2; i < NUMERO_PONT_ARV - 1; i++)
    {
        printf("DEBUG - Metade1[%d] = %d\n", i, metade1->chaves[i]);
        metade2->chaves[j++]=metade1->chaves[i];
        metade2->num_chaves++;
        metade1->chaves[i]=0;
        metade1->num_chaves--;
    }

    int tamanho = 0;
    if (NUMERO_PONT_ARV%2==0){
        tamanho = NUMERO_PONT_ARV/2;
    } else{ 
        tamanho = NUMERO_PONT_ARV/2+1;
    }

    if (k>=NUMERO_PONT_ARV/2)
    {
        insertOrdered(metade2, new_key);
    }
    else
    {
        insertOrdered(metade1, new_key);
    }
    
   
}

void promover(BTree *arvore, Node *metade1, Node *metade2){ // a chave vai ser SEMPRE o 1 valor do vetor chaves da metade 2
    Node *papis = criar_no(0);
    insertOrdered(papis, metade2->chaves[0]);
    // Melhorar essa função de promoção, mas a logica é essa vou promover e onde a chave for inserida, eu vou mudar os ponteiros
    // o da direita do valor inserido é a metade 2 e o da esquerda é a metade 1
    papis->ponteiros[0] = metade1;
    papis->ponteiros[1] = metade2;
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
            Node *new_no = criar_no(1); 
            dividir_vetor(no_inserir, new_no, value);
            no_inserir->next = new_no;
            printf("No 1:\n");
            printArray(*no_inserir);
            printf("No 2:\n");
            printArray(*new_no);
            return;
        }
        insertOrdered(no_inserir, value);
        printArray(*no_inserir);
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