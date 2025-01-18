#include "gameplay.h"
#include "translations.h"
#include "settings.h"
#include "console.h"
#include "AI.h"

bool Playing = true;
int currentStartingPlayer = 1;
int Player1Score = 0;
int Player2Score = 0;

void Play(bool rememberMode, bool previousAgainstAI) {
    static bool againstAI = false; // To remember the game mode
    if (!rememberMode) {
        std::vector<std::string> playModeMenu = {
            T("Hot Seat (Player vs Player)"),
            T("Play Against AI")
        };

        size_t modeChoice = NavigateMenu(playModeMenu, true, T("Select Game Mode"), T("Use arrows to navigate.\nPress Enter to select."));

        if (modeChoice == -1) {
            // User pressed Esc, return to main menu
            return;
        }

        againstAI = (modeChoice == 1); // Check if the player selected "Play Against AI"
    }
    else {
        againstAI = previousAgainstAI; // Use the remembered mode
    }

    std::vector<std::vector<char>> board(BoardSize, std::vector<char>(BoardSize, ' '));

    int currentPlayer = currentStartingPlayer;
    char playerSymbols[2] = { Player1Symbol, Player2Symbol };
    size_t selectedColumn = 0;

    while (true) {
        // Construct the header message
        std::string header = T("Player") + " " + std::to_string(currentPlayer) + " (" + playerSymbols[currentPlayer - 1] + ") - ";
        header += (againstAI && currentPlayer == 2) ? T("AI is thinking...") : T("Select a column");

        ConsoleClear();

        // Display the board with the current header
        std::cout << header << "\n\n";
        for (size_t row = 0; row < BoardSize; row++) {
            for (size_t col = 0; col < BoardSize; col++) {
                std::cout << "| " << board[row][col] << " ";
            }
            std::cout << "|\n";
            for (size_t col = 0; col < BoardSize; col++) {
                std::cout << "----";
            }
            std::cout << "\n";
        }

        // Display column numbers
        for (size_t col = 0; col < board[0].size(); col++) {
            if (col + 1 >= 10) {
                std::cout << " " << col + 1 << " "; // Columns >= 10
            }
            else {
                std::cout << "  " << col + 1 << " "; // Columns < 10
            }
        }
        std::cout << "\n";

        if (againstAI && currentPlayer == 2) {
            // AI's turn
            std::this_thread::sleep_for(std::chrono::milliseconds(AnimationSpeed + 500)); // Simulate thinking time
            selectedColumn = GetAIMove(board, playerSymbols[1], AIDifficulty); // Pass depth based on difficulty (2, 4, 6, 8, 10)
            // Call AI move function
        }
        else {
            // Player's turn
            selectedColumn = NavigateColumn(board, selectedColumn, header);
        }

        // Place the piece in the column
        for (int row = BoardSize - 1; row >= 0; row--) {
            if (board[row][selectedColumn] == ' ') {
                board[row][selectedColumn] = playerSymbols[currentPlayer - 1];
                break;
            }
        }

        // Check for win or draw
        if (CheckWin(board, playerSymbols[currentPlayer - 1])) {
            ConsoleClear();
            std::cout << T("Player") << " " << currentPlayer << " (" << playerSymbols[currentPlayer - 1] << ") " << T("wins!") << "\n";

            if (currentPlayer == 1) {
                Player1Score++;
            }
            else {
                Player2Score++;
            }
            break;
        }

        bool full = true;
        for (size_t i = 0; i < BoardSize; i++) {
            if (board[0][i] == ' ') {
                full = false;
                break;
            }
        }
        if (full) {
            ConsoleClear();
            std::cout << T("Draw! The board is full.") << "\n";
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    currentStartingPlayer = (currentStartingPlayer == 1) ? 2 : 1;
    std::swap(playerSymbols[0], playerSymbols[1]);

    std::ostringstream headerStream;
    headerStream << T("Player Scores:") << "\n";
    headerStream << T("Player 1") << " (" << Player1Symbol << "): " << Player1Score << " " << T("points") << "\n";
    headerStream << T("Player 2") << " (" << Player2Symbol << "): " << Player2Score << " " << T("points") << "\n";
    std::string header = headerStream.str();

    // End game menu
    std::vector<std::string> endGameMenu = {
        T("Play Again"),
        T("Return to Main Menu")
    };

    size_t choice = NavigateMenu(endGameMenu, true, header, T("Select one of the above options by pressing Enter."));

    if (choice == 0) {
        // Replay with the same mode
        Play(true, againstAI);
        return;
    }
    else if (choice == 1 || choice == -1) {
        return; // Return to main menu
    }
}

bool CheckWin(const std::vector<std::vector<char>>& board, char symbol) {
    int n = board.size();

    // Sprawdzenie poziome
    for (int row = 0; row < n; row++) {
        for (int col = 0; col <= n - CheckSize; col++) {
            bool win = true;
            for (int k = 0; k < CheckSize; k++) {
                if (board[row][col + k] != symbol) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    // Sprawdzenie pionowe
    for (int col = 0; col < n; col++) {
        for (int row = 0; row <= n - CheckSize; row++) {
            bool win = true;
            for (int k = 0; k < CheckSize; k++) {
                if (board[row + k][col] != symbol) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    // Sprawdzenie ukośne (lewo-dół do prawo-góra)
    for (int row = 0; row <= n - CheckSize; row++) {
        for (int col = 0; col <= n - CheckSize; col++) {
            bool win = true;
            for (int k = 0; k < CheckSize; k++) {
                if (board[row + k][col + k] != symbol) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    // Sprawdzenie ukośne (prawo-dół do lewo-góra)
    for (int row = 0; row <= n - CheckSize; row++) {
        for (int col = CheckSize - 1; col < n; col++) {
            bool win = true;
            for (int k = 0; k < CheckSize; k++) {
                if (board[row + k][col - k] != symbol) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    return false;
}

int NavigateColumn(std::vector<std::vector<char>>& board, size_t& selectedColumn, const std::string& header) {
    char key;

    while (true) {
        ConsoleClear();

        // Wyświetlanie nagłówka
        if (!header.empty()) {
            std::cout << header << "\n\n";
        }

        // Wyświetlanie planszy z podświetloną kolumną
        for (size_t row = 0; row < board.size(); row++) {
            for (size_t col = 0; col < board[row].size(); col++) {
                if (col == selectedColumn) {
                    std::cout << "| " << board[row][col] << " ";
                }
                else {
                    std::cout << "| " << board[row][col] << " ";
                }
            }
            std::cout << "|\n";
            for (size_t col = 0; col < board[row].size(); col++) {
                std::cout << "----";
            }
            std::cout << "\n";
        }

        // Wyświetlanie numerów kolumn
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

        // Obsługa klawiszy
        key = GetKey();
#ifdef _WIN32
        if (key == -32) {
            char arrowKey = GetKey();
            if (arrowKey == 75) { // Strzałka w lewo
                selectedColumn = (selectedColumn == 0) ? board[0].size() - 1 : selectedColumn - 1;
            }
            else if (arrowKey == 77) { // Strzałka w prawo
                selectedColumn = (selectedColumn + 1) % board[0].size();
            }
        }
#else
        if (key == '\033') { // Sekwencje ESC w Linux/MacOS
            GetKey();         // Pomiń znak '['
            char arrowKey = GetKey();
            if (arrowKey == 'D') { // Strzałka w lewo
                selectedColumn = (selectedColumn == 0) ? board[0].size() - 1 : selectedColumn - 1;
            }
            else if (arrowKey == 'C') { // Strzałka w prawo
                selectedColumn = (selectedColumn + 1) % board[0].size();
            }
        }
#endif
        else if (key == '\r' || key == '\n') { // Enter
            if (board[0][selectedColumn] == ' ') {
                return selectedColumn;
            }
            else {
                std::cout << "\nTa kolumna jest pełna. Wybierz inną kolumnę.\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
    }
}


int NavigateMenu(const std::vector<std::string>& menuItems, bool AllowExit, const std::string& header, const std::string& footer) {
    size_t selectedIndex = 0;
    char key;

    while (true) {
        ConsoleClear();

        if (!header.empty()) {
            std::cout << header << "\n\n";
        }

        DisplayMenu(menuItems, selectedIndex);

        if (!footer.empty()) {
            std::cout << "\n" << footer;
        }

        key = GetKey();

#ifdef _WIN32
        if (key == -32) { // Sprawdzanie czy jest kliknięta klawisz specjalny w systemie Windows, w naszym przypadku jest to strzałka
            char arrowKey = GetKey();
            if (arrowKey == 72) { // Sprawdzanie czy jest kliknięta strzałka w górę
                selectedIndex = (selectedIndex == 0) ? menuItems.size() - 1 : selectedIndex - 1;
            }
            else if (arrowKey == 80) { // Sprawdzanie czy jest kliknięta strzałka w dół
                selectedIndex = (selectedIndex == menuItems.size() - 1) ? 0 : selectedIndex + 1;
            }
        }
#else
        if (key == '\033') { // Sekwencje ESC w Linux/MacOS
            GetKey(); // Pomiń znak '['
            char arrowKey = GetKey();
            if (arrowKey == 'A') { // Sprawdzanie czy jest kliknięta strzałka w górę
                selectedIndex = (selectedIndex == 0) ? menuItems.size() - 1 : selectedIndex - 1;
            }
            else if (arrowKey == 'B') { // Sprawdzanie czy jest kliknięta strzałka w dół
                selectedIndex = (selectedIndex == menuItems.size() - 1) ? 0 : selectedIndex + 1;
            }
        }
#endif
        else if (key == '\r' || key == '\n') { // Sprawdzanie czy kliknięty jest klawisze enter
            return selectedIndex;
        }
        else if (key == 27 && AllowExit) { // Sprawdzanie czy kliknięty jest klawisz Esc
            return -1; // Wyjście z menu do poprzedniego
        }
    }
}

void DisplayMenu(const std::vector<std::string>& currentMenuItems, size_t selectedIndex) { //wyświetlanie podświetlonego tekstu, interaktywna konsola
    for (size_t i = 0; i < currentMenuItems.size(); i++) {
        if (i == selectedIndex) {
            std::cout << "\033[7m" << currentMenuItems[i] << "\033[0m\n";
        }
        else {
            std::cout << currentMenuItems[i] << "\n";
        }
    }
}