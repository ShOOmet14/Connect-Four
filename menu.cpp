#include <vector>
#include <string>
#include <sstream>
#include "console.h"
#include "translations.h"
#include "menu.h"
#include "gameplay.h"
#include "settings.h"

/*Wyświetla główne menu gry z następującymi opcjami: Graj, Ustawienia, Pokaż wynik, Samouczek, Wyjście.
W zależności od wyboru obsługike odpowiednią funkcję*/
void mainMenu() {
    std::vector<std::string> menuItems = {
        T("Play"),
        T("Settings"),
        T("Show Scores"),
        T("Tutorial"),
        T("Exit")
    };

    size_t choice = navigateMenu(menuItems, true, T("Main menu"), T("Use arrows to navigate.\nPress Enter to select.\nPress Esc to return."));

    switch (choice) {
    case 0:
        play();
        break;
    case 1:
        settings();
        break;
    case 2:
        showScores();
        break;
    case 3:
        showTutorial();
        break;
    case 4:
    case -1:
        exit();
        break;
    }
}

//Funkcja ta wyświetla aktualne wyniki graczy, punkty dla gracza 1 i gracza 2
void showScores() {
    consoleClear();

    std::ostringstream currentScore;
    currentScore << T("Player Scores:") << "\n";
    currentScore << T("Player 1") << " (" << player1Symbol << "): " << player1Score << " " << T("points") << "\n";
    currentScore << T("Player 2") << " (" << player2Symbol << "): " << player2Score << " " << T("points") << "\n";
    std::string header = currentScore.str();

    std::vector<std::string> menuItems = { T("Return to Main Menu") };

    size_t choice = navigateMenu(menuItems, true, header, T("Press Enter or Esc to return to the main menu."));

    if (choice == 0 || choice == -1) {
        return;
    }
}

/*Funkcja ta wyświetla zasady i instrukcje dotyczące gry, są w nich między innymi:
cel gry, zasady wykonywania ruchów, kontrolowanie*/
void showTutorial() {
    consoleClear();
    std::ostringstream tutorialContent;

    tutorialContent << "===== " << T("Tutorial") << " =====\n\n";
    tutorialContent << "1. " << T("Game Objective:") << "\n";
    tutorialContent << "   - " << T("Place your symbols") << " (" << player1Symbol << " " << T("or") << " " << player2Symbol << ") " << T("in a single line.") << "\n";
    tutorialContent << "   - " << T("The player who first aligns") << " " << checkSize << " " << T("symbols vertically, horizontally, or diagonally wins.") << "\n\n";
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

    size_t choice = navigateMenu(menuItems, true, header, T("Press Enter or Esc to return to the main menu."));

    if (choice == 0 || choice == -1) {
        return;
    }
}

//Pyta się użytkownika czy chce wyjść, jeżeli chce to kończy główną pętlę gry i zamyka program
void exit() {
    std::vector<std::string> exitItems = { T("Yes"), T("No") };
    size_t choice = navigateMenu(exitItems, false, T("Are you sure you want to exit?"));

    if (choice == 0) {
        playing = false;
    }
}