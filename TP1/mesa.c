#include <stdio.h>
#include "mesa.h"
#include "carta.h"
#include "listaCartas.h"
#include <string.h>
#include <stdlib.h>
#ifndef MESA_H
#define MESA_H

void Inicializar(MesaCartas *mesa){
    mesa->baralho = CriarListaVazia();
    mesa->descarte = CriarListaVazia();
    for(int i=0;i<4;i++){ //como é um arranjo, temos que percorrer ele todo e tornar cada posição vazia 
        mesa->bases[i] = CriarListaVazia();
    }
    for(int i=0;i<7;i++){ //como é um arranjo, temos que percorrer ele todo e tornar cada posição vazia 
        mesa->tableau[i] = CriarListaVazia();
    }
    mesa->pontuacao=0; 
}
void CarregarBaralhoAleatorio(MesaCartas *mesa) {
    EmbaralharLista(mesa->baralho);}

void CarregarBaralho(MesaCartas* mesa) {
    // Inicialize o baralho vazio
    mesa->baralho = CriarListaVazia();
    // Loop para criar as cartas e adicioná-las ao baralho
    for (Tipovalor valor = A; valor <= K; valor++) {
        for (Tiponaipe naipe = PAUS; naipe <= OUROS; naipe++) {
            Carta carta;
            Inicializa(&carta, naipe, valor, BAIXO);
            AdicionarCartaAoTopo(mesa->baralho, &carta);
        }
    } 
    EmbaralharLista(mesa->baralho);   
}
void Preparar(MesaCartas *mesa){
    for(int i = 0; i < 7; i++){
        TransferirCartas(mesa->baralho, mesa->tableau[i], i+1);
    }
    for(int i = 0; i < 7; i++){
        Setposicao(&mesa->tableau[i]->topo->carta, CIMA);
    }
}
int VerificarVitoria(MesaCartas* mesa) {
    // Verifique se todas as bases contêm todas as cartas do mesmo naipe (copas, espadas, paus, ouros) em ordem crescente.
    for (Tiponaipe naipe = PAUS; naipe <= OUROS; naipe++) {
        bool baseCompleta = true;
        // Verifique a base correspondente ao naipe atual
        ListaDeCartas* base = mesa->bases[naipe];
        if (TamanhoDaLista(base) != 13) {
            baseCompleta = false; // Se não houver 13 cartas na base, não está completa.
        } else {
            // Verifique se as cartas estão em ordem crescente e alternam entre preto e vermelho.
            Carta* cartaAnterior = CartaNoTopo(base);
            for (int i = 1; i < 13; i++) {
                Carta* cartaAtual = CartaNaPosicao(base, i);
                // Verifique a ordem crescente
                if (cartaAtual->valor != cartaAnterior->valor + 1) {
                    baseCompleta = false;
                    break; // Não está em ordem crescente, saia do loop.
                }
                // Verifique a alternância de cores
                if ((cartaAnterior->naipe == PAUS || cartaAnterior->naipe == ESPADAS) &&
                    (cartaAtual->naipe == COPAS || cartaAtual->naipe == OUROS)) {
                    baseCompleta = false;
                    break; // Não estão alternando as cores, saia do loop.
                } else if ((cartaAnterior->naipe == COPAS || cartaAnterior->naipe == OUROS) &&
                           (cartaAtual->naipe == PAUS || cartaAtual->naipe == ESPADAS)) {
                    baseCompleta = false;
                    break; // Não estão alternando as cores, saia do loop.
                }
                cartaAnterior = cartaAtual;
            }
        }
        // Se uma base não estiver completa, o jogo não está ganho.
        if (!baseCompleta) {
            printf("O jogo ainda não foi vencido.\n");
            return 0; // O jogo não foi vencido, retorne 0.
        }
    }
    // Se todas as bases estiverem completas, o jogador ganhou.
    printf("Você ganhou o jogo de paciência!\n");
    return 1; // O jogo foi vencido, retorne 1.
}
void Exibir(MesaCartas* mesa) {
    printf("===== Mesa de Cartas =====\n");
    for(int i = 0; i< 7; i++){
        printf("Coluna[%d]\n", i);
        ExibirLista(mesa->tableau[i]);
    }
    // Exibir as bases na horizontal
    printf("Bases: ");
    for (int naipe = PAUS; naipe <= OUROS; naipe++) {
        ListaDeCartas* base = mesa->bases[naipe];
        if (!EstaVazia(base)) {
            Carta* carta1 = CartaNoTopo(base);
            printf("Carta na base [%d]: ", naipe); // Impressão de depuração
            Imprimi(carta1);
            printf("  "); // Espaço entre as cartas
        } else {
            printf("    "); // Espaço vazio
        }
    }
    printf("\n");
    // Exibir o baralho, o descarte e a pontuação
    printf("Baralho: %d cartas\n", TamanhoDaLista(mesa->baralho));
    printf("Descarte: ");
    ExibirLista(mesa->descarte);
    printf("\n");
    printf("Pontuação: %d\n", mesa->pontuacao);
    printf("==========================\n");
}
void ComprarCarta(MesaCartas *mesa) {
   if (!EstaVazia(mesa->baralho)) { // se a  mesa estiver precisando de uma carta, 
      Carta *carta = CartaNoTopo(mesa->baralho); // vamos chamar o baralho para pegar uma carta
      carta->posicao = CIMA; // a posicao da carta apos a saida do baralho é sempre para cima, assim, iremos identificar sua posicao chamando o carta->posicao
      AdicionarCartaAoTopo(mesa->descarte, carta); // vamos adicionar a carta ou em cima do descarte
      RetirarCartaDoTopo(mesa->baralho); // aqui vamos retirar a carta do topo do baralho
   }
}
void DescarteBase(MesaCartas *mesa) {
    Carta *descarte = CartaNoTopo(mesa->descarte);
    if (descarte != NULL) {
        // Verifique cada base em busca do naipe correspondente.
        for (int naipeBase = 0; naipeBase < 4; naipeBase++) {
            ListaDeCartas* base = mesa->bases[naipeBase];
            if (EstaVazia(base)) {
                // Se a base estiver vazia, somente cartas As podem ser adicionadas.
                if (descarte->valor == A) {
                    AdicionarCartaAoTopo(base, descarte);
                    RetirarCartaDoTopo(mesa->descarte);
                    mesa->pontuacao += 10;
                    break;
                }
            } else {
                // Se a base não estiver vazia, verifique se a carta pode ser adicionada à sequência.
                Carta* cartaTopoBase = CartaNoTopo(base);
                if (descarte->naipe == cartaTopoBase->naipe && descarte->valor == cartaTopoBase->valor + 1) {
                    AdicionarCartaAoTopo(base, descarte);
                    RetirarCartaDoTopo(mesa->descarte);
                    mesa->pontuacao += 10;
                    break;
                }
            }
        }
    }
}

