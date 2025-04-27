#include <stdio.h>
#include <stdlib.h>
#define MEMORIA_MAX 1000000

int main() {
    int M;
    printf("Digite a quantidade de elementos a serem carregados por vez em memória (M): ");
    scanf("%d", &M);

    if (M <= 0 || M > MEMORIA_MAX) {
        printf("Valor de M inválido. Deve ser entre 1 e %d.\n", MEMORIA_MAX);
        return 0;
    }

    //ordenacao_externa(M);
    return 0;
}