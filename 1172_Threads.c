#include <stdio.h>
#include <windows.h>
#include <pthread.h>

#define QTDE_ENTRADAS 10000
#define NUM_THREADS 16

typedef struct {
    int inicio;
    int fim;
} DadosThread;

int saida[QTDE_ENTRADAS][10];
int entrada[QTDE_ENTRADAS][10];

void *processaVetor(void *args) {
    DadosThread *dados_thread = (DadosThread *)args;
    int i, j;

    for (i = dados_thread->inicio; i <= dados_thread->fim; i++) {
        int vetor[10];
        for (j = 0; j < 10; j++) {
            vetor[j] = entrada[i][j];
        }
        for (j = 0; j < 10; j++) {
            if (vetor[j] <= 0) {
                vetor[j] = 1;
            }
            saida[i][j] = vetor[j];
        }
    }

    pthread_exit(NULL);
}

int main() {
    FILE *arquivo;
    int i, j;
    LARGE_INTEGER frequencia, inicio, fim;
    double tempo;

    arquivo = fopen("1172_Entrada.txt", "r");

    pthread_t threads[NUM_THREADS];
    DadosThread DadosThread[NUM_THREADS];

    for (i = 0; i < QTDE_ENTRADAS; i++) {
        for (j = 0; j < 10; j++) {
            fscanf(arquivo, "%d", &entrada[i][j]);
        }
    }

    fclose(arquivo);

    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&inicio);

    int elementosPorThread = QTDE_ENTRADAS / NUM_THREADS;
    int elementosRestantes = QTDE_ENTRADAS % NUM_THREADS;
    int indiceInicio = 0;

    for (i = 0; i < NUM_THREADS; i++) {
        DadosThread[i].inicio = indiceInicio;
        DadosThread[i].fim = indiceInicio + elementosPorThread - 1;

        if (elementosRestantes > 0) {
            DadosThread[i].fim++;
            elementosRestantes--;
        }

        pthread_create(&threads[i], NULL, processaVetor, (void *)&DadosThread[i]);

        indiceInicio = DadosThread[i].fim + 1;
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    QueryPerformanceCounter(&fim);
    tempo = (double)(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart;

    for (i = 0; i < QTDE_ENTRADAS; i++) {
        for (j = 0; j < 10; j++) {
            printf("X[%d] = %d\n", j, saida[i][j]);
        }
    }

    printf("Tempo: %f\n", tempo);

    return 0;
}
