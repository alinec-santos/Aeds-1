#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../headers/Cartas.h"
#include "../headers/ordenacao.h"
#include "../headers/arquivo.h"

void imprimirCarta(Carta carta) {
    const char* cores[] = {"VERDE", "AMARELO", "VERMELHO", "AZUL", "PRETO"};
    const char* valores[] = {"ZERO", "UM", "DOIS", "TRES", "QUATRO", "CINCO", "SEIS", "SETE", "OITO", "NOVE", "PULAR", "VOLTAR", "MAIS2", "MAIS4", "CORINGA"};

    printf("Cor: %s, Valor: %s\n", cores[carta.cor], valores[carta.valor]);
}

void lerConjunto(FILE* arquivo, Carta vetorRetiradas[NUMERO_DE_CARTAS]) {
    for (int j = 0; j < NUMERO_DE_CARTAS; j++) {
        char corStr[20];
        char valorStr[20];

        // Leitura da entrada no formato (cor valor)
        if (fscanf(arquivo, " (%19[^ ] %19[^)])", corStr, valorStr) != 2) {
            // Tratar erro de leitura
            printf("Erro de leitura no arquivo.\n");
            // Outras ações necessárias, como fechar o arquivo e encerrar o programa.
            break;
        }

        // Converte a string da cor para o tipo enum Cor
        if (strcasecmp(corStr, "verde") == 0) {
            vetorRetiradas[j].cor = VERDE;
        } else if (strcasecmp(corStr, "amarelo") == 0) {
            vetorRetiradas[j].cor = AMARELO;
        } else if (strcasecmp(corStr, "vermelho") == 0) {
            vetorRetiradas[j].cor = VERMELHO;
        } else if (strcasecmp(corStr, "azul") == 0) {
            vetorRetiradas[j].cor = AZUL;
        } else if (strcasecmp(corStr, "preto") == 0) {
            vetorRetiradas[j].cor = PRETO;
        } else {
            // Tratar cor não reconhecida
            printf("Cor não reconhecida: %s\n", corStr);
            // Outras ações necessárias, como fechar o arquivo e encerrar o programa.
            break;
        }

        // Converte a string do valor para o tipo enum Valor ou int
        if (strcasecmp(valorStr, "0") == 0) {
            vetorRetiradas[j].valor = ZERO;
        } else if (strcasecmp(valorStr, "1") == 0) {
            vetorRetiradas[j].valor = UM;
        } else if (strcasecmp(valorStr, "2") == 0) {
            vetorRetiradas[j].valor = DOIS;
        } else if (strcasecmp(valorStr, "3") == 0) {
            vetorRetiradas[j].valor = TRES;
        } else if (strcasecmp(valorStr, "4") == 0) {
            vetorRetiradas[j].valor = QUATRO;
        } else if (strcasecmp(valorStr, "5") == 0) {
            vetorRetiradas[j].valor = CINCO;
        } else if (strcasecmp(valorStr, "6") == 0) {
            vetorRetiradas[j].valor = SEIS;
        } else if (strcasecmp(valorStr, "7") == 0) {
            vetorRetiradas[j].valor = SETE;
        } else if (strcasecmp(valorStr, "8") == 0) {
            vetorRetiradas[j].valor = OITO;
        } else if (strcasecmp(valorStr, "9") == 0) {
            vetorRetiradas[j].valor = NOVE;
        } else if (strcasecmp(valorStr, "Pular") == 0) {
            vetorRetiradas[j].valor = PULAR;
        } else if (strcasecmp(valorStr, "Voltar") == 0) {
            vetorRetiradas[j].valor = VOLTAR;
        }  else if (strcasecmp(valorStr, "+2") == 0) {
            vetorRetiradas[j].valor = MAIS2;
        }else if (strcasecmp(valorStr, "+4") == 0) {
            vetorRetiradas[j].valor = MAIS4;
        } else if (strcasecmp(valorStr, "Coringa") == 0) {
            vetorRetiradas[j].valor = CORINGA;
         }

        // Imprimir a carta para verificar
        imprimirCarta(vetorRetiradas[j]);
    }
}
    
// Função para trocar duas cartas de posição
void trocarCartas1(Carta *a, Carta *b) {
    Carta temp = *a;
    *a = *b;
    *b = temp;
    
}

// Função de ordenação Bubble Sort
void bubbleSort(Carta vetor[], int n) {
    int movimentos = 0; 
    int comparacoes = 0; 
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++; 

            if (vetor[j].cor > vetor[j + 1].cor || 
                (vetor[j].cor == vetor[j + 1].cor && vetor[j].valor > vetor[j + 1].valor)) {
                movimentos++; 
                trocarCartas1(&vetor[j], &vetor[j + 1]);

            }

        }

    }
    printf("Número de movimentações: %d, Número de comparações %d\n ", movimentos, comparacoes);
}

// Função de ordenação Selection Sort
void selectionSort(Carta vetor[], int n) {
    int movimentos = 0; 
    int comparacoes = 0;     
    for (int i = 0; i < n - 1; i++) {
        int menorIndice = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (vetor[j].cor < vetor[menorIndice].cor || 
                (vetor[j].cor == vetor[menorIndice].cor && vetor[j].valor < vetor[menorIndice].valor)) {
                menorIndice = j;
            }
        }
        trocarCartas1(&vetor[i], &vetor[menorIndice]);
        movimentos++; 
    }
    printf("Número de movimentações: %d, Número de comparações %d\n ", movimentos, comparacoes);

}

// Função de ordenação Insertion Sort
void insertionSort(Carta vetor[], int n, int* movimentos,  int* comparacoes) {
    int i, j;
    Carta chave;
    for (i = 1; i < n; i++) {

        chave = vetor[i];
        j = i - 1;
        (*comparacoes)++;


        while (j >= 0 && (vetor[j].cor > chave.cor || 
                          (vetor[j].cor == chave.cor && vetor[j].valor > chave.valor))) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
            (*comparacoes)++;  // Incrementa o contador de movimentações


        }
        vetor[j + 1] = chave;
        (*movimentos)++;

    }
}

// Função de ordenação Shell Sort
void shellSort(Carta vetor[], int n, int* movimentos, int* comparacoes) {
    for (int intervalo = n / 2; intervalo > 0; intervalo /= 2) {

        for (int i = intervalo; i < n; i += 1) {
            (*comparacoes)++;  // Incrementa o contador de movimentações


            Carta temp = vetor[i];
            int j;
            for (j = i; j >= intervalo && (vetor[j - intervalo].cor > temp.cor ||
                                           (vetor[j - intervalo].cor == temp.cor && vetor[j - intervalo].valor > temp.valor)); j -= intervalo) {
                vetor[j] = vetor[j - intervalo];
                (*comparacoes)++;  // Incrementa o contador de movimentações


            }
            vetor[j] = temp;
            (*movimentos)++;  // Incrementa o contador de movimentações
        }
    }
}

// Função auxiliar para o Quick Sort
int particionar2(Carta vetor[], int baixo, int alto, int* comparacoes, int* movimentacoes) {  
    Carta pivo = vetor[alto];
    int i = baixo - 1;

    for (int j = baixo; j <= alto - 1; j++) {
        (*comparacoes)++;

        if (vetor[j].cor < pivo.cor || (vetor[j].cor == pivo.cor && vetor[j].valor < pivo.valor)) {
            i++;
            trocarCartas1(&vetor[i], &vetor[j]);
            (*movimentacoes)++;
            (*comparacoes)++;  // Incrementa o contador de movimentações


        }
    }

    trocarCartas1(&vetor[i + 1], &vetor[alto]);
    (*movimentacoes)++;
    return i + 1;



}

// Função de ordenação Quick Sort
void quickSort(Carta vetor[], int baixo, int alto) {
    int movimentos = 0; 
    int comparacoes = 0;     
    if (baixo < alto) {
        comparacoes++; 
        int indicePivo = particionar2(vetor, baixo, alto, &comparacoes, &movimentos);


        quickSort(vetor, baixo, indicePivo - 1);
        quickSort(vetor, indicePivo + 1, alto);

    }

}

// Função auxiliar para o Heap Sort
void heapify2(Carta vetor[], int n, int indice) {
    int movimentos = 0; 
    int comparacoes = 0;     
    int maior = indice;
    int filhoEsquerda = 2 * indice + 1;
    int filhoDireita = 2 * indice + 2;

    if (filhoEsquerda < n && (vetor[filhoEsquerda].cor > vetor[maior].cor ||
                              (vetor[filhoEsquerda].cor == vetor[maior].cor && vetor[filhoEsquerda].valor > vetor[maior].valor))) {
        maior = filhoEsquerda;
        comparacoes++;
    }

    if (filhoDireita < n && (vetor[filhoDireita].cor > vetor[maior].cor ||
                             (vetor[filhoDireita].cor == vetor[maior].cor && vetor[filhoDireita].valor > vetor[maior].valor))) {
        maior = filhoDireita;
        comparacoes++; 
    }

    if (maior != indice) {
        trocarCartas1(&vetor[indice], &vetor[maior]);
        movimentos++;

        heapify2(vetor, n, maior);
    }

}

// Função de ordenação Heap Sort
void heapSort2(Carta vetor[], int n ) {
    int movimentos = 0; 
    int comparacoes = 0; 
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify2(vetor, n, i);
        comparacoes++; 
    }

    for (int i = n - 1; i > 0; i--) {
        trocarCartas1(&vetor[0], &vetor[i]);
        movimentos++; 

    

        heapify2(vetor, i, 0);
    }
    printf("Número de movimentações: %d, Número de comparações %d\n ", movimentos, comparacoes);

}