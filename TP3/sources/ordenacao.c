#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/Cartas.h"
#include "../headers/Menu.h"
#include "../headers/ordenacao.h"
#include "../headers/arquivo.h"
#include <time.h>
clock_t start_time, end_time;
double cpu_time_used;

void BubbleSort(Item* v, int n, int* comparacoes, int* movimentacoes) {
    int i, j;
    Item aux;

    for (i = 0; i < n - 1; i++) {
        for (j = 1; j < n - i; j++) {
            // Incrementa o contador de comparações
            (*comparacoes)++;

            if (v[j].Dado.cor < v[j - 1].Dado.cor || 
               (v[j].Dado.cor == v[j - 1].Dado.cor && v[j].Dado.valor < v[j - 1].Dado.valor)) {
                aux = v[j];
                v[j] = v[j - 1];
                v[j - 1] = aux;

                // Incrementa o contador de movimentações
                (*movimentacoes)++;
            }
        }
    }
}

void ordenarCartasBubbleSort(Carta vetorRetiradas[NUMERO_DE_CARTAS]) {
    start_time = clock();
    int comparacoes = 0;
    int movimentacoes = 0;

    // Criar um vetor de itens para facilitar a ordenação
    Item vetorItens[NUMERO_DE_CARTAS];
    
    // Preencher o vetor de itens com as cartas a serem ordenadas
    for (int i = 0; i < NUMERO_DE_CARTAS; i++) {
        vetorItens[i].Dado = vetorRetiradas[i];
    }

    // Ordenar o vetor de itens usando o método de ordenação bolha
    BubbleSort(vetorItens, NUMERO_DE_CARTAS, &comparacoes, &movimentacoes);

    // Atualizar o vetor de cartas ordenado
    for (int i = 0; i < NUMERO_DE_CARTAS; i++) {
        vetorRetiradas[i] = vetorItens[i].Dado;
    }
    mostrarVetorCartas(vetorRetiradas);
    // Mostrar o número de comparações e movimentações
    printf("\nNúmero de comparações: %d\n", comparacoes);
    printf("Número de movimentações: %d\n", movimentacoes);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
}

void SelectSort(Item* v, int n, int* comparacoes, int* movimentacoes) {
    for (int i = 0; i < n - 1; i++) {
        int indiceMin = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j].Dado.cor < v[indiceMin].Dado.cor ||
                (v[j].Dado.cor == v[indiceMin].Dado.cor &&
                 v[j].Dado.valor < v[indiceMin].Dado.valor)) {
                indiceMin = j;
            }
        }
        if (indiceMin != i) {
            Item temp = v[i];
            printf("parou\n");
            v[i] = v[indiceMin];
            v[indiceMin] = temp;
            // Incrementa o contador de movimentações
            (*movimentacoes)++;
        }
    }
}

void ordenarCartasSelectSort(Carta vetorRetiradas[NUMERO_DE_CARTAS]) {
    start_time = clock();
    int comparacoes = 0;
    int movimentacoes = 0;
    // Criar um vetor de itens para facilitar a ordenação
    Item vetorItens[NUMERO_DE_CARTAS];
    // Preencher o vetor de itens com as cartas a serem ordenadas
    for (int i = 0; i < NUMERO_DE_CARTAS; i++) {
        vetorItens[i].Dado = vetorRetiradas[i];
    }
    
    // Ordenar o vetor de itens usando o método de ordenação Selection Sort
    SelectSort(vetorItens, NUMERO_DE_CARTAS, &comparacoes, &movimentacoes);

    // Atualizar o vetor de cartas ordenado
    for (int i = 0; i < NUMERO_DE_CARTAS; i++) {
        vetorRetiradas[i] = vetorItens[i].Dado;
    }
    
    // Mostrar o vetor ordenado
    mostrarVetorCartas(vetorRetiradas);

    // Mostrar o número de comparações e movimentações
    printf("\nNúmero de comparações: %d\n", comparacoes);
    printf("Número de movimentações: %d\n", movimentacoes);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
}

void Insercao(Item* v, int n, int* comparacoes, int* movimentacoes) {
    int i, j;
    Item aux;

    for (i = 1; i < n; i++) {
        aux = v[i];
        j = i - 1;
        (*comparacoes)++;  // Incrementa o contador de comparações

        while ((j >= 0) && (aux.Dado.cor < v[j].Dado.cor || (aux.Dado.cor == v[j].Dado.cor && aux.Dado.valor < v[j].Dado.valor))) {
            v[j + 1] = v[j];
            j--;
            (*movimentacoes)++;  // Incrementa o contador de movimentações
            if (j >= 0) {
                (*comparacoes)++;  // Incrementa o contador de comparações
            }
        }

        v[j + 1] = aux;
        (*movimentacoes)++;  // Incrementa o contador de movimentações
    }
}

