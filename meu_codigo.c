#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TAM 10  // Tamanho do tabuleiro

// Função para preencher o tabuleiro com '-'
void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = '-';
}

// Função para exibir o tabuleiro
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

// Função para ler coordenadas digitadas
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
            printf("Entrada inválida! Use o formato correto: número espaço número (ex: 3 5).\n");
            continue;
        }

        if (*linha < 0 || *linha >= TAM || *coluna < 0 || *coluna >= TAM) {
            printf("Posição fora dos limites! Tente novamente.\n");
            continue;
        }

        return 1;
    }
}

// Função para posicionar 5 navios
void posicionarNavios(char tabuleiro[TAM][TAM], int jogador) {
    int linha, coluna;
    int navios = 0;

    printf("\nJogador %d - Posicione seus navios (Letra 'N')\n", jogador);

    while (navios < 5) {
        printf("Navio %d - ", navios + 1);
        lerCoordenadas(&linha, &coluna);

        if (tabuleiro[linha][coluna] == 'N') {
            printf("Você já possui navio nesta posição!\n");
            continue;
        }

        tabuleiro[linha][coluna] = 'N';
        printf("NAVIO COLOCADO EM [%d][%d]\n", linha, coluna);
        navios++;
    }

    printf("\nTodos os navios do jogador %d foram posicionados!\n", jogador);
}

// Função para realizar ataque no tabuleiro do oponente
int realizarAtaque(char tabuleiro[TAM][TAM], int jogador) {
    int linha, coluna;

    printf("\nJogador %d - Escolha onde atacar!\n", jogador);

    while (1) {
        lerCoordenadas(&linha, &coluna);

        if (tabuleiro[linha][coluna] == 'X' || tabuleiro[linha][coluna] == 'O') {
            printf("Você já atacou essa posição! Tente outra.\n");
            continue;
        }

        if (tabuleiro[linha][coluna] == 'N') {
            tabuleiro[linha][coluna] = 'O';
            printf("VOCÊ ACERTOU UM NAVIO!\n");
            return 1;
        } else {
            tabuleiro[linha][coluna] = 'X';
            printf("VOCÊ ERROU O ATAQUE!\n");
            return 0;
        }
    }
}

// Função para verificar se ainda existem navios não atingidos
int verificarVitoria(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tabuleiro[i][j] == 'N')
                return 0;
    return 1;
}

// Função principal de controle do jogo
int executarJogo(char tabuleiro1[TAM][TAM], char tabuleiro2[TAM][TAM]) {
    int jogadorAtual = 1;
    int acabou = 0;

    while (!acabou) {
        printf("\n--- TURNO DO JOGADOR %d ---\n", jogadorAtual);

        if (jogadorAtual == 1) {
            mostrarTabuleiro(tabuleiro2, 1);
            realizarAtaque(tabuleiro2, jogadorAtual);
            if (verificarVitoria(tabuleiro2)) {
                printf("\nPARABÉNS JOGADOR 1, VOCÊ VENCEU!\n");
                acabou = 1;
                return 1;
            } else {
                jogadorAtual = 2;
            }
        } else {
            mostrarTabuleiro(tabuleiro1, 1);
            realizarAtaque(tabuleiro1, jogadorAtual);
            if (verificarVitoria(tabuleiro1)) {
                printf("\nPARABÉNS JOGADOR 2, VOCÊ VENCEU!\n");
                acabou = 1;
                return 2;
            } else {
                jogadorAtual = 1;
            }
        }

        printf("Pressione ENTER para o próximo jogador...");
        while (getchar() != '\n');
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    return 0; // Segurança, nunca chega aqui
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
                printf("Opção inválida! Digite apenas 's' para sim ou 'n' para não.\n");
            }
        } while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N');

    } while (resposta == 's' || resposta == 'S');

    printf("Obrigado por jogar Batalha Naval!\n");
    return 0;
}




