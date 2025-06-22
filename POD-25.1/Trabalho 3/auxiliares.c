#include <stdio.h>
#include <stdlib.h>
#include "auxiliares.h"

// Cria uma arvore B vazia
BTree *criar_arvore() {
    BTree *arvore = malloc(sizeof(BTree));
    arvore->raiz = NULL;
    return arvore;
}

// Cria um nó com o tipo de nó (folha ou interno)
Node *criar_no(int is_leaf) {
    Node *no = malloc(sizeof(Node));
    no->is_leaf = is_leaf;
    no->num_chaves = 0;
    no->num_ponteiro = 0;
    no->next = NULL;
    no->anterior = NULL;
    no->parent = NULL;

    for (int i = 0; i < DEGREE - 1; i++) no->chaves[i] = 0;
    for (int i = 0; i < DEGREE; i++) no->ponteiros[i] = NULL;
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

// Função auxiliar para inserir uma chave na sua posição correta em um nó
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
    int temp_chaves[DEGREE];
    int temp_size = 0;
    
    // Inserir as chaves existentes e a nova chave em ordem
    int i = 0, j = 0;
    int flag_key_inserted = 0;
    
    while (i < no_cheio->num_chaves || flag_key_inserted == 0) {
        if (flag_key_inserted == 0 && (i >= no_cheio->num_chaves || new_key < no_cheio->chaves[i])) {
            temp_chaves[temp_size++] = new_key;
            flag_key_inserted = 1;
        } else {
            temp_chaves[temp_size++] = no_cheio->chaves[i++];
        }
    }
    
    // Calcular ponto de divisão
    int mid = DEGREE / 2;
    
    // Criar novo nó
    Node *novo_no = criar_no(1);
    
    // Dividir chaves
    no_cheio->num_chaves = mid;
    novo_no->num_chaves = temp_size - mid;
    
    // Copiar primeira metade para o nó original
    for (int k = 0; k < mid; k++) {
        no_cheio->chaves[k] = temp_chaves[k];
    }

    // Copiar segunda metade para o novo nó e zerar o resto do no original
    for (int k = 0; k < novo_no->num_chaves; k++) {
        novo_no->chaves[k] = temp_chaves[mid + k];
        no_cheio->chaves[mid+k] = 0;
    }
    
    // Ajustar ponteiros de lista encadeada (Duplamente)
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

// Função para dividir um nó interno - retorna a chave promovida
int dividir_no_interno(Node *no_cheio, int new_key, Node *novo_filho, Node **novo_no_criado) {
    // Arrays temporários para chaves e ponteiros
    int temp_chaves[DEGREE];
    Node *temp_ponteiros[DEGREE + 1];
    
    // Encontrar posição para inserir nova chave
    int pos = 0;
    while (pos < no_cheio->num_chaves && new_key > no_cheio->chaves[pos]) {
        pos++;
    }
    
    // Copiar chaves e ponteiros para arrays temporários
    for (int i = 0; i < pos; i++) { // Copiar os anteriores da posição que vai ser inserido
        temp_chaves[i] = no_cheio->chaves[i];
        temp_ponteiros[i] = no_cheio->ponteiros[i];
    }
    
    // Colocar a nova chave com os respectivos ponteiros nos arrays temmporários
    temp_chaves[pos] = new_key;
    temp_ponteiros[pos] = no_cheio->ponteiros[pos];
    temp_ponteiros[pos + 1] = novo_filho;
    
    for (int i = pos; i < no_cheio->num_chaves; i++) { // Copiar os valores depois da posição que foi inserido
        temp_chaves[i + 1] = no_cheio->chaves[i];
        temp_ponteiros[i + 2] = no_cheio->ponteiros[i + 1];
    }
    
    // Calcular ponto de divisão
    int mid = DEGREE / 2;
    
    // Criar novo nó interno
    Node *novo_no = criar_no(0);
    *novo_no_criado = novo_no;
    
    // A chave do meio será promovida
    int chave_promovida = temp_chaves[mid];
    
    // Distribuir chaves e ponteiros
    no_cheio->num_chaves = mid;
    novo_no->num_chaves = DEGREE - mid - 1;
    
    // Primeira metade fica no nó original
    for (int i = 0; i < mid; i++) {
        no_cheio->chaves[i] = temp_chaves[i];
        no_cheio->ponteiros[i] = temp_ponteiros[i];
    }
    no_cheio->ponteiros[mid] = temp_ponteiros[mid];
    
    // Segunda metade vai para o novo nó (excluindo a chave promovida)
    for (int i = 0; i < novo_no->num_chaves; i++) {
        novo_no->chaves[i] = temp_chaves[mid + 1 + i];
        novo_no->ponteiros[i] = temp_ponteiros[mid + 1 + i];
    }
    novo_no->ponteiros[novo_no->num_chaves] = temp_ponteiros[DEGREE];
    
    // Atualizar pais dos filhos do novo nó
    for (int i = 0; i <= novo_no->num_chaves; i++) {
        if (novo_no->ponteiros[i]) {
            novo_no->ponteiros[i]->parent = novo_no;
        }
    }
    
    return chave_promovida;
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
    if (pai->num_chaves < DEGREE - 1) {
        // Inserir chave no pai
        // Desloca chaves maiores "para o lado"
        int i = pai->num_chaves - 1;
        while (i >= 0 && pai->chaves[i] > chave_promovida) {
            pai->chaves[i + 1] = pai->chaves[i];
            pai->ponteiros[i + 2] = pai->ponteiros[i + 1];
            i--;
        }
        // Insere a nova chave na posição adequada
        pai->chaves[i + 1] = chave_promovida;
        pai->ponteiros[i + 2] = direita;
        pai->num_chaves++;
        direita->parent = pai;
    } else {
        // Pai também está cheio, precisa dividir
        Node *novo_pai;
        int chave_promovida_pai = dividir_no_interno(pai, chave_promovida, direita, &novo_pai);
        direita->parent = novo_pai;
                
        // Promover recursivamente a chave que subiu da divisão do pai
        promover(arvore, pai, novo_pai, chave_promovida_pai);
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
            return;
        }
    }

    if (no_inserir->num_chaves >= DEGREE - 1) {
        // Nó está cheio, precisa dividir
        Node *novo_no = dividir_no_folha(no_inserir, value);
        
        // Promover a primeira chave do novo nó
        promover(arvore, no_inserir, novo_no, novo_no->chaves[0]);
    } else {
        // Tem espaço no nó (Folha), somente inserir a chave
        insertOrdered(no_inserir, value);
    }
}

void imprimir_arvore(Node *no, int nivel) {
    if (no == NULL) return;

    int i;

    if (no->is_leaf) {
        // Imprimir a folha
        printf("|");
        for (int j = 0; j < nivel; j++) printf("-");
        for (i = 0; i < no->num_chaves; i++) {
            printf("%d ", no->chaves[i]);
        }
        printf("\n");
    } else {
        for (i = 0; i < no->num_chaves; i++) {
            imprimir_arvore(no->ponteiros[i], nivel + 1);
            
            // Imprimir nó interno
            printf("|");
            for (int j = 0; j < nivel; j++) printf("-");
            printf("%d\n", no->chaves[i]);
        }
        // Imprimir ultimo ponteiro
        imprimir_arvore(no->ponteiros[i], nivel + 1);
    }
}

// Função para liberar memória recursivamente
void liberar_arvore(Node *no) {
    if (no == NULL) return;
    
    if (no->is_leaf == 0) {
        for (int i = 0; i <= no->num_chaves; i++) {
            liberar_arvore(no->ponteiros[i]);
        }
    }
    free(no);
}