#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include "translations.h"
#include "settings.h"
#include "console.h"
#include "AI.h"
#include "gameplay.h"

bool playing = true;
int currentStartingPlayer = 1;
int player1Score = 0;
int player2Score = 0;

/*Funkcja ta rozpoczyna rozgrywkę, można grać na innego gracza albo AI.
rememberMode - jeżeli prawidziwa, to gra używa poprzedniego trybu (hot seat / vs AI)
previousAgainstAI - określa czy ostatnia gra była przeciwko AI*/
void play(bool rememberMode, bool previousAgainstAI) {
    bool againstAI = false; //Do zapamiętywania trybu gry
    if (!rememberMode) {
        std::vector<std::string> playModeMenu = {
            T("Hot Seat (Player vs Player)"),
            T("Play Against AI")
        };

        size_t modeChoice = navigateMenu(playModeMenu, true, T("Select Game Mode"), T("Use arrows to navigate.\nPress Enter to select."));

        if (modeChoice == -1) { //Jeżeli wciśnięty jest Esc, powrót do menu głównego
            return;
        }

        againstAI = (modeChoice == 1); //Sprawdź, czy gracz wybrał tryb vs AI
    }
    else {
        againstAI = previousAgainstAI; //Zapamiętywanie wybranego trybu
    }

    std::vector<std::vector<char>> board(boardSize, std::vector<char>(boardSize, ' '));

    int currentPlayer = currentStartingPlayer;
    char playerSymbols[2] = { player1Symbol, player2Symbol };
    size_t selectedColumn = 0;

    while (true) {
        //Tworzenie nagłówka, wyświetlanego nad planszą
        std::string header = T("Player") + " " + std::to_string(currentPlayer) + " (" + playerSymbols[currentPlayer - 1] + ") - ";
        header += (againstAI && currentPlayer == 2) ? T("AI is thinking...") : T("Select a column");

        consoleClear();

        //Wyświetlanie planszy z nagłówkiem
        std::cout << header << "\n\n";
        for (size_t row = 0; row < boardSize; row++) {
            for (size_t col = 0; col < boardSize; col++) {
                std::cout << "| " << board[row][col] << " ";
            }
            std::cout << "|\n";
            for (size_t col = 0; col < boardSize; col++) {
                std::cout << "----";
            }
            std::cout << "\n";
        }

        //Wyświetlanie numerów kolumn
        for (size_t col = 0; col < board[0].size(); col++) {
            if (col + 1 >= 10) {
                std::cout << " " << col + 1 << " "; //Kolumny >= 10
            }
            else {
                std::cout << "  " << col + 1 << " "; //Kolumny < 10
            }
        }
        std::cout << "\n";

        if (againstAI && currentPlayer == 2) {
            //Tura AI
            selectedColumn = getAIMove(board, playerSymbols[1], aiDifficulty); //Głębokość myślenia AI w zależności od poziomu trudności
        }
        else {
            //Tura gracza
            selectedColumn = navigateColumn(board, selectedColumn, header);
        }

        //Wstaw symbol w kolumnie
        for (int row = boardSize - 1; row >= 0; row--) {
            if (board[row][selectedColumn] == ' ') {
                board[row][selectedColumn] = playerSymbols[currentPlayer - 1];
                break;
            }
        }

        //Sprawdź wygraną i remis
        if (checkWin(board, playerSymbols[currentPlayer - 1])) {
            consoleClear();
            // Display final board
            for (size_t row = 0; row < boardSize; row++) {
                for (size_t col = 0; col < boardSize; col++) {
                    std::cout << "| " << board[row][col] << " ";
                }
                std::cout << "|\n";
                for (size_t col = 0; col < boardSize; col++) {
                    std::cout << "----";
                }
                std::cout << "\n";
            }

            std::cout << T("Player") << " " << currentPlayer << " (" << playerSymbols[currentPlayer - 1] << ") " << T("wins!") << "\n";

            if (currentPlayer == 1) {
                player1Score++;
            }
            else {
                player2Score++;
            }
            break;
        }

        bool full = true;
        for (size_t i = 0; i < boardSize; i++) {
            if (board[0][i] == ' ') {
                full = false;
                break;
            }
        }
        if (full) {
            consoleClear();
            std::cout << T("Draw! The board is full.") << "\n";
            break;
        }

        //Zamienianie graczy
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    currentStartingPlayer = (currentStartingPlayer == 1) ? 2 : 1;
    std::swap(playerSymbols[0], playerSymbols[1]);

    std::ostringstream headerStream;
    headerStream << T("Player Scores:") << "\n";
    headerStream << T("Player 1") << " (" << player1Symbol << "): " << player1Score << " " << T("points") << "\n";
    headerStream << T("Player 2") << " (" << player2Symbol << "): " << player2Score << " " << T("points") << "\n";
    std::string header = headerStream.str();

    //Menu końca gry
    std::vector<std::string> endGameMenu = {
        T("Play Again"),
        T("Return to Main Menu")
    };

    size_t choice = navigateMenu(endGameMenu, true, header, T("Select one of the above options by pressing Enter."));

    if (choice == 0) {
        //Zagraj ponownie na tym samym trybie
        play(true, againstAI);
        return;
    }
    else if (choice == 1 || choice == -1) {
        return; //Powrót do menu głównego
    }
}

//Funkcja, która sprawdza czy dany symbol ułożył ciąg wystarczającej długości w pionie, poziomie i na ukos, aby wygrać
bool checkWin(const std::vector<std::vector<char>>& board, char symbol) {
    int n = board.size();
    std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {1, 1}, {1, -1} };

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            for (const auto& [dRow, dCol] : directions) {
                bool win = true;
                for (int k = 0; k < checkSize; k++) {
                    int newRow = row + k * dRow;
                    int newCol = col + k * dCol;
                    if (newRow >= n || newCol >= n || newCol < 0 || board[newRow][newCol] != symbol) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;
            }
        }
    }
    return false;
}

