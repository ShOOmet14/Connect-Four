#pragma once
#include "gameplay.h"

int CountConnected(const std::vector<std::vector<char>>& board, size_t row, size_t col, int dRow, int dCol, char symbol);

int evaluateBoard(const std::vector<std::vector<char>>& board, char aiSymbol, char playerSymbol);

size_t GetAIMove(std::vector<std::vector<char>>& board, char aiSymbol, int depth);

int minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizing, char aiSymbol, char playerSymbol, int alpha, int beta);
