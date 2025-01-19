#pragma once
#include <vector>

/*Funkcja ta liczy, ile sumboli jest połączonych na jednej linii na planszy w danym kierunku
board - aktualny stan planszy, row/col - początkowa pozycja od której sprawdzamy, dRow/dCol - kierunek, w którym sprawdzamy
(pionowo/poziomo/na ukos), symbol - symbol gracza*/
int countConnected(const std::vector<std::vector<char>>& board, size_t row, size_t col, int dRow, int dCol, char symbol);

/*Ocena aktualnego stanu planszy, aby określić, kto ma przewagę: AI czy gracz.
board - aktualny stan planszy, aiSymbol - symbol AI, playerSymbol - symbol gracza*/
int evaluateBoard(const std::vector<std::vector<char>>& board, char aiSymbol, char playerSymbol);

/*Funckja ta polega na wybraniu najlepszego możliwego ruchu dla AI.
board - aktualny stan planszy, aiSymbol - symbol AI, depth - głębokość przeszukiwania (im głębsza, tym lepsza decyzja ai)*/
size_t getAIMove(std::vector<std::vector<char>>& board, char aiSymbol, int depth);

/*Implementuje algorytm minimax z cięciami alfa-beta, który jest podstawą AI.
board - aktualny stan planszy, depth - maksymalna głębokość przeszukiwania, isMaximizing - czy obecnie optymalizujemy 
wynik dla AI,czy minimalizujemy winik gracza, aiSymbol/playerSymbol - symbole AI i gracza, alpha/beta - wartości dla cięć alfa-beta, 
które redukują liczbę stanów do analizy*/
int minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizing, char aiSymbol, char playerSymbol, int alpha, int beta);