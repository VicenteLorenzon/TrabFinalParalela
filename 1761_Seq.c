#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define QTDE_ENTRADAS 10000

void calcular(double angulo, double distancia, double alturaElfo, double* comprimentoCorda) {
    double alturaArvore = distancia * tan(angulo * (3.141592654 / 180.0)) + alturaElfo;
    *comprimentoCorda = alturaArvore * 5.0;
}

int main() {
    FILE* arquivo;
    double entradas[QTDE_ENTRADAS][3];
    double saidas[QTDE_ENTRADAS];

    arquivo = fopen("1761_Entrada.txt", "r");

    int i;
    for (i = 0; i < QTDE_ENTRADAS; i++) {
        fscanf(arquivo, "%lf %lf %lf", &entradas[i][0], &entradas[i][1], &entradas[i][2]);
    }

    fclose(arquivo);

    LARGE_INTEGER frequencia, inicio, fim;
    double tempo;

    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&inicio);
    for (i = 0; i < QTDE_ENTRADAS; i++) {
        calcular(entradas[i][0], entradas[i][1], entradas[i][2], &saidas[i]);
    }
    QueryPerformanceCounter(&fim);
    tempo = (double)(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart;

    for (i = 0; i < QTDE_ENTRADAS; i++) {
        printf("%.2lf\n", saidas[i]);
    }

    printf("Tempo: %f\n", tempo);

    return 0;
}
