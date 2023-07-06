#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define QTDE_ENTRADAS 10000

int f(int n, int k) {
    if (n == 1)
        return 0;
    return (f(n - 1, k) + k) % n;
}

int main() {
    FILE* arquivo;
    int entrada[QTDE_ENTRADAS][2];
    int saidas[QTDE_ENTRADAS];

    arquivo = fopen("1030_Entrada.txt", "r");

    int i;
    for (i = 0; i < QTDE_ENTRADAS; i++) {
        fscanf(arquivo, "%d %d", &entrada[i][0], &entrada[i][1]);
    }

    fclose(arquivo);

    LARGE_INTEGER frequencia, inicio, fim;
    double tempo;

    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&inicio);
    for (i = 0; i < QTDE_ENTRADAS; i++) {
        saidas[i] = f(entrada[i][0], entrada[i][1]) + 1;
    }
    QueryPerformanceCounter(&fim);
    tempo = (double)(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart;

    for (i = 0; i < QTDE_ENTRADAS; i++) {
        printf("Case %d: %d\n", i+1, saidas[i]);
    }

    printf("Tempo : %f\n", tempo);

    return 0;
}
