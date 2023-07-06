#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define QTDE_ENTRADAS 10000

typedef struct {
    int a;
    int b;
    int c;
} CasoTeste;

void sort(int* a, int* b, int* c) {
    int aux;

    if (*a > *b) {
        aux = *a;
        *a = *b;
        *b = aux;
    }

    if (*a > *c) {
        aux = *a;
        *a = *c;
        *c = aux;
    }

    if (*b > *c) {
        aux = *b;
        *b = *c;
        *c = aux;
    }
}

int main() {
    FILE* arquivo;
    CasoTeste casos_teste[QTDE_ENTRADAS];
    int saidas[QTDE_ENTRADAS][3];

    arquivo = fopen("1042_Entrada.txt", "r");

    int i;
    for (i = 0; i < QTDE_ENTRADAS; i++) {
        fscanf(arquivo, "%d %d %d", &casos_teste[i].a, &casos_teste[i].b, &casos_teste[i].c);
    }

    fclose(arquivo);

    LARGE_INTEGER frequencia, inicio, fim;
    double tempo;

    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&inicio);
    for (i = 0; i < QTDE_ENTRADAS; i++) {
        int a = casos_teste[i].a;
        int b = casos_teste[i].b;
        int c = casos_teste[i].c;

        sort(&a, &b, &c);

        saidas[i][0] = a;
        saidas[i][1] = b;
        saidas[i][2] = c;
    }
    QueryPerformanceCounter(&fim);
    tempo = (double)(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart;

    for (i = 0; i < QTDE_ENTRADAS; i++) {
        printf("%d %d %d\n", saidas[i][0], saidas[i][1], saidas[i][2]);
    }

    printf("\nTempo: %f\n", tempo);

    return 0;
}
