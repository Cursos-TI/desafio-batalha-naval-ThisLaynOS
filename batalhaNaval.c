#include <stdio.h>

// _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
// BATALHA NAVAL - NIVEL AVENTUREIRO
//
// Continuacao do Nivel Novato.
// Novidade: posicionamento de 4 navios no total
//   - Navio 1: horizontal  (mantido do novato)
//   - Navio 2: vertical    (mantido do novato)
//   - Navio 3: diagonal principal (linha e coluna aumentam juntos)
//   - Navio 4: diagonal secundaria (linha aumenta, coluna diminui)
//
// Tabuleiro: 10x10  |  Tamanho de cada navio: 3
// Representacao: 0 = agua, 3 = navio
// _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

#define TAMANHO  10
#define NAVIO_SZ 3
#define AGUA     0
#define NAVIO    3

int main() {

    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 1. DECLARACAO E INICIALIZACAO DO TABULEIRO
    // Matriz 10x10 preenchida com 0 (agua)
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

    int tabuleiro[TAMANHO][TAMANHO];

    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 2. VETORES DOS NAVIOS
    // Cada vetor representa um navio com 3 posicoes de valor 3
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

    int navioHorizontal [NAVIO_SZ] = {NAVIO, NAVIO, NAVIO};
    int navioVertical   [NAVIO_SZ] = {NAVIO, NAVIO, NAVIO};
    int navioDiagPrin   [NAVIO_SZ] = {NAVIO, NAVIO, NAVIO}; // diagonal principal
    int navioDiagSec    [NAVIO_SZ] = {NAVIO, NAVIO, NAVIO}; // diagonal secundaria

    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 3. NAVIO HORIZONTAL - linha 2, coluna 1  -> posicoes (2,1)(2,2)(2,3)
    // Loop copia navioHorizontal[i] para tabuleiro[linhaH][colunaH + i]
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

    int linhaH = 2, colunaH = 1;

    if (colunaH + NAVIO_SZ <= TAMANHO) {
        for (int i = 0; i < NAVIO_SZ; i++) {
            tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
        }
        printf("Navio horizontal posicionado: linha %d, colunas %d-%d\n",
               linhaH, colunaH, colunaH + NAVIO_SZ - 1);
    }

    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 4. NAVIO VERTICAL - linha 5, coluna 7  -> posicoes (5,7)(6,7)(7,7)
    // Loop copia navioVertical[i] para tabuleiro[linhaV + i][colunaV]
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

    int linhaV = 5, colunaV = 7;

    if (linhaV + NAVIO_SZ <= TAMANHO) {
        int sobreposto = 0;
        for (int i = 0; i < NAVIO_SZ; i++) {
            if (tabuleiro[linhaV + i][colunaV] != AGUA) { sobreposto = 1; break; }
        }
        if (!sobreposto) {
            for (int i = 0; i < NAVIO_SZ; i++) {
                tabuleiro[linhaV + i][colunaV] = navioVertical[i];
            }
            printf("Navio vertical posicionado: coluna %d, linhas %d-%d\n",
                   colunaV, linhaV, linhaV + NAVIO_SZ - 1);
        }
    }

    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 5. NAVIO DIAGONAL PRINCIPAL - linha 0, coluna 0
    // Linha e coluna aumentam simultaneamente: tabuleiro[linha+i][coluna+i]
    // Posicoes: (0,0), (1,1), (2,2)
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

    int linhaDP = 0, colunaDP = 0;

    if (linhaDP + NAVIO_SZ <= TAMANHO && colunaDP + NAVIO_SZ <= TAMANHO) {
        int sobreposto = 0;
        for (int i = 0; i < NAVIO_SZ; i++) {
            if (tabuleiro[linhaDP + i][colunaDP + i] != AGUA) { sobreposto = 1; break; }
        }
        if (!sobreposto) {
            for (int i = 0; i < NAVIO_SZ; i++) {
                tabuleiro[linhaDP + i][colunaDP + i] = navioDiagPrin[i];
            }
            printf("Navio diagonal principal posicionado: inicio (%d,%d) -> (%d,%d)\n",
                   linhaDP, colunaDP, linhaDP + NAVIO_SZ - 1, colunaDP + NAVIO_SZ - 1);
        }
    }

    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 6. NAVIO DIAGONAL SECUNDARIA - linha 0, coluna 9
    // Linha aumenta, coluna diminui: tabuleiro[linha+i][coluna-i]
    // Posicoes: (0,9), (1,8), (2,7)
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

    int linhaDS = 0, colunaDS = 9;

    if (linhaDS + NAVIO_SZ <= TAMANHO && colunaDS - (NAVIO_SZ - 1) >= 0) {
        int sobreposto = 0;
        for (int i = 0; i < NAVIO_SZ; i++) {
            if (tabuleiro[linhaDS + i][colunaDS - i] != AGUA) { sobreposto = 1; break; }
        }
        if (!sobreposto) {
            for (int i = 0; i < NAVIO_SZ; i++) {
                tabuleiro[linhaDS + i][colunaDS - i] = navioDiagSec[i];
            }
            printf("Navio diagonal secundaria posicionado: inicio (%d,%d) -> (%d,%d)\n",
                   linhaDS, colunaDS, linhaDS + NAVIO_SZ - 1, colunaDS - (NAVIO_SZ - 1));
        }
    }

    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 7. EXIBICAO DO TABULEIRO COMPLETO
    // Loops aninhados percorrem toda a matriz e imprimem cada elemento
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");

    // Cabecalho com indices das colunas
    printf("   ");
    for (int col = 0; col < TAMANHO; col++) {
        printf("%d ", col);
    }
    printf("\n");

    // Linhas do tabuleiro com indice da linha a esquerda
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d  ", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = Agua | 3 = Navio\n");

    return 0;
}
