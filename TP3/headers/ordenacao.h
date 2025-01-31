#ifndef ORDENACAO_H
#define ORDENACAO_H

typedef struct {
    int Chave;
    Carta Dado;
} Item;

void BubbleSort(Item* v, int n, int* comparacoes, int* movimentacoes);
void ordenarCartasBubbleSort(Carta vetorRetiradas[NUMERO_DE_CARTAS]);
void SelectSort(Item* v, int n, int* comparacoes, int* movimentacoes);
void ordenarCartasSelectSort(Carta vetorRetiradas[NUMERO_DE_CARTAS]) ;
void Insercao(Item* v, int n, int* comparacoes, int* movimentacoes) ;
void ordenarCartasInsercao(Carta vetorRetiradas[NUMERO_DE_CARTAS]);
void Shellsort(Item* A, int n, int* comparacoes, int* movimentacoes) ;
void ordenarCartasShellSort(Carta vetorRetiradas[NUMERO_DE_CARTAS]) ;
int particionar(Item* A, int baixo, int alto, int* comparacoes, int* movimentacoes) ;
void quicksort(Item* A, int baixo, int alto, int* comparacoes, int* movimentacoes) ;
void ordenarCartasQuickSort(Carta vetorRetiradas[NUMERO_DE_CARTAS]); 
void heapify(Item* A, int n, int i, int* comparacoes, int* movimentacoes) ;
void heapSort(Item* A, int n, int* comparacoes, int* movimentacoes) ;
void ordenarCartasHeapSort(Carta vetorRetiradas[NUMERO_DE_CARTAS]) ;


#endif