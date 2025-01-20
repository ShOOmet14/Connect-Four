#include <vector>
#include "gameplay.h"
#include "AI.h"

/*Funkcja ta liczy, ile sumboli jest połączonych na jednej linii na planszy w danym kierunku
board - aktualny stan planszy, row/col - początkowa pozycja od której sprawdzamy, dRow/dCol - kierunek, w którym sprawdzamy
(pionowo/poziomo/na ukos), symbol - symbol gracza*/
int countConnected(const std::vector<std::vector<char>>& board, size_t row, size_t col, int dRow, int dCol, char symbol) {
    int count = 0;
    size_t n = board.size();
    while (row < n && col < n && board[row][col] == symbol) {
        count++;
        row += dRow;
        col += dCol;
    }
    return count;
}

/*Ocena aktualnego stanu planszy, aby określić, kto ma przewagę: AI czy gracz.
board - aktualny stan planszy, aiSymbol - symbol AI, playerSymbol - symbol gracza*/
int evaluateBoard(const std::vector<std::vector<char>>& board, char aiSymbol, char playerSymbol) {
    int score = 0;
    size_t n = board.size();

    for (size_t row = 0; row < n; ++row) {
        for (size_t col = 0; col < n; ++col) {
            if (board[row][col] == aiSymbol) {
                score += countConnected(board, row, col, 0, 1, aiSymbol); // Poziomo
                score += countConnected(board, row, col, 1, 0, aiSymbol); // Pionowo
                score += countConnected(board, row, col, 1, 1, aiSymbol); // Ukośnie od lewej strony
                score += countConnected(board, row, col, 1, -1, aiSymbol); // Ukośnie od prawej strony
            }
            else if (board[row][col] == playerSymbol) {
                score -= countConnected(board, row, col, 0, 1, playerSymbol);
                score -= countConnected(board, row, col, 1, 0, playerSymbol);
                score -= countConnected(board, row, col, 1, 1, playerSymbol);
                score -= countConnected(board, row, col, 1, -1, playerSymbol);
            }
        }
    }
    return score;
}

/*Implementuje algorytm minimax z cięciami alfa-beta, który jest podstawą AI.
board - aktualny stan planszy, depth - maksymalna głębokość przeszukiwania, isMaximizing - czy obecnie optymalizujemy
wynik dla AI,czy minimalizujemy winik gracza, aiSymbol/playerSymbol - symbole AI i gracza, alpha/beta - wartości dla cięć alfa-beta,
które redukują liczbę stanów do analizy*/
int minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizing, char aiSymbol, char playerSymbol, int alpha, int beta) {
    if (depth == 0 || checkWin(board, aiSymbol) || checkWin(board, playerSymbol)) {
        return evaluateBoard(board, aiSymbol, playerSymbol);
    }

    if (isMaximizing) {
        int maxEval = INT_MIN;
        for (size_t col = 0; col < board[0].size(); ++col) {
            // Sprawdź, czy można wykonać ruch w tej kolumnie
            if (board[0][col] == ' ') {
                // Symuluj ruch AI
                for (int row = (int)board.size() - 1; row >= 0; --row) {
                    if (board[row][col] == ' ') {
                        board[row][col] = aiSymbol;
                        int eval = minimax(board, depth - 1, false, aiSymbol, playerSymbol, alpha, beta);
                        board[row][col] = ' ';
                        maxEval = std::max(maxEval, eval);
                        alpha = std::max(alpha, eval);
                        if (beta <= alpha) {
                            break;
                        }
                        break;
                    }
                }
            }
        }
        return maxEval;
    }
    else {
        int minEval = INT_MAX;
        for (size_t col = 0; col < board[0].size(); ++col) {
            if (board[0][col] == ' ') {
                for (int row = (int)board.size() - 1; row >= 0; --row) {
                    if (board[row][col] == ' ') {
                        board[row][col] = playerSymbol;
                        int eval = minimax(board, depth - 1, true, aiSymbol, playerSymbol, alpha, beta);
                        board[row][col] = ' ';
                        minEval = std::min(minEval, eval);
                        beta = std::min(beta, eval);
                        if (beta <= alpha) {
                            break;
                        }
                        break;
                    }
                }
            }
        }
        return minEval;
    }
}

/*Funckja ta polega na wybraniu najlepszego możliwego ruchu dla AI.
board - aktualny stan planszy, aiSymbol - symbol AI, depth - głębokość przeszukiwania (im głębsza, tym lepsza decyzja ai)*/
size_t getAIMove(std::vector<std::vector<char>>& board, char aiSymbol, int depth) {
    int bestScore = INT_MIN;
    size_t bestMove = 0;

    for (size_t col = 0; col < board[0].size(); ++col) {
        if (board[0][col] == ' ') {
            for (int row = (int)board.size() - 1; row >= 0; --row) {
                if (board[row][col] == ' ') {
                    board[row][col] = aiSymbol;
                    int score = minimax(board, depth - 1, false, aiSymbol, 'X', INT_MIN, INT_MAX);
                    board[row][col] = ' ';

                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = col;
                    }
                    break;
                }
            }
        }
    }
    return bestMove;
}