#include <stdio.h>
#include <windows.h>

#define QTDE_ENTRADAS 10000

int main() {
    FILE *arquivo;
    int i, j;
    LARGE_INTEGER frequencia, inicio, fim;
    double tempo;
    int entrada[QTDE_ENTRADAS][10];
    int saida[QTDE_ENTRADAS][10];

    arquivo = fopen("1172_Entrada.txt", "r"); 

    // ENTRADA
    for (i = 0; i < QTDE_ENTRADAS; i++) {
        for (j = 0; j < 10; j++) {
            fscanf(arquivo, "%d", &entrada[i][j]);
        }      
    }   
    fclose(arquivo);

    // PROCESSAMENTO
    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&inicio);
    for (i = 0; i < QTDE_ENTRADAS; i++) {
        for (j = 0; j < 10; j++) {
            if (entrada[i][j] <= 0) {
                entrada[i][j] = 1;
            }
            saida[i][j] = entrada[i][j];
        }        
    }
    QueryPerformanceCounter(&fim);    

    // SAÍDA
    tempo = (double)(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart;

    for (i = 0; i < QTDE_ENTRADAS; i++) {
        for (j = 0; j < 10; j++) {
            // printf("X[%d] = %d\n", j, saida[i][j]);
        }
    }
    printf("Tempo: %f\n", tempo);

    return 0;
}
