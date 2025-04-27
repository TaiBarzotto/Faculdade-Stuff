#include <stdio.h>
#include <stdlib.h>

void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particiona(int arr[], int inicio, int fim) {
    int pivot = arr[fim];
    int i = (inicio - 1); 

    for (int j = inicio; j < fim; j++) {
        if (arr[j] <= pivot) {
            i++; 
            troca(&arr[i], &arr[j]); 
        }
    }
    troca(&arr[i + 1], &arr[fim]); // Coloca o pivô na posição correta
    return (i + 1); 
}

void quickSort(int arr[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particiona(arr, inicio, fim);

        quickSort(arr, inicio, pivo - 1);
        quickSort(arr, pivo + 1, fim);
    }
}
