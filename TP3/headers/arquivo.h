#ifndef ARQUIVO_H
#define ARQUIVO_H

void lerConjunto(FILE* arquivo, Carta vetorRetiradas[NUMERO_DE_CARTAS]) ;
void trocarCartas(Carta *a, Carta *b);
void ordenarCartas(Carta vetorRetiradas[NUMERO_DE_CARTAS]);
int compararCores(Carta carta1, Carta carta2);
void selectSort(Carta vetor[], int tamanho);
void imprimirCarta(Carta carta);
void trocarCartas1(Carta *a, Carta *b);
void bubbleSort(Carta vetor[], int n);
void selectionSort(Carta vetor[], int n);
void insertionSort(Carta vetor[], int n, int* movimentos, int* comparacoes) ;
void shellSort(Carta vetor[], int n, int* movimentos, int* comparacoes); 
int particionar2(Carta vetor[], int baixo, int alto, int* comparacoes, int* movimentacoes);
void quickSort(Carta vetor[], int baixo, int alto);
void heapify2(Carta vetor[], int n, int indice) ;
void heapSort2(Carta vetor[], int n) ;
#endif