void ordenarCartasInsercao(Carta vetorRetiradas[NUMERO_DE_CARTAS]) {
    start_time = clock();
    // Criar um vetor de itens para facilitar a ordenação
    Item vetorItens[NUMERO_DE_CARTAS];

    // Preencher o vetor de itens com as cartas a serem ordenadas
    for (int i = 0; i < NUMERO_DE_CARTAS; i++) {
        vetorItens[i].Dado = vetorRetiradas[i];
    }

    // Inicializar os contadores
    int comparacoesInsercao = 0;
    int movimentacoesInsercao = 0;

    // Ordenar o vetor de itens usando o método de ordenação por inserção
    Insercao(vetorItens, NUMERO_DE_CARTAS, &comparacoesInsercao, &movimentacoesInsercao);

    // Atualizar o vetor de cartas ordenado
    for (int i = 0; i < NUMERO_DE_CARTAS; i++) {
        vetorRetiradas[i] = vetorItens[i].Dado;
    }

    mostrarVetorCartas(vetorRetiradas);

    // Mostrar o número de comparações e movimentações
    printf("\nNúmero de comparações: %d\n", comparacoesInsercao);
    printf("Número de movimentações: %d\n", movimentacoesInsercao);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
}

void Shellsort(Item* A, int n, int* comparacoes, int* movimentacoes) {
    int i, j;
    int h = 1;
    Item aux;

    do h = h * 3 + 1; while (h < n);
    
    do {
        h = h / 3;
        
        for (i = h; i < n; i++) {
            aux = A[i];
            j = i;

            (*comparacoes)++;  // Incrementa o contador de comparações

            while (A[j - h].Dado.cor > aux.Dado.cor || 
                   (A[j - h].Dado.cor == aux.Dado.cor && A[j - h].Dado.valor > aux.Dado.valor)) {
                printf("parou\n");

                A[j] = A[j - h];
                j -= h;
                (*movimentacoes)++;  // Incrementa o contador de movimentações

                if (j < h) break;
            }

            A[j] = aux;
        }
    } while (h != 1);
}

void ordenarCartasShellSort(Carta vetorRetiradas[NUMERO_DE_CARTAS]) {
    start_time = clock();
    // Criar um vetor de itens para facilitar a ordenação
    Item vetorItens[NUMERO_DE_CARTAS];
    
    // Preencher o vetor de itens com as cartas a serem ordenadas
    for (int i = 0; i < NUMERO_DE_CARTAS; i++) {
        vetorItens[i].Dado = vetorRetiradas[i];
    }

    // Inicializar os contadores
    int comparacoesShell = 0;
    int movimentacoesShell = 0;

    // Ordenar o vetor de itens usando o método de ordenação shell sort
    Shellsort(vetorItens, NUMERO_DE_CARTAS, &comparacoesShell, &movimentacoesShell);

    // Atualizar o vetor de cartas ordenado
    for (int i = 0; i < NUMERO_DE_CARTAS; i++) {
        vetorRetiradas[i] = vetorItens[i].Dado;
    }

    mostrarVetorCartas(vetorRetiradas);

    // Mostrar o número de comparações e movimentações
    printf("\nNúmero de comparações: %d\n", comparacoesShell);
    printf("Número de movimentações: %d\n", movimentacoesShell);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
}

int particionar(Item* A, int baixo, int alto, int* comparacoes, int* movimentacoes) {
    Item pivo = A[alto];
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        (*comparacoes)++;
        if (A[j].Dado.cor < pivo.Dado.cor || (A[j].Dado.cor == pivo.Dado.cor && A[j].Dado.valor < pivo.Dado.valor)) {
            i++;

            // Troca diretamente na lógica de particionar
            Item temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            // Incrementa o contador de movimentações
            (*movimentacoes)++;
        }
    }

    // Troca do pivo
    Item temp = A[i + 1];
    A[i + 1] = A[alto];
    A[alto] = temp;

    return i + 1;
}

