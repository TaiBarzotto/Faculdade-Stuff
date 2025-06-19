#include <stdio.h>
#include <stdlib.h>
#define NUMERO_PONT_ARV 4

typedef struct node {
    int is_leaf; // 1 se for folha, 0 se for nó
    int num_chaves; // número de chaves atualmente no nó
    int num_ponteiro; // número de ponteiros no nó

    // chaves e ponteiros são arrays de tamanho num_ponteiros-1 e num_ponteiros, respectivamente
    int chaves[NUMERO_PONT_ARV-1];
    struct node *ponteiros[NUMERO_PONT_ARV];
    struct node *next; // próximo nó (usado para folhas)
    struct node *anterior; // próximo nó (usado para folhas)
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
    no->anterior = NULL;
    no->parent = NULL;

    for (int i = 0; i < NUMERO_PONT_ARV - 1; i++) no->chaves[i] = 0;
    for (int i = 0; i < NUMERO_PONT_ARV; i++) no->ponteiros[i] = NULL;
    return no;
}

Node *buscar_no(Node *no, int value) {
    if (no == NULL) return NULL;

    // Percorrer as chaves do nó para encontrar a posição correta
    int i = 0;
    while (i < no->num_chaves && value > no->chaves[i]) {
        i++;
    }

    if (no->is_leaf == 1) {
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

// Função para dividir um nó folha
Node *dividir_no_folha(Node *no_cheio, int new_key) {
    // Criar array temporário com todas as chaves (incluindo a nova)
    int temp_chaves[NUMERO_PONT_ARV];
    int temp_size = 0;
    
    // Inserir as chaves existentes e a nova chave em ordem
    int i = 0, j = 0;
    int key_inserted = 0;
    
    while (i < no_cheio->num_chaves || !key_inserted) {
        if (!key_inserted && (i >= no_cheio->num_chaves || new_key < no_cheio->chaves[i])) {
            temp_chaves[temp_size++] = new_key;
            key_inserted = 1;
        } else {
            temp_chaves[temp_size++] = no_cheio->chaves[i++];
        }
    }
    
    int mid = NUMERO_PONT_ARV / 2;
    
    Node *novo_no = criar_no(1);
    
    no_cheio->num_chaves = mid;
    novo_no->num_chaves = temp_size - mid;
    
    // Copiar primeira metade para o nó original
    for (int k = 0; k < mid; k++) {
        no_cheio->chaves[k] = temp_chaves[k];
    }
    
    // Copiar segunda metade para o novo nó
    for (int k = 0; k < novo_no->num_chaves; k++) {
        novo_no->chaves[k] = temp_chaves[mid + k];
    }
    
    // Ajustar ponteiros de lista ligada
    novo_no->next = no_cheio->next;
    if (no_cheio->next) {
        no_cheio->next->anterior = novo_no;
    }
    no_cheio->next = novo_no;
    novo_no->anterior = no_cheio;
    
    // Definir mesmo pai
    novo_no->parent = no_cheio->parent;
    
    return novo_no;
}

// Função para dividir um nó interno
Node *dividir_no_interno(Node *no_cheio, int new_key, Node *novo_filho) {
    // Arrays temporários para chaves e ponteiros
    int temp_chaves[NUMERO_PONT_ARV];
    Node *temp_ponteiros[NUMERO_PONT_ARV + 1];
    
    // Encontrar posição para inserir nova chave
    int pos = 0;
    while (pos < no_cheio->num_chaves && new_key > no_cheio->chaves[pos]) {
        pos++;
    }
    
    // Copiar chaves e ponteiros para arrays temporários
    for (int i = 0; i < pos; i++) {
        temp_chaves[i] = no_cheio->chaves[i];
        temp_ponteiros[i] = no_cheio->ponteiros[i];
    }
    
    temp_chaves[pos] = new_key;
    temp_ponteiros[pos] = no_cheio->ponteiros[pos];
    temp_ponteiros[pos + 1] = novo_filho;
    
    for (int i = pos; i < no_cheio->num_chaves; i++) {
        temp_chaves[i + 1] = no_cheio->chaves[i];
        temp_ponteiros[i + 2] = no_cheio->ponteiros[i + 1];
    }
    
    // Calcular ponto de divisão
    int mid = NUMERO_PONT_ARV / 2;
    
    // Criar novo nó interno
    Node *novo_no = criar_no(0);
    
    // Distribuir chaves e ponteiros
    no_cheio->num_chaves = mid;
    novo_no->num_chaves = NUMERO_PONT_ARV - mid - 1;
    
    // Primeira metade fica no nó original
    for (int i = 0; i < mid; i++) {
        no_cheio->chaves[i] = temp_chaves[i];
        no_cheio->ponteiros[i] = temp_ponteiros[i];
    }
    no_cheio->ponteiros[mid] = temp_ponteiros[mid];
    
    // Segunda metade vai para o novo nó
    for (int i = 0; i < novo_no->num_chaves; i++) {
        novo_no->chaves[i] = temp_chaves[mid + 1 + i];
        novo_no->ponteiros[i] = temp_ponteiros[mid + 1 + i];
    }
    novo_no->ponteiros[novo_no->num_chaves] = temp_ponteiros[NUMERO_PONT_ARV];
    
    // Atualizar pais dos filhos do novo nó
    for (int i = 0; i <= novo_no->num_chaves; i++) {
        if (novo_no->ponteiros[i]) {
            novo_no->ponteiros[i]->parent = novo_no;
        }
    }
    
    // A chave do meio será promovida
    int chave_promovida = temp_chaves[mid];
    
    return novo_no;
}

void promover(BTree *arvore, Node *esquerda, Node *direita, int chave_promovida) {
    Node *pai = esquerda->parent;
    
    if (pai == NULL) {
        // Criar nova raiz
        pai = criar_no(0);
        arvore->raiz = pai;
        pai->chaves[0] = chave_promovida;
        pai->num_chaves = 1;
        pai->ponteiros[0] = esquerda;
        pai->ponteiros[1] = direita;
        esquerda->parent = pai;
        direita->parent = pai;
        return;
    }
    
    // Verificar se o pai tem espaço
    if (pai->num_chaves < NUMERO_PONT_ARV - 1) {
        // Inserir chave no pai
        int i = pai->num_chaves - 1;
        while (i >= 0 && pai->chaves[i] > chave_promovida) {
            pai->chaves[i + 1] = pai->chaves[i];
            pai->ponteiros[i + 2] = pai->ponteiros[i + 1];
            i--;
        }
        
        pai->chaves[i + 1] = chave_promovida;
        pai->ponteiros[i + 2] = direita;
        pai->num_chaves++;
        direita->parent = pai;
    } else {
        // Pai também está cheio, precisa dividir
        Node *novo_pai = dividir_no_interno(pai, chave_promovida, direita);
        direita->parent = novo_pai;
        
        // Promover recursivamente
        int chave_meio = pai->chaves[NUMERO_PONT_ARV / 2];
        promover(arvore, pai, novo_pai, chave_meio);
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
    
    // Verificar se a chave já existe
    for (int i = 0; i < no_inserir->num_chaves; i++) {
        if (no_inserir->chaves[i] == value) {
            printf("Chave %d já existe na árvore\n", value);
            return;
        }
    }

    if (no_inserir->num_chaves >= NUMERO_PONT_ARV - 1) {
        // Nó está cheio, precisa dividir
        Node *novo_no = dividir_no_folha(no_inserir, value);
        
        // Promover a primeira chave do novo nó
        int chave_promovida = novo_no->chaves[0];
        promover(arvore, no_inserir, novo_no, chave_promovida);
        
        printf("Divisão realizada. Chave promovida: %d\n", chave_promovida);
        printf("Nó esquerdo: ");
        printArray(*no_inserir);
        printf("Nó direito: ");
        printArray(*novo_no);
    } else {
        // Nó tem espaço, inserir normalmente
        insertOrdered(no_inserir, value);
        printf("Inserido %d: ", value);
        printArray(*no_inserir);
    }
}

void imprimir_arvore(Node *no, int nivel) {
    if (no == NULL) return;

    int i;

    if (no->is_leaf) {
        // Indentação: folhas ficam um nível abaixo
        printf("|");
        for (int j = 0; j < nivel; j++) printf("-");
        for (i = 0; i < no->num_chaves; i++) {
            printf("%d ", no->chaves[i]);
        }
        printf("\n");
    } else {
        for (i = 0; i < no->num_chaves; i++) {
            imprimir_arvore(no->ponteiros[i], nivel + 1);
            
            // Nó interno: chave de separação
            printf("|");
            for (int j = 0; j < nivel; j++) printf("-");
            printf("%d\n", no->chaves[i]);
        }
        // Último ponteiro
        imprimir_arvore(no->ponteiros[i], nivel + 1);
    }
}

// Função para liberar memória recursivamente
void liberar_arvore(Node *no) {
    if (no == NULL) return;
    
    if (!no->is_leaf) {
        for (int i = 0; i <= no->num_chaves; i++) {
            liberar_arvore(no->ponteiros[i]);
        }
    }
    free(no);
}

int main(){
    BTree *arvore = criar_arvore();
    
    // Inserir manualmente algumas chaves na folha
    inserir_no(arvore, 5);
    inserir_no(arvore, 15);
    inserir_no(arvore, 18);
    inserir_no(arvore, 20);
    inserir_no(arvore, 25);
    inserir_no(arvore, 30);
    inserir_no(arvore, 35);
    inserir_no(arvore, 40);
    inserir_no(arvore, 50);
    inserir_no(arvore, 70);

    printf("\n=== ESTRUTURA FINAL DA ARVORE ===\n");
    imprimir_arvore(arvore->raiz, 0);
    printf("\nFIM\n");

    // Libera a memória alocada adequadamente
    liberar_arvore(arvore->raiz);
    free(arvore);

    return 0;
}
