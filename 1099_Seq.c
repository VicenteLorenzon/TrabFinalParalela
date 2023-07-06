#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define QTDE_ENTRADAS 10000

int calcula(int a, int b) {
    int soma=0;

    if (a > b) {
        int aux = b;
        b = a;
        a = aux;
    }
    if (a%2==0) {
        a++;
    }   
    else{
        a += 2;
    } 
    for (int i = a; i < b; i+=2){
        soma += i;
    }    
    return soma;
}

int main() {
    FILE* arquivo;
    int entrada[QTDE_ENTRADAS][2];
    int saidas[QTDE_ENTRADAS];

    arquivo = fopen("1099_Entrada.txt", "r");

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
        saidas[i] = calcula(entrada[i][0], entrada[i][1]);
    }
    QueryPerformanceCounter(&fim);
    tempo = (double)(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart;

    for (i = 0; i < QTDE_ENTRADAS; i++) {
        printf("%d\n", saidas[i]);
    }

    printf("Tempo : %f\n", tempo);

    return 0;
}