/*Funckja, która umożliwia użytkownikowi nawigowanie między kolumnami planszy przy użyciu strzałek.
board - aktualny stan planszy, selectedColumn - wybrana/podświetlona kolumna, header - nagłówek wyświetlany nad planszą*/
int navigateColumn(std::vector<std::vector<char>>& board, size_t& selectedColumn, const std::string& header) {
    char key;

    while (true) {
        consoleClear();

        //Wyświetlanie nagłówka
        if (!header.empty()) {
            std::cout << header << "\n\n";
        }

        //Wyświetlanie planszy
        for (size_t row = 0; row < boardSize; row++) {
            for (size_t col = 0; col < boardSize; col++) {
                std::cout << "| "; // Separator i spacja w domyślnym kolorze

                // Ustaw kolor w zależności od symbolu
                if (board[row][col] == player1Symbol) {
                    setConsoleColor(10); // Jasny zielony dla gracza 1
                }
                else if (board[row][col] == player2Symbol) {
                    setConsoleColor(14); // Jasny żółty dla gracza 2
                }
                else {
                    setConsoleColor(7); // Domyślny kolor dla pustych miejsc
                }

                // Wyświetlanie symbolu
                std::cout << board[row][col];

                // Przywrócenie domyślnego koloru
                setConsoleColor(7);

                std::cout << " "; // Spacja po symbolu w domyślnym kolorze
            }
            std::cout << "|\n"; // Separator na końcu wiersza w domyślnym kolorze

            // Rysowanie linii oddzielających
            for (size_t col = 0; col < boardSize; col++) {
                std::cout << "----";
            }
            std::cout << "\n";
        }

        //Wyświetlanie numerów kolumn
        for (size_t col = 0; col < board[0].size(); col++) {
            if (col == selectedColumn) {
                if (col + 1 >= 10) {
                    std::cout << " \033[7m" << col + 1 << " \033[0m"; // Kolumny >= 10 na początku
                }
                else {
                    std::cout << " \033[7m " << col + 1 << " \033[0m"; // Kolumny < 10 wyśrodkowane
                }
            }
            else {
                if (col + 1 >= 10) {
                    std::cout << " " << col + 1 << " "; // Kolumny >= 10 na początku
                }
                else {
                    std::cout << "  " << col + 1 << " "; // Kolumny < 10 wyśrodkowane
                }
            }
        }
        std::cout << "\n";

        //Obsługa klawiszy, na różnych systemach operacyjnych
        key = getKey();
        if (key == -32) {
            char arrowKey = getKey();
            if (arrowKey == 75) { //Strzałka w lewo
                selectedColumn = (selectedColumn == 0) ? board[0].size() - 1 : selectedColumn - 1;
            }
            else if (arrowKey == 77) { //Strzałka w prawo
                selectedColumn = (selectedColumn + 1) % board[0].size();
            }
        }
        else if (key == '\r' || key == '\n') {
            if (board[0][selectedColumn] == ' ') {
                return selectedColumn;
            }
            else { //Jeżeli kolumna jest już pełna
                std::cout << T("\nThis column is full\n");
                std::this_thread::sleep_for(std::chrono::milliseconds(700));
            }
        }
    }
}

/*Umożliwia użytkownikowi nawigowanie w między opcjami menu.
menuItems - lista opcji w menu, allowExit - zezwolenie na wyjście z konkretnego menu, header/footer - nagłówek nad menu/stopka pod menu*/
int navigateMenu(const std::vector<std::string>& menuItems, bool allowExit, const std::string& header, const std::string& footer) {
    size_t selectedIndex = 0;
    char key;

    while (true) {
        consoleClear();

        if (!header.empty()) {
            std::cout << header << "\n\n";
        }

        displayMenu(menuItems, selectedIndex);

        if (!footer.empty()) {
            std::cout << "\n" << footer;
        }

        key = getKey();

        if (key == -32) { //Sprawdzanie czy jest kliknięta klawisz specjalny w systemie Windows, w naszym przypadku jest to strzałka
            char arrowKey = getKey();
            if (arrowKey == 72) { //Sprawdzanie czy jest kliknięta strzałka w górę
                selectedIndex = (selectedIndex == 0) ? menuItems.size() - 1 : selectedIndex - 1;
            }
            else if (arrowKey == 80) { //Sprawdzanie czy jest kliknięta strzałka w dół
                selectedIndex = (selectedIndex == menuItems.size() - 1) ? 0 : selectedIndex + 1;
            }
        }
        else if (key == '\r' || key == '\n') { //Sprawdzanie czy kliknięty jest klawisze enter
            return selectedIndex;
        }
        else if (key == 27 && allowExit) { //Sprawdzanie czy kliknięty jest klawisz Esc
            return -1; //Wyjście z menu do poprzedniego
        }
    }
}

/*Funckja ta wyświetla menu na ekranie z podświetleniem aktualnie wybranej opcji.
currentMenuItems - lista opcji w menu, selectedIndex - indeks aktualnie wybranej opcji*/
void displayMenu(const std::vector<std::string>& currentMenuItems, size_t selectedIndex) {
    for (size_t i = 0; i < currentMenuItems.size(); i++) {
        if (i == selectedIndex) {
            std::cout << "\033[7m" << currentMenuItems[i] << "\033[0m\n";
        }
        else {
            std::cout << currentMenuItems[i] << "\n";
        }
    }
}