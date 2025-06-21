#include <stdio.h>
#include <stdlib.h>
#include "auxiliares.h"

int main(){
    BTree *arvore = criar_arvore();
    int value;
    FILE *entrada = fopen("dados.txt", "r");
    while (fscanf(entrada, "%d;", &value) != EOF)
    {
        inserir_no(arvore, value);
    }

    imprimir_arvore(arvore->raiz, 0);

    // Libera a memória alocada adequadamente
    liberar_arvore(arvore->raiz);
    free(arvore);

    return 0;
}
