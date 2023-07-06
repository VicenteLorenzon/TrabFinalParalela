#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>
#include <math.h>

#define QTDE_ENTRADAS 10000
#define QTDE_THREADS 16

typedef struct {
    int idx_inicio;
    int idx_fim;
} DadosThread;

double entradas[QTDE_ENTRADAS][3];
double saidas[QTDE_ENTRADAS];

void calcular(double angulo, double distancia, double alturaElfo, double* comprimentoCorda) {
    double alturaArvore = distancia * tan(angulo * (3.141592654 / 180.0)) + alturaElfo;
    *comprimentoCorda = alturaArvore * 5.0;
}

void* processaCasoTeste(void* arg) {
    DadosThread* dados_thread = (DadosThread*)arg;
    int idx_inicio = dados_thread->idx_inicio;
    int idx_fim = dados_thread->idx_fim;

    for (int i = idx_inicio; i < idx_fim; i++) {
        calcular(entradas[i][0], entradas[i][1], entradas[i][2], &saidas[i]);
    }

    pthread_exit(NULL);
}

int main() {
    FILE* arquivo;

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
    pthread_t threads[QTDE_THREADS];
    DadosThread dados_thread[QTDE_THREADS];

    int casos_por_thread = QTDE_ENTRADAS / QTDE_THREADS;
    int resto = QTDE_ENTRADAS % QTDE_THREADS;
    int idx_inicio = 0;
    int idx_fim;

    for (i = 0; i < QTDE_THREADS; i++) {
        idx_fim = idx_inicio + casos_por_thread + (i < resto ? 1 : 0);
        dados_thread[i].idx_inicio = idx_inicio;
        dados_thread[i].idx_fim = idx_fim;
        pthread_create(&threads[i], NULL, processaCasoTeste, (void*)&dados_thread[i]);
        idx_inicio = idx_fim;
    }

    for (i = 0; i < QTDE_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    QueryPerformanceCounter(&fim);
    tempo = (double)(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart;

    for (i = 0; i < QTDE_ENTRADAS; i++) {
        printf("%f\n", saidas[i]);
    }

    printf("\nTempo: %f\n", tempo);

    return 0;
}
