#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>

#define QTDE_ENTRADAS 10000
#define QTDE_THREADS 16

int entrada[QTDE_ENTRADAS][2];
int saidas[QTDE_ENTRADAS];

typedef struct {
    int idx_inicio;
    int idx_fim;
} DadosThread;

int f(int n, int k) {
    if (n == 1)
        return 0;
    return (f(n - 1, k) + k) % n;
}

void* processaCasoTeste(void* arg) {
    DadosThread* dados_thread = (DadosThread*)arg;
    int idx_inicio = dados_thread->idx_inicio;
    int idx_fim = dados_thread->idx_fim;

    for (int i = idx_inicio; i < idx_fim; i++) {
        int n = entrada[i][0];
        int k = entrada[i][1];
        saidas[i] = f(n, k) + 1;
    }

    return NULL;
}

int main() {
    FILE* arquivo;

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
        printf("Case %d: %d\n", i + 1, saidas[i]);
    }

    printf("\nTempo: %f\n", tempo);

    return 0;
}
