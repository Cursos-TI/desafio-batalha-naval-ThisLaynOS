#include <stdio.h>

// _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
// BATALHA NAVAL - NIVEL MESTRE
//
// Continuacao do Nivel Aventureiro.
// Novidade: 3 habilidades especiais com areas de efeito distintas
//   - Cone:     area que se expande para baixo a partir do ponto de origem
//   - Cruz:     linha horizontal + linha vertical centradas no ponto de origem
//   - Octaedro: formato de losango centrado no ponto de origem
//
// As matrizes de habilidade (5x5) usam: 0 = nao afetado, 1 = afetado
// No tabuleiro: 0 = agua, 3 = navio, 5 = area afetada por habilidade
//
// Obrigatorio: construir as matrizes com condicionais dentro de loops
// _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

#define TAMANHO   10
#define NAVIO_SZ  3
#define HAB_SZ    5    // tamanho das matrizes de habilidade (5x5)
#define AGUA      0
#define NAVIO     3
#define HABILIDADE 5

int main() {

    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 1. TABULEIRO 10x10 inicializado com agua (0)
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

    int tabuleiro[TAMANHO][TAMANHO];

    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            tabuleiro[i][j] = AGUA;

    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 2. VETORES DOS NAVIOS e posicionamento (herdado do aventureiro)
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

    int navioH[NAVIO_SZ]  = {NAVIO, NAVIO, NAVIO}; // horizontal
    int navioV[NAVIO_SZ]  = {NAVIO, NAVIO, NAVIO}; // vertical
    int navioDP[NAVIO_SZ] = {NAVIO, NAVIO, NAVIO}; // diagonal principal
    int navioDS[NAVIO_SZ] = {NAVIO, NAVIO, NAVIO}; // diagonal secundaria

    // Navio horizontal: linha 2, coluna 1 -> (2,1)(2,2)(2,3)
    for (int i = 0; i < NAVIO_SZ; i++)
        tabuleiro[2][1 + i] = navioH[i];

    // Navio vertical: linha 5, coluna 7 -> (5,7)(6,7)(7,7)
    for (int i = 0; i < NAVIO_SZ; i++)
        tabuleiro[5 + i][7] = navioV[i];

    // Navio diagonal principal: (0,0)(1,1)(2,2)
    for (int i = 0; i < NAVIO_SZ; i++)
        tabuleiro[0 + i][0 + i] = navioDP[i];

    // Navio diagonal secundaria: (0,9)(1,8)(2,7)
    for (int i = 0; i < NAVIO_SZ; i++)
        tabuleiro[0 + i][9 - i] = navioDS[i];

    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 3. MATRIZES DE HABILIDADE (5x5) construidas com condicionais em loops
    //
    // Cada matriz usa: 1 = posicao afetada, 0 = posicao nao afetada
    // O centro logico de cada matriz e a posicao [2][2] (indice central de 5x5)
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

    int cone[HAB_SZ][HAB_SZ];
    int cruz[HAB_SZ][HAB_SZ];
    int octaedro[HAB_SZ][HAB_SZ];

    // -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    // CONE: ponto de origem no topo (linha 0, coluna central), expande para baixo
    // A largura do cone aumenta 1 celula para cada lado por linha percorrida
    //
    // Linha 0: apenas coluna central [0][2]         -> 0 0 1 0 0
    // Linha 1: coluna central +/- 1  [1][1..3]      -> 0 1 1 1 0
    // Linha 2: coluna central +/- 2  [2][0..4]      -> 1 1 1 1 1
    // Linhas 3 e 4: fora do alcance do cone          -> 0 0 0 0 0
    //
    // Condicional: j >= (centro - i) && j <= (centro + i) && i <= 2
    // -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    int centro = HAB_SZ / 2; // centro = 2 para matriz 5x5

    for (int i = 0; i < HAB_SZ; i++) {
        for (int j = 0; j < HAB_SZ; j++) {
            // Afetado se a coluna estiver dentro da expansao do cone na linha i
            // e a linha i estiver dentro da altura do cone (ate linha 2)
            if (i <= centro && j >= (centro - i) && j <= (centro + i)) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }

    // -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    // CRUZ: linha horizontal e coluna vertical passando pelo centro [2][2]
    //
    // Afetado se i == centro (linha central) OU j == centro (coluna central)
    // Resultado:
    // 0 0 1 0 0
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0
    // 0 0 1 0 0
    // -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    for (int i = 0; i < HAB_SZ; i++) {
        for (int j = 0; j < HAB_SZ; j++) {
            if (i == centro || j == centro) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }

    // -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    // OCTAEDRO (losango): formato de diamante centrado em [2][2]
    //
    // Afetado se a distancia de Manhattan do centro for <= raio (centro = 2)
    // Distancia de Manhattan: |i - centro| + |j - centro| <= centro
    //
    // Resultado:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    // 0 1 1 1 0
    // 0 0 1 0 0
    // -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    for (int i = 0; i < HAB_SZ; i++) {
        for (int j = 0; j < HAB_SZ; j++) {
            // Calcula distancia de Manhattan entre (i,j) e o centro (2,2)
            int distLinha  = i - centro;
            int distColuna = j - centro;

            // Valor absoluto manual (sem abs() para usar apenas logica condicional)
            if (distLinha  < 0) distLinha  = -distLinha;
            if (distColuna < 0) distColuna = -distColuna;

            if (distLinha + distColuna <= centro) {
                octaedro[i][j] = 1;
            } else {
                octaedro[i][j] = 0;
            }
        }
    }

    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 4. INTEGRACAO DAS HABILIDADES AO TABULEIRO
    //
    // Para cada habilidade, define-se um ponto de origem no tabuleiro.
    // A matriz de habilidade e sobreposta ao tabuleiro centrada nesse ponto.
    // O offset calcula o deslocamento entre o indice da matriz de habilidade
    // e o indice real no tabuleiro: linha_tabuleiro = origemLinha + (i - centro)
    //
    // Posicoes afetadas (valor 1 na matriz de habilidade) sao marcadas com 5
    // no tabuleiro, desde que estejam dentro dos limites (0 a 9).
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

    // Ponto de origem do CONE no tabuleiro: linha 4, coluna 4
    int origemConeL = 4, origemConeC = 4;

    for (int i = 0; i < HAB_SZ; i++) {
        for (int j = 0; j < HAB_SZ; j++) {
            // Converte indice da matriz de habilidade para coordenada do tabuleiro
            int tL = origemConeL + (i - centro); // linha no tabuleiro
            int tC = origemConeC + (j - centro); // coluna no tabuleiro

            // Verifica limites do tabuleiro antes de marcar
            if (tL >= 0 && tL < TAMANHO && tC >= 0 && tC < TAMANHO) {
                if (cone[i][j] == 1) {
                    tabuleiro[tL][tC] = HABILIDADE;
                }
            }
        }
    }

    // Ponto de origem da CRUZ no tabuleiro: linha 7, coluna 3
    int origemCruzL = 7, origemCruzC = 3;

    for (int i = 0; i < HAB_SZ; i++) {
        for (int j = 0; j < HAB_SZ; j++) {
            int tL = origemCruzL + (i - centro);
            int tC = origemCruzC + (j - centro);

            if (tL >= 0 && tL < TAMANHO && tC >= 0 && tC < TAMANHO) {
                if (cruz[i][j] == 1) {
                    tabuleiro[tL][tC] = HABILIDADE;
                }
            }
        }
    }

    // Ponto de origem do OCTAEDRO no tabuleiro: linha 4, coluna 8
    int origemOctL = 4, origemOctC = 8;

    for (int i = 0; i < HAB_SZ; i++) {
        for (int j = 0; j < HAB_SZ; j++) {
            int tL = origemOctL + (i - centro);
            int tC = origemOctC + (j - centro);

            if (tL >= 0 && tL < TAMANHO && tC >= 0 && tC < TAMANHO) {
                if (octaedro[i][j] == 1) {
                    tabuleiro[tL][tC] = HABILIDADE;
                }
            }
        }
    }

    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 5. EXIBICAO DO TABULEIRO FINAL
    // 0 = agua, 3 = navio, 5 = area afetada por habilidade
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

    printf("=== TABULEIRO BATALHA NAVAL - NIVEL MESTRE ===\n\n");

    printf("   ");
    for (int col = 0; col < TAMANHO; col++) printf("%d ", col);
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%d  ", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = Agua | 3 = Navio | 5 = Area de habilidade\n");

    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 6. EXIBICAO DAS MATRIZES DE HABILIDADE ISOLADAS (para debug)
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

    printf("\n--- Matriz CONE (origem tabuleiro: %d,%d) ---\n", origemConeL, origemConeC);
    for (int i = 0; i < HAB_SZ; i++) {
        for (int j = 0; j < HAB_SZ; j++) printf("%d ", cone[i][j]);
        printf("\n");
    }

    printf("\n--- Matriz CRUZ (origem tabuleiro: %d,%d) ---\n", origemCruzL, origemCruzC);
    for (int i = 0; i < HAB_SZ; i++) {
        for (int j = 0; j < HAB_SZ; j++) printf("%d ", cruz[i][j]);
        printf("\n");
    }

    printf("\n--- Matriz OCTAEDRO (origem tabuleiro: %d,%d) ---\n", origemOctL, origemOctC);
    for (int i = 0; i < HAB_SZ; i++) {
        for (int j = 0; j < HAB_SZ; j++) printf("%d ", octaedro[i][j]);
        printf("\n");
    }

    return 0;
}