void DescarteTableau(MesaCartas *mesa, int indiceColunaTableau) {
    // Verifica se o descarte não está vazio.
    if (!EstaVazia(mesa->descarte)) {
        // Verifica se o índice da coluna do tableau é válido.
        if (indiceColunaTableau >= 0 && indiceColunaTableau < 7) {
            ListaDeCartas *colunaTableau = mesa->tableau[indiceColunaTableau];
            
            // Verifica se a coluna do tableau está vazia.
            if (EstaVazia(colunaTableau)) {
                // Se a coluna estiver vazia, verifica se a carta no descarte é um rei.
                if (mesa->descarte->topo->carta.valor == K) {
                    // Move a carta do topo do descarte para o topo da coluna do tableau.
                    TransferirCartas(mesa->descarte, colunaTableau, 1);
                    mesa->pontuacao += 5;
                } else {
                    printf("A coluna do tableau selecionada está vazia e só aceita um rei.\n");
                }
            } else {
                // Se a coluna do tableau não estiver vazia, verifica a sequência.
                if (Verificasequenciaalt(&mesa->descarte->topo->carta, &colunaTableau->topo->carta)) {
                    // Move a carta do topo do descarte para o topo da coluna do tableau.
                    TransferirCartas(mesa->descarte, colunaTableau, 1);
                    mesa->pontuacao += 5;
                } else {
                    printf("A coluna do tableau selecionada está cheia ou a sequência não é válida. Escolha outra coluna.\n");
                }
            }
        } else {
            printf("O índice da coluna do tableau é inválido. Escolha um índice válido.\n");
        }
    } else {
        printf("O descarte está vazio. Não é possível mover cartas.\n");
    }
}

