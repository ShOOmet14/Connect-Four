// AI.cpp - Optymalizacja AI dla gry Connect Four
#include "AI.h"
#include <algorithm>
#include <climits>

/*Funkcja pomocnicza: policz ciąg symboli w danym kierunku
Parametry
Co ma zwracaj*/
int CountConnected(const std::vector<std::vector<char>>& board, size_t row, size_t col, int dRow, int dCol, char symbol) {
    int count = 0;
    size_t n = board.size();
    while (row < n && col < n && board[row][col] == symbol) {
        count++;
        row += dRow;
        col += dCol;
    }
    return count;
}

// Funkcja do oceny stanu planszy
int evaluateBoard(const std::vector<std::vector<char>>& board, char aiSymbol, char playerSymbol) {
    int score = 0;
    size_t n = board.size();

    for (size_t row = 0; row < n; ++row) {
        for (size_t col = 0; col < n; ++col) {
            if (board[row][col] == aiSymbol) {
                score += CountConnected(board, row, col, 0, 1, aiSymbol); // Poziomo
                score += CountConnected(board, row, col, 1, 0, aiSymbol); // Pionowo
                score += CountConnected(board, row, col, 1, 1, aiSymbol); // Ukośnie \ 
                score += CountConnected(board, row, col, 1, -1, aiSymbol); // Ukośnie //
            }
            else if (board[row][col] == playerSymbol) {
                score -= CountConnected(board, row, col, 0, 1, playerSymbol);
                score -= CountConnected(board, row, col, 1, 0, playerSymbol);
                score -= CountConnected(board, row, col, 1, 1, playerSymbol);
                score -= CountConnected(board, row, col, 1, -1, playerSymbol);
            }
        }
    }

    return score;
}

// Funkcja minimax z cięciami alfa-beta
int minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizing, char aiSymbol, char playerSymbol, int alpha, int beta) {
    if (depth == 0 || CheckWin(board, aiSymbol) || CheckWin(board, playerSymbol)) {
        return evaluateBoard(board, aiSymbol, playerSymbol);
    }

    if (isMaximizing) {
        int maxEval = INT_MIN;
        for (size_t col = 0; col < board[0].size(); ++col) {
            // Sprawdź, czy można wykonać ruch w tej kolumnie
            if (board[0][col] == ' ') {
                // Symuluj ruch AI
                for (int row = board.size() - 1; row >= 0; --row) {
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
                for (int row = board.size() - 1; row >= 0; --row) {
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

// Funkcja główna: Wybierz najlepszy ruch AI
size_t GetAIMove(std::vector<std::vector<char>>& board, char aiSymbol, int depth) {
    int bestScore = INT_MIN;
    size_t bestMove = 0;

    for (size_t col = 0; col < board[0].size(); ++col) {
        if (board[0][col] == ' ') {
            for (int row = board.size() - 1; row >= 0; --row) {
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