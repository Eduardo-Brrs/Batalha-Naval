#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TAM 10  // Tamanho do tabuleiro

// Fun��o para preencher o tabuleiro com '-'
void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = '-';
}

// Fun��o para exibir o tabuleiro
void mostrarTabuleiro(char tabuleiro[TAM][TAM], int esconder) {
    printf("   ");
    for (int i = 0; i < TAM; i++)
        printf("%d ", i);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%d  ", i);
        for (int j = 0; j < TAM; j++) {
            if (esconder && tabuleiro[i][j] == 'N')
                printf("- ");
            else
                printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Fun��o para ler coordenadas digitadas
int lerCoordenadas(int *linha, int *coluna) {
    char entrada[100];
    char extra;

    while (1) {
        printf("Digite a linha e a coluna (ex: 3 5): ");
        if (!fgets(entrada, sizeof(entrada), stdin)) {
            printf("Erro na leitura! Tente novamente.\n");
            continue;
        }

        if (sscanf(entrada, "%d %d %c", linha, coluna, &extra) != 2) {
            printf("Entrada inv�lida! Use o formato correto: n�mero espa�o n�mero (ex: 3 5).\n");
            continue;
        }

        if (*linha < 0 || *linha >= TAM || *coluna < 0 || *coluna >= TAM) {
            printf("Posi��o fora dos limites! Tente novamente.\n");
            continue;
        }

        return 1;
    }
}

// Fun��o para posicionar 5 navios
void posicionarNavios(char tabuleiro[TAM][TAM], int jogador) {
    int linha, coluna;
    int navios = 0;

    printf("\nJogador %d - Posicione seus navios (Letra 'N')\n", jogador);

    while (navios < 5) {
        printf("Navio %d - ", navios + 1);
        lerCoordenadas(&linha, &coluna);

        if (tabuleiro[linha][coluna] == 'N') {
            printf("Voc� j� possui navio nesta posi��o!\n");
            continue;
        }

        tabuleiro[linha][coluna] = 'N';
        printf("NAVIO COLOCADO EM [%d][%d]\n", linha, coluna);
        navios++;
    }

    printf("\nTodos os navios do jogador %d foram posicionados!\n", jogador);
}

// Fun��o para realizar ataque no tabuleiro do oponente
int realizarAtaque(char tabuleiro[TAM][TAM], int jogador) {
    int linha, coluna;

    printf("\nJogador %d - Escolha onde atacar!\n", jogador);

    while (1) {
        lerCoordenadas(&linha, &coluna);

        if (tabuleiro[linha][coluna] == 'X' || tabuleiro[linha][coluna] == 'O') {
            printf("Voc� j� atacou essa posi��o! Tente outra.\n");
            continue;
        }

        if (tabuleiro[linha][coluna] == 'N') {
            tabuleiro[linha][coluna] = 'O';
            printf("VOC� ACERTOU UM NAVIO!\n");
            return 1;
        } else {
            tabuleiro[linha][coluna] = 'X';
            printf("VOC� ERROU O ATAQUE!\n");
            return 0;
        }
    }
}

// Fun��o para verificar se ainda existem navios n�o atingidos
int verificarVitoria(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tabuleiro[i][j] == 'N')
                return 0;
    return 1;
}

// Fun��o principal de controle do jogo
int executarJogo(char tabuleiro1[TAM][TAM], char tabuleiro2[TAM][TAM]) {
    int jogadorAtual = 1;
    int acabou = 0;

    while (!acabou) {
        printf("\n--- TURNO DO JOGADOR %d ---\n", jogadorAtual);

        if (jogadorAtual == 1) {
            mostrarTabuleiro(tabuleiro2, 1);
            realizarAtaque(tabuleiro2, jogadorAtual);
            if (verificarVitoria(tabuleiro2)) {
                printf("\nPARAB�NS JOGADOR 1, VOC� VENCEU!\n");
                acabou = 1;
                return 1;
            } else {
                jogadorAtual = 2;
            }
        } else {
            mostrarTabuleiro(tabuleiro1, 1);
            realizarAtaque(tabuleiro1, jogadorAtual);
            if (verificarVitoria(tabuleiro1)) {
                printf("\nPARAB�NS JOGADOR 2, VOC� VENCEU!\n");
                acabou = 1;
                return 2;
            } else {
                jogadorAtual = 1;
            }
        }

        printf("Pressione ENTER para o pr�ximo jogador...");
        while (getchar() != '\n');
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    return 0; // Seguran�a, nunca chega aqui
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    char tabuleiro1[TAM][TAM];
    char tabuleiro2[TAM][TAM];
    char resposta;

    do {
        // Inicializa os tabuleiros
        inicializarTabuleiro(tabuleiro1);
        inicializarTabuleiro(tabuleiro2);

        // Posiciona os navios dos dois jogadores
        posicionarNavios(tabuleiro1, 1);
        printf("Pressione ENTER para continuar...");
        while (getchar() != '\n');
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        posicionarNavios(tabuleiro2, 2);
        printf("Pressione ENTER para continuar...");
        while (getchar() != '\n');
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        // Executa o jogo
        executarJogo(tabuleiro1, tabuleiro2);

        // Pergunta se desejam jogar novamente
        do {
            printf("Desejam jogar novamente? (s/n): ");
            scanf(" %c", &resposta);
            while (getchar() != '\n');

            if (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                printf("Op��o inv�lida! Digite apenas 's' para sim ou 'n' para n�o.\n");
            }
        } while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N');

    } while (resposta == 's' || resposta == 'S');

    printf("Obrigado por jogar Batalha Naval!\n");
    return 0;
}