void TableauBase(MesaCartas *mesa, int colunaTableau) {
    Carta* cartaTableau = CartaNoTopo(mesa->tableau[colunaTableau]);
    if (cartaTableau == NULL) {
        return; // Se não houver carta no topo, não há nada a fazer.
    }
    for (int naipeBase = 0; naipeBase < 4; naipeBase++) {
        Carta* cartaBaseTopo = CartaNoTopo(mesa->bases[naipeBase]);
        if (EstaVazia(mesa->bases[naipeBase]) && cartaTableau->valor == A) {
            // Se a base estiver vazia e a carta for um Ás, mova a carta para a base.
            MoverCartaParaBase(mesa, colunaTableau, naipeBase);
            return;
        }
        else if (!EstaVazia(mesa->bases[naipeBase]) &&
                 cartaTableau->valor == cartaBaseTopo->valor + 1 &&
                 cartaTableau->naipe == cartaBaseTopo->naipe) {
            // Se a carta do tableau puder ser movida para a base atual, mova-a.
            MoverCartaParaBase(mesa, colunaTableau, naipeBase);
            return;
        }
    }
}
void MoverCartaParaBase(MesaCartas *mesa, int colunaTableau, int naipeBase) {
    Carta* cartaTableau = CartaNoTopo(mesa->tableau[colunaTableau]);
    if (TamanhoDaLista(mesa->tableau[colunaTableau]) > 1) {
        Carta* cartaAbaixo = CartaNaPosicao(mesa->tableau[colunaTableau], 1); // Obtém a carta abaixo da carta no topo.
        cartaAbaixo->posicao = CIMA; // Vire a próxima carta para cima.
        mesa->pontuacao += 5; // Incrementa a pontuação em 5.
    }
    AdicionarCartaAoTopo(mesa->bases[naipeBase], cartaTableau);
    RetirarCartaDoTopo(mesa->tableau[colunaTableau]);
     // Vira a próxima carta para cima.
    mesa->pontuacao += 10;// Incrementa a pontuação em 5.
}
void BaseTableau(MesaCartas* mesa, int indiceBase, int colunaTableau) {
    Carta* cartaBase = CartaNoTopo(mesa->bases[indiceBase]);
    if (cartaBase != NULL) {
        Carta* cartaTableau = CartaNoTopo(mesa->tableau[colunaTableau]);        
        if (cartaTableau == NULL) {
            // Se a coluna de tableau estiver vazia, só é permitido colocar um rei.
            if (cartaBase->valor == K) {
                AdicionarCartaAoTopo(mesa->tableau[colunaTableau], cartaBase);
                RetirarCartaDoTopo(mesa->bases[indiceBase]);
                mesa->pontuacao -= 15; // Deduz 15 pontos da pontuação da mesa
            }
        } else {
            // Verifique se a carta da base pode ser movida para o tableau.
            if (cartaBase->valor == cartaTableau->valor - 1 &&
                cartaBase->naipe % 2 != cartaTableau->naipe % 2) {
                AdicionarCartaAoTopo(mesa->tableau[colunaTableau], cartaBase);
                RetirarCartaDoTopo(mesa->bases[indiceBase]);
                mesa->pontuacao -= 15; // Deduz 15 pontos da pontuação da mesa
                if(mesa->pontuacao<0){
                    mesa->pontuacao=0;
                }
            }
        }
    }
}
void ColunasTableau(MesaCartas* mesa, int quantidade, int colunaOrigem, int colunaDestino) {
    if (mesa == NULL || quantidade <= 0 || colunaOrigem < 0 || colunaOrigem >= 7 || colunaDestino < 0 || colunaDestino >= 7) {
        printf("Erro: Argumentos inválidos.\n");
        return;
    }
    ListaDeCartas* origem = mesa->tableau[colunaOrigem];
    ListaDeCartas* destino = mesa->tableau[colunaDestino];

    if (quantidade >= 1) {
        // Verifique se as cartas podem ser movidas para a coluna de destino
        Carta* cartaTopoDestino = CartaNoTopo(destino);
        
        // Verificar se a última carta virada para cima na coluna de origem é um Rei
        Carta* ultimaCartaViradaCima = NULL;
        int i;
        for (i = TamanhoDaLista(origem) - 1; i >= 0; i--) {
            Carta* carta = CartaNaPosicao(origem, i);
            if (carta->posicao == CIMA) {
                ultimaCartaViradaCima = carta;
                break;
            }
        }
        
        if ((cartaTopoDestino == NULL && ultimaCartaViradaCima != NULL && ultimaCartaViradaCima->valor == K) ||
            (cartaTopoDestino != NULL && Verificasequenciaalt(cartaTopoDestino, ultimaCartaViradaCima))) {

        

            // Adicione mensagens de depuração para mostrar a condição de movimentação satisfeita.
            printf("Condição de movimentação satisfeita.\n");

            // Transferir 'quantidade' cartas de origem para destino em ordem decrescente
            ListaDeCartas* listaTemporaria = CriarListaVazia();

            for (int i = quantidade - 1; i >= 0; i--) {
                Carta* carta = CartaNoTopo(origem);
                RetirarCartaDoTopo(origem);
                carta->posicao = CIMA;
                AdicionarCartaAoTopo(listaTemporaria, carta);
            }

            while (!EstaVazia(listaTemporaria)) {
                Carta* carta = CartaNoTopo(listaTemporaria);
                RetirarCartaDoTopo(listaTemporaria);
                AdicionarCartaAoTopo(destino, carta);
                
            }
            LimparListaDeCartas(listaTemporaria);
            // Atualize a posição da próxima carta da coluna de origem (se ainda houver alguma carta)
            if (!EstaVazia(origem)) {
                Carta* proximaCarta = CartaNoTopo(origem);
                proximaCarta->posicao = CIMA;
            }

            // Atualize a pontuação da mesa após a movimentação
            mesa->pontuacao += 5;

            // Adicione mensagens de depuração para mostrar o resultado da movimentação.
            printf("Movido %d carta(s) de %d para %d\n", quantidade, colunaOrigem, colunaDestino);
        }
    }
}

