#include <stdio.h>

// _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
// BATALHA NAVAL - NIVEL NOVATO
//
// Objetivo: Posicionar 2 navios (1 horizontal, 1 vertical) no tabuleiro
// Tabuleiro: matriz 10x10
// Navios: tamanho fixo de 3 posicoes cada
// Representacao: 0 = agua, 3 = navio
// _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 1. DECLARACAO E INICIALIZACAO DO TABULEIRO
    // Matriz 10x10 inicializada com 0 (agua)
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializar todo o tabuleiro com agua (0)
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            tabuleiro[linha][coluna] = AGUA;
        }
    }
    
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 2. DECLARACAO DOS VETORES REPRESENTANDO OS NAVIOS
    // Cada navio tem tamanho 3 e e representado pelo valor 3
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    
    int navioHorizontal[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};
    
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 3. POSICIONAMENTO DO NAVIO HORIZONTAL
    // Coordenada inicial: linha 2, coluna 1
    // Ocupa as posicoes: (2,1), (2,2), (2,3)
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    
    int linhaH = 2;    // linha inicial do navio horizontal
    int colunaH = 1;   // coluna inicial do navio horizontal
    
    // Validacao: verificar se o navio horizontal cabe no tabuleiro
    if (colunaH + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Copiar os valores do vetor navioHorizontal para o tabuleiro
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
        }
        printf("Navio horizontal posicionado com sucesso na linha %d, colunas %d-%d\n",
               linhaH, colunaH, colunaH + TAMANHO_NAVIO - 1);
    } else {
        printf("ERRO: Navio horizontal nao cabe no tabuleiro!\n");
    }
    
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 4. POSICIONAMENTO DO NAVIO VERTICAL
    // Coordenada inicial: linha 5, coluna 7
    // Ocupa as posicoes: (5,7), (6,7), (7,7)
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    
    int linhaV = 5;    // linha inicial do navio vertical
    int colunaV = 7;   // coluna inicial do navio vertical
    
    // Validacao: verificar se o navio vertical cabe no tabuleiro
    if (linhaV + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Verificar se nao ha sobreposicao com navio horizontal
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaV + i][colunaV] != AGUA) {
                sobreposicao = 1;
                break;
            }
        }
        
        if (!sobreposicao) {
            // Copiar os valores do vetor navioVertical para o tabuleiro
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = navioVertical[i];
            }
            printf("Navio vertical posicionado com sucesso na coluna %d, linhas %d-%d\n",
                   colunaV, linhaV, linhaV + TAMANHO_NAVIO - 1);
        } else {
            printf("ERRO: Navio vertical se sobrepoe a outro navio!\n");
        }
    } else {
        printf("ERRO: Navio vertical nao cabe no tabuleiro!\n");
    }
    
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    // 5. EXIBICAO DO TABULEIRO
    // Loop aninhado para imprimir a matriz completa
    // 0 = agua, 3 = partes do navio
    // _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
    
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");
    
    // Cabecalho com numeros das colunas
    printf("   ");  // espacamento para alinhamento
    for (int col = 0; col < TAMANHO_TABULEIRO; col++) {
        printf("%d ", col);
    }
    printf("\n");
    
    // Imprimir cada linha do tabuleiro com numero da linha
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        printf("%d  ", linha);  // numero da linha
        
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");  // quebra de linha apos cada linha completa
    }
    
    printf("\nLegenda: 0 = Agua | 3 = Navio\n");
    
    return 0;
}
