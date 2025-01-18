#include "menu.h"
#include "gameplay.h"
#include "translations.h"
#include "settings.h"
#include "console.h"

void MainMenu() {
    std::vector<std::string> menuItems = {
        T("Play"),
        T("Settings"),
        T("Show Scores"),
        T("Tutorial"),
        T("Exit")
    };

    size_t choice = NavigateMenu(menuItems, true, T("Main menu"), T("Use arrows to navigate.\nPress Enter to select.\nPress Esc to return."));

    switch (choice) {
    case 0:
        Play();
        break;
    case 1:
        Settings();
        break;
    case 2:
        ShowScores();
        break;
    case 3:
        ShowTutorial();
        break;
    case 4:
    case -1:
        Exit();
        break;
    }
}

void ShowScores() {
    ConsoleClear();

    std::ostringstream currentScore;
    currentScore << T("Player Scores:") << "\n";
    currentScore << T("Player 1") << " (" << Player1Symbol << "): " << Player1Score << " " << T("points") << "\n";
    currentScore << T("Player 2") << " (" << Player2Symbol << "): " << Player2Score << " " << T("points") << "\n";
    std::string header = currentScore.str();

    std::vector<std::string> menuItems = { T("Return to Main Menu") };

    size_t choice = NavigateMenu(menuItems, true, header, T("Press Enter or Esc to return to the main menu."));

    if (choice == 0 || choice == -1) { // Powrót do menu głównego
        return;
    }
}

void ShowTutorial() {
    ConsoleClear();
    std::ostringstream tutorialContent;

    tutorialContent << "===== " << T("Tutorial") << " =====\n\n";
    tutorialContent << "1. " << T("Game Objective:") << "\n";
    tutorialContent << "   - " << T("Place your symbols") << " (" << Player1Symbol << " " << T("or") << " " << Player2Symbol << ") " << T("in a single line.") << "\n";
    tutorialContent << "   - " << T("The player who first aligns") << " " << CheckSize << " " << T("symbols vertically, horizontally, or diagonally wins.") << "\n\n";
    tutorialContent << "2. " << T("Game Rules:") << "\n";
    tutorialContent << "   - " << T("Players take turns making moves.") << "\n";
    tutorialContent << "   - " << T("Symbols fall to the lowest available spot in the selected column.") << "\n";
    tutorialContent << "   - " << T("The game ends when a player wins or the board is full (draw).") << "\n\n";
    tutorialContent << "3. " << T("Controls during the game:") << "\n";
    tutorialContent << "   - " << T("Use arrows to select a column.") << "\n";
    tutorialContent << "   - " << T("Press Enter to confirm your move.") << "\n\n";
    tutorialContent << "4. " << T("Controls in the menu:") << "\n";
    tutorialContent << "   - " << T("Arrow keys up/down: Navigate between options.") << "\n";
    tutorialContent << "   - " << T("Enter: Confirm your selection.") << "\n";
    tutorialContent << "   - " << T("Esc: Return to the previous menu.") << "\n\n";
    tutorialContent << "5. " << T("Settings:") << "\n";
    tutorialContent << "   - " << T("You can adjust the board size, animation speed, and player symbols in the settings menu.") << "\n\n";
    tutorialContent << "6. " << T("Exiting the game:") << "\n";
    tutorialContent << "   - " << T("You can exit the game at any time by selecting the 'Exit' option in the menu.") << "\n\n";
    tutorialContent << "======================";

    std::string header = tutorialContent.str();

    std::vector<std::string> menuItems = { T("Return to Main Menu") };

    size_t choice = NavigateMenu(menuItems, true, header, T("Press Enter or Esc to return to the main menu."));

    if (choice == 0 || choice == -1) { // Powrót do menu głównego
        return;
    }
}

void Exit() {
    std::vector<std::string> exitItems = { T("Yes"), T("No") };
    size_t choice = NavigateMenu(exitItems, false, T("Are you sure you want to exit?"));

    if (choice == 0) {
        Playing = false;
    }
}