int ModoInterativo() {
    MesaCartas mesa;
    Inicializar(&mesa);
    CarregarBaralho(&mesa);
    Preparar(&mesa);
    
    
    bool vitoria = false;
    int coluna=0,base=0,origem=0,destino=0,qtd=0;
    char opcao[3];
        
    while (!vitoria) {
        Exibir(&mesa);
        printf("Opcoes:\n");
        printf("1 - Comprar Carta: CC\n");
        printf("2 - Descarte Base: DB\n");
        printf("3 - Descarte Tableau: DT\n");
        printf("4 - Mover Carta do Tableau para Base:TB\n ");
        printf("5 - Mover Carta da Base para Tableau: BT\n");
        printf("6 - Mover Carta entre Colunas do Tableau: TT\n");
        printf("7 - Reciclar Baralho: RB\n");
        printf("0 - Encerrar o Jogo: SA\n");
        printf("Escolha uma opcao: ");
        scanf("%2s", opcao);
        
        if(strcmp(opcao, "CC")==0){
            ComprarCarta(&mesa);
        }
        else if(strcmp(opcao, "DB")==0){
            DescarteBase(&mesa);
                
        }             
        else if(strcmp(opcao, "DT")==0) {       
                printf("Coluna Tableau:");
                scanf("%d",&coluna);
                DescarteTableau(&mesa,coluna);
        }

        else if(strcmp(opcao, "TB")==0)  {  
                printf("Coluna Tableau:");
                scanf("%d",&coluna);
                TableauBase(&mesa,coluna);
        }
        else if(strcmp(opcao, "BT")==0)  {
                printf("Indice da base:");
                scanf("%d",&base);
                printf("Coluna Tableau:");
                scanf("%d",&coluna);
                BaseTableau(&mesa,base,coluna);
        }
        else if(strcmp(opcao, "TT")==0) {
                printf("Quantidade de cartas:");
                scanf("%d",&qtd);
                printf("Coluna Origem:");
                scanf("%d",&origem); 
                printf("Coluna destino:");
                scanf("%d",&destino);               
                ColunasTableau(&mesa,qtd,origem,destino);

        }
        else if(strcmp(opcao, "RB")==0){
            
                ReciclarBaralho(&mesa);
        }
        else if(strcmp(opcao, "SA")==0){
                printf("Encerrando o Jogo.\n");
                return 0;
        }
        else{
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
    // Verificar se a condição de vitória foi atingida.
    vitoria = VerificarVitoria(&mesa);
    // Exibir a mesa final após a vitória.
    Exibir(&mesa);        
}
void ModoArquivo(const char* nomeArquivo) {
    MesaCartas mesa;
    FILE* arquivo;
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    int numCartas;
    fscanf(arquivo, "%d", &numCartas);

    // Verifica se o número de cartas está no intervalo válido
    if (numCartas < 28 || numCartas > 52) {
        fclose(arquivo);
        printf("Valor ultrapassado");
        return;
    }
    Inicializar(&mesa);
    // Cria a estrutura de mesa de cartas
    // Inicializa as listas de cartas na mesa (baralho, descarte, bases e tableau) como necessário
    // Criação dos vetores auxiliares
    Carta* auxiliar1[numCartas];
    Carta* auxiliar2[52];

    for (int i = 0; i < numCartas; i++) {
        int valor;
        char naipe;
        // Corrigir o formato de leitura da carta
        if (fscanf(arquivo, " (%d %c)", &valor, &naipe) != 2) {
            printf("%d %c",valor,naipe);
            printf("Erro ao ler carta %d\n", i);
            fclose(arquivo);
            return;
        }
        // Converte os valores lidos para os tipos do seu programa
        Tiponaipe tipoNaipe;
        Tipovalor tipoValor;
        Tipoposicao tipoPosicao;
        printf("%c", tipoNaipe);
        switch (naipe) {
            case 'C':
                tipoNaipe = COPAS;
                break;
            case 'P':
                tipoNaipe = PAUS;
                break;
            case 'O':
                tipoNaipe = OUROS;
                break;
            case 'E':
                tipoNaipe = ESPADAS;
                break;
            default:
                printf("Naipe inválido\n");
                fclose(arquivo);
                return;
        }
        tipoValor = (Tipovalor)(valor - 1); // Subtrai 1 para ajustar o valor
        printf("%c", tipoNaipe);
        Inicializa(auxiliar1[i], tipoNaipe, tipoValor, BAIXO);
        
    }

    for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13; j++) {
        Carta* auxiliar3 = (Carta*)malloc(sizeof(Carta)); // Aloca memória para uma Carta
        Inicializa(auxiliar3, i, j + 1, 0); // Adicione +1 para ajustar o valor
        auxiliar2[i * 13 + j] = auxiliar3; // Armazena o endereço da Carta no vetor
    }
}
    ListaDeCartas* lista2=CriarListaVazia();

    // Preencha a lista2 com base na correspondência entre auxiliar1 e auxiliar2
    for (int i = 0; i < numCartas; i++) {
        for (int j = 0; j < 52; j++) {
            if (auxiliar1[i]->valor == auxiliar2[j]-> valor && auxiliar1[i]->naipe == auxiliar2[j]-> naipe) {
                AdicionarCartaAoTopo(lista2, auxiliar2[j]);
                auxiliar2[j]->valor = -1;
            }
        }
    }

    int numcartasvalidas = 0;//esta verificando quantas cartas diferentes de -1 estão sendo encontradas 
    for (int i = 0; i < 52; i++) {//quando encontradas , são armazenadas dentro do auxiliar 2
        if (auxiliar2[i]->valor != -1) {
            auxiliar2[numcartasvalidas] = auxiliar2[i];
            numcartasvalidas++;//e o contador aumenta 
        }
    }

    for (int i = 0; i < numcartasvalidas; i++) {
        Carta novaCarta;
    // Crie uma nova carta usando os valores do vetor auxiliar2
        Inicializa(&novaCarta,auxiliar1[i]->naipe, auxiliar2[i]->valor,BAIXO);
    
    // Adicione a nova carta ao topo do baralho
        AdicionarCartaAoTopo(mesa.baralho, &novaCarta);
    }
    

    CarregarBaralhoAleatorio(&mesa);

    // Preparar a mesa
    Preparar(&mesa);
    Exibir(&mesa);
    bool vitoria = false;
    while (!feof(arquivo)) {
         while (!vitoria){
        char opcao[3]; // Aumentar o tamanho para acomodar a string "CC"
        fscanf(arquivo, "%s", opcao); // Correção: Corrigir o formato de leitura da opção

        if (strcmp(opcao, "CC") == 0) {
            ComprarCarta(&mesa);
        } else if (strcmp(opcao, "DB") == 0) {
            DescarteBase(&mesa);
        } else if (strcmp(opcao, "DT") == 0) {
            int indicador=0;
            fscanf(arquivo, "%d", &indicador);
            DescarteTableau(&mesa, indicador);
        } else if (strcmp(opcao, "TB") == 0) {
            int indicador=0;
            fscanf(arquivo, "%d", &indicador);
            TableauBase(&mesa, indicador);
        } else if (strcmp(opcao, "BT") == 0) {
            int indicador1=0, indicador2=0;
            fscanf(arquivo, "%d %d", &indicador1, &indicador2);
            BaseTableau(&mesa, indicador1, indicador2);
        } else if (strcmp(opcao, "TT") == 0) {
            int indicador1=0, indicador2=0, qtd=0;
            fscanf(arquivo, "%d %d %d", &indicador1, &indicador2, &qtd);
            ColunasTableau(&mesa, qtd, indicador1, indicador2);
        } else if (strcmp(opcao, "RB") == 0) {
            ReciclarBaralho(&mesa);
        } 
        else if (strcmp(opcao, "SA") == 0) {
            printf("Encerrando o Jogo.\n");
            return;
        } else {
            printf("Opcao invalida.\n");
        }
        }
    }
    vitoria = VerificarVitoria(&mesa);
    fclose(arquivo);
}

void ReciclarBaralho(MesaCartas* mesa) {
    // Verifique se todas as cartas no descarte estão viradas para cima.
    bool todasViradasParaCima = true;
    ListaDeCartas* descarte = mesa->descarte;
    while (!EstaVazia(descarte)) {
        Carta* carta = CartaNoTopo(descarte);
        if (carta->posicao != CIMA) {
            todasViradasParaCima = false;
            break;
        }
        AdicionarCartaAoTopo(mesa->baralho, carta);
        RetirarCartaDoTopo(descarte);
        if (mesa->pontuacao>=50){
            mesa->pontuacao-=50;
        }
        else if(mesa->pontuacao<=0){
            mesa->pontuacao=0;//0
        }
    }
}
#endif