void quicksort(Item* A, int baixo, int alto, int* comparacoes, int* movimentacoes) {
    if (baixo < alto) {
        int indicePivo = particionar(A, baixo, alto, comparacoes, movimentacoes);
        quicksort(A, baixo, indicePivo - 1, comparacoes, movimentacoes);
        quicksort(A, indicePivo + 1, alto, comparacoes, movimentacoes);
    }
}

void ordenarCartasQuickSort(Carta vetorRetiradas[NUMERO_DE_CARTAS]) {
    start_time = clock();
    int comparacoes = 0;
    int movimentacoes = 0;
    // Criar um vetor de itens para facilitar a ordenação
    Item vetorItens[NUMERO_DE_CARTAS];

    // Preencher o vetor de itens com as cartas a serem ordenadas
    for (int i = 0; i < NUMERO_DE_CARTAS; i++) {
        vetorItens[i].Dado = vetorRetiradas[i];
    }

    // Ordenar o vetor de itens usando o método de ordenação Quicksort
    quicksort(vetorItens, 0, NUMERO_DE_CARTAS - 1, &comparacoes, &movimentacoes);

    // Atualizar o vetor de cartas ordenado
    for (int i = 0; i < NUMERO_DE_CARTAS; i++) {
        vetorRetiradas[i] = vetorItens[i].Dado;
    }

    mostrarVetorCartas(vetorRetiradas);

    // Mostrar o número de comparações e movimentações
    printf("\nNúmero de comparações: %d\n", comparacoes);
    printf("Número de movimentações: %d\n", movimentacoes);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
}

void heapify(Item* A, int n, int i, int* comparacoes, int* movimentacoes) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    // Incrementa o contador de comparações
    (*comparacoes)++;

    if (esquerda < n && (A[esquerda].Dado.cor > A[maior].Dado.cor || 
                         (A[esquerda].Dado.cor == A[maior].Dado.cor && A[esquerda].Dado.valor > A[maior].Dado.valor))) {
        maior = esquerda;
    }

    // Incrementa o contador de comparações
    (*comparacoes)++;

    if (direita < n && (A[direita].Dado.cor > A[maior].Dado.cor ||
                        (A[direita].Dado.cor == A[maior].Dado.cor && A[direita].Dado.valor > A[maior].Dado.valor))) {
        maior = direita;
    }

    // Incrementa o contador de comparações
    (*comparacoes)++;

    if (maior != i) {
        // Troca diretamente na lógica do heapify
        Item temp = A[i];
        A[i] = A[maior];
        A[maior] = temp;

        // Incrementa o contador de movimentações
        (*movimentacoes)++;

        // Recursivamente transforma a subárvore afetada em um heap
        heapify(A, n, maior, comparacoes, movimentacoes);
    }
}

void heapSort(Item* A, int n, int* comparacoes, int* movimentacoes) {
    
    // Constrói o heap (reorganiza o array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, n, i, comparacoes, movimentacoes);
    }

    // Extrai um elemento por vez do heap
    for (int i = n - 1; i > 0; i--) {
        // Move a raiz atual para o final
        Item temp = A[0];
        A[0] = A[i];
        A[i] = temp;

        // Incrementa o contador de movimentações
        (*movimentacoes)++;

        // Chama a função heapify para o heap reduzido
        heapify(A, i, 0, comparacoes, movimentacoes);
    }
}

void ordenarCartasHeapSort(Carta vetorRetiradas[NUMERO_DE_CARTAS]) {
    start_time = clock();
    int comparacoes = 0;
    int movimentacoes = 0;

    // Cria um vetor de itens para facilitar a ordenação
    Item vetorItens[NUMERO_DE_CARTAS];

    // Preenche o vetor de itens com as cartas a serem ordenadas
    for (int i = 0; i < NUMERO_DE_CARTAS; i++) {
        vetorItens[i].Dado = vetorRetiradas[i];
    }

    // Ordena o vetor de itens usando o método de ordenação Heap Sort
    heapSort(vetorItens, NUMERO_DE_CARTAS, &comparacoes, &movimentacoes);

    // Atualiza o vetor de cartas ordenado
    for (int i = 0; i < NUMERO_DE_CARTAS; i++) {
        vetorRetiradas[i] = vetorItens[i].Dado;
    }

    // Mostra o vetor ordenado
    mostrarVetorCartas(vetorRetiradas);

    // Mostra o número de comparações e movimentações
    printf("\nNúmero de comparações: %d\n", comparacoes);
    printf("Número de movimentações: %d\n", movimentacoes);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
}
