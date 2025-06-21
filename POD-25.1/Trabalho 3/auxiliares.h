#ifndef AUXILIARES_H
#define AUXILIARES_H
#define DEGREE 4

typedef struct node {
    int is_leaf; // 1 se for folha, 0 se for nó
    int num_chaves; // número de chaves atualmente no nó
    int num_ponteiro; // número de ponteiros no nó

    // chaves e ponteiros são arrays de tamanho num_ponteiros-1 e num_ponteiros, respectivamente
    int chaves[DEGREE-1];
    struct node *ponteiros[DEGREE];
    struct node *next; // próximo nó (usado para folhas)
    struct node *anterior; // próximo nó (usado para folhas)
    struct node *parent; // nó pai (usado para nós)
} Node;

typedef struct BTree {
    Node *raiz;
} BTree;

BTree *criar_arvore();
Node *criar_no(int is_leaf);
Node *buscar_no(Node *no, int value);
void printArray(Node no);
void insertOrdered(Node *no, int key);
Node *dividir_no_folha(Node *no_cheio, int new_key);
int dividir_no_interno(Node *no_cheio, int new_key, Node *novo_filho, Node **novo_no_criado);
void inserir_no(BTree *arvore, int value);
void imprimir_arvore(Node *no, int nivel);
void liberar_arvore(Node *no);
void promover(BTree *arvore, Node *no, Node *novo_filho, int chave_promovida);
#endif