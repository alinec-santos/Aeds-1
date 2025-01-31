#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../headers/Cartas.h"
#include "../headers/Menu.h"
#include "../headers/ordenacao.h"
#include "../headers/arquivo.h"


void modoAleatorio(){
    int modo;
    printf("Cartas não ordenadas::\n");
    Baralho meuBaralho;
    meuBaralho.tamanho = 0;
    inicializarBaralho(&meuBaralho);
    Carta vetorRetiradas[NUMERO_DE_CARTAS];
    retirarCartasAleatorias(&meuBaralho, vetorRetiradas);
    mostrarVetorCartas(vetorRetiradas);
    printf("\nOpções de ordenação: ");
    printf("\n[1]-BubbleSort\n");
    printf("[2]-SelectSort\n");
    printf("[3]-InsertSort\n");
    printf("[4]-ShellSort\n");
    printf("[5]-QuickSort\n");
    printf("[6]-HeapSort\n");
    printf("[7]-Todas as opções\n");
    printf("Escolha uma opção:");
    scanf("%d",&modo);

    if(modo==1){
        printf("===BubbleSort===\n");
        ordenarCartasBubbleSort(vetorRetiradas);
    }
    
    else if(modo==2){
        printf("===SelectSort===\n");
        ordenarCartasSelectSort(vetorRetiradas);
    }
    else if(modo==3){
        printf("===InsertSort===\n");
        ordenarCartasInsercao(vetorRetiradas);     
    }
    else if(modo==4){
        printf("===ShellSort===\n");
        ordenarCartasShellSort(vetorRetiradas);
    }
    else if(modo==5){
        printf("===QuickSort===\n");
        ordenarCartasQuickSort(vetorRetiradas);
    }
    else if(modo==6){
        printf("===HeapSort===\n");
        ordenarCartasHeapSort(vetorRetiradas);
    }
    else if(modo==7){
        printf("===BubbleSort===\n");
        ordenarCartasBubbleSort(vetorRetiradas);
        printf("===SelectSort===\n");
        ordenarCartasSelectSort(vetorRetiradas);
        printf("===InsertSort===\n");
        ordenarCartasInsercao(vetorRetiradas);
        printf("===ShellSort===\n");
        ordenarCartasShellSort(vetorRetiradas);
        printf("===QuickSort===\n");
        ordenarCartasQuickSort(vetorRetiradas);
        printf("===HeapSort===\n");
        ordenarCartasHeapSort(vetorRetiradas);
    }
    else{
        printf("Ordenação inválida");
    }
    

}

void modoArquivo() {
    FILE *arquivo;
    int modo; 
    char nomeArquivo[50];
    int nConjuntos;
    clock_t start_time, end_time;
    double cpu_time_used;
    int movimentos = 0;
    int comparacoes = 0; 

    // Solicita o nome do arquivo ao usuário
   // printf("Digite o nome do arquivo: ");
   // scanf("%s", nomeArquivo);

    // Tenta abrir o arquivo
    arquivo = fopen("arquivotp3.txt", "r");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Lê a quantidade de conjuntos de cartas
    fscanf(arquivo, "%d", &nConjuntos);

    // Processa cada conjunto
    for (int i = 0; i < nConjuntos; i++) {
        Carta conjunto[NUMERO_DE_CARTAS];
        printf("\n==============================================\n");
        printf("CONJUNTO %d DESORDENADO\n",i+1);
        printf("==============================================\n");
        lerConjunto(arquivo, conjunto);
        printf("==============================================\n");
        printf("\n");


        // Escolhe o algoritmo de ordenação
        int escolha;
        printf("Escolha uma opção:");        
        printf("\n[1]-BubbleSort\n");
        printf("[2]-SelectSort\n");
        printf("[3]-InsertSort\n");
        printf("[4]-ShellSort\n");
        printf("[5]-QuickSort\n");
        printf("[6]-HeapSort\n");
        printf("Escolha uma opção:\n");
        scanf("%d", &escolha);

        // Ordena o conjunto conforme a escolha do usuário
        switch (escolha) {
            case 1:
                start_time = clock(); // Início da contagem de tempo
                printf("\n==============================================\n");
                printf("Conjunto %d Ordenado com Bubble Sort:\n",i+1);
                printf("==============================================\n");
                bubbleSort(conjunto, NUMERO_DE_CARTAS);
                
                break;
            case 2:
                start_time = clock(); // Início da contagem de tempo
                printf("\n==============================================\n");
                printf("Conjunto %d Ordenado com Select Sort:\n",i+1);
                printf("==============================================\n");

                selectionSort(conjunto, NUMERO_DE_CARTAS);
                break;
            case 3:
                start_time = clock(); // Início da contagem de tempo
                printf("\n==============================================\n");
                printf("Conjunto %d Ordenado com Insert Sort:\n",i+1);
                printf("==============================================\n");
                insertionSort(conjunto, NUMERO_DE_CARTAS, &movimentos, &comparacoes);
                printf("\nNúmero de movimentações: %d, Número de comparações %d\n ", movimentos, comparacoes);

                break;
            case 4:
                start_time = clock(); // Início da contagem de tempo
                printf("\n==============================================\n");
                printf("Conjunto %d Ordenado com Shell Sort:\n",i+1);
                printf("==============================================\n");
                shellSort(conjunto, NUMERO_DE_CARTAS, &movimentos, &comparacoes);
                printf("\nNúmero de movimentações: %d, Número de comparações %d\n ", movimentos, comparacoes);

                break;
            case 5:
                start_time = clock(); // Início da contagem de tempo
                printf("\n==============================================\n");
                printf("Conjunto %d Ordenado com Quick Sort:\n",i+1);
                printf("==============================================\n");
                quickSort(conjunto, 0, NUMERO_DE_CARTAS - 1);
                printf("\nNúmero de movimentações: %d, Número de comparações %d\n ", movimentos, comparacoes);


                break;
            case 6:
                start_time = clock(); // Início da contagem de tempo
                printf("\n==============================================\n");
                printf("Conjunto %d Ordenado com Heap Sort:\n",i+1);
                printf("==============================================\n");
                heapSort2(conjunto, NUMERO_DE_CARTAS);
                break;

            default:
                printf("Opcao invalida.\n");
                // Tratar outras ações necessárias, se houver
                break;
        }

       
        for (int j = 0; j < NUMERO_DE_CARTAS; j++) {
            imprimirCarta(conjunto[j]);
        }
        end_time = clock();
        cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("Tempo de execução: %f segundos\n", cpu_time_used);  
        // Imprime uma linha em branco para separar os conjuntos
        printf("\n");
    }


    fclose(arquivo);
}