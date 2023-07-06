#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>

#define QTDE_ENTRADAS 10000
#define QTDE_THREADS 16

typedef struct {
    int a;
    int b;
    int c;
} CasoTeste;

typedef struct {
    int idx_inicio;
    int idx_fim;
} DadosThread;

CasoTeste casos_teste[QTDE_ENTRADAS];
int saidas[QTDE_ENTRADAS][3];

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

void* processaCasoTeste(void* arg) {
    DadosThread* dados_thread = (DadosThread*)arg;
    int idx_inicio = dados_thread->idx_inicio;
    int idx_fim = dados_thread->idx_fim;

    for (int i = idx_inicio; i < idx_fim; i++) {
        int a = casos_teste[i].a;
        int b = casos_teste[i].b;
        int c = casos_teste[i].c;

        sort(&a, &b, &c);

        saidas[i][0] = a;
        saidas[i][1] = b;
        saidas[i][2] = c;
    }

    return NULL;
}

int main() {
    FILE* arquivo;

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
        printf("%d %d %d\n", saidas[i][0], saidas[i][1], saidas[i][2]);
    }

    printf("\nTempo: %f\n", tempo);

    return 0;
}
