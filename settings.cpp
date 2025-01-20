#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "translations.h"
#include "console.h"
#include "settings.h"
#include "gameplay.h"

//ustaiwnia domyślne, gdy nie zostały zmienione przez przez użytkownika
int boardSize = 8;
int checkSize = 4;
bool polish = true;
char player1Symbol = 'X';
char player2Symbol = 'O';
int aiDifficulty = 3;

/*Funkcja ta wczytuje ustawienia z pliku settings.txt i przypisuje je do
odpowiadających zmiennych ustawień*/
void loadSettings() {
    std::ifstream inFile("settings.txt");
    if (!inFile) {
        std::cerr << T("Error: settings.txt not found. Using default settings.") << "\n";
        return;
    }

    inFile >> boardSize;
    inFile >> checkSize;

    std::string language;
    inFile >> language;
    if (language == "Polski") {
        polish = true;
        loadTranslations("Polski");
    }
    else {
        polish = false;
        loadTranslations("English");
    }

    inFile >> player1Symbol;
    inFile >> player2Symbol;
    inFile >> aiDifficulty;

    inFile.close();
}

/*Funkcja zapisująca ustawienia do pliku settings.txt, aby nie było trzeba
za każdym razem zmieniać przy włączaniu gry*/
void saveSettings() {
    std::ofstream outFile("settings.txt");
    if (!outFile) {
        std::cerr << T("Error: Failed to save settings to the file.") << "\n";
        return;
    }

    outFile << boardSize << "\n";
    outFile << checkSize << "\n";
    outFile << (polish ? "Polski" : "English") << "\n";
    outFile << player1Symbol << "\n";
    outFile << player2Symbol << "\n";
    outFile << aiDifficulty << "\n";

    outFile.close();
}

/*Funcjka, która stanowi główne menu ustawień gry, umożliwia zmianę różnych ustawień*/
void settings() {
    int difficultyIndex = aiDifficulty - 1;
    int languageIndex = polish ? 1 : 0;
    int result;

    while (true) {
        std::vector<std::string> difficultyLevels = { T("Easy"), T("Medium"), T("Hard"), T("Very Hard"), T("Insane") };
        std::ostringstream oss;
        std::vector<std::string> settingsMenu;

        oss << std::left << std::setw(32) << T("Board Size") + ": " << std::left << std::setw(5) << boardSize;
        settingsMenu.push_back(oss.str());
        oss.str("");
        oss.clear();

        oss << std::left << std::setw((polish) ? 35 : 32) << T("Winning Line Length") + ": " << std::left << std::setw(5) << checkSize;
        settingsMenu.push_back(oss.str());
        oss.str("");
        oss.clear();

        oss << std::left << std::setw((polish) ? 33 : 32) << T("Language") + ": " << "<" << (polish ? "Polski" : "English") << ">";
        settingsMenu.push_back(oss.str());
        oss.str("");
        oss.clear();

        oss << std::left << std::setw(32) << T("Player 1 Symbol") + ": " << std::left << std::setw(5) << player1Symbol;
        settingsMenu.push_back(oss.str());
        oss.str("");
        oss.clear();

        oss << std::left << std::setw(32) << T("Player 2 Symbol") + ": " << std::left << std::setw(5) << player2Symbol;
        settingsMenu.push_back(oss.str());
        oss.str("");
        oss.clear();

        oss << std::left << std::setw((polish) ? 33 : 32) << T("AI Difficulty") + ": " << "<" << difficultyLevels[difficultyIndex] << ">";
        settingsMenu.push_back(oss.str());
        oss.str("");
        oss.clear();

        //Dodanie opcji "powrót" do menu
        settingsMenu.push_back(T("Return"));

        //Wyświetlanie menu z możliwością nawigacji
        size_t choice = navigateMenu(
            settingsMenu,
            true,
            T("Settings"),
            T("Use arrows to navigate.\nPress Enter to edit.\nPress Esc to return.")
        );

        //Wychodzenie, jeżeli wybrano "powrót" albo klinkięto klawisz Esc
        if (choice == -1 || choice == settingsMenu.size() - 1) {
            return;
        }

        switch (choice) {
        case 0: //Edytowanie wielkości planszy
            consoleClear();
            std::cout << T("Current Board Size") << ": " << boardSize << "\n";
            std::cout << T("Enter new board size") << " (>= " << checkSize * 2 << "): ";
            while (!(std::cin >> boardSize) || boardSize < checkSize * 2) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << T("Invalid size. Enter a number larger than ") << checkSize * 2 << ": ";
            }
            saveSettings();
            break;

        case 1: //Edytowanie długości rzędu symboli do wygranej
            consoleClear();
            std::cout << T("Current Winning Line Length") << ": " << checkSize << "\n";
            std::cout << T("Enter new winning line length") << " (1-" << boardSize / 2 << "): ";
            while (!(std::cin >> checkSize) || checkSize > boardSize / 2) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << T("Invalid size. Enter a number between 1 and ") << boardSize / 2 << ": ";
            }
            saveSettings();
            break;

        case 2: //Zmiana języka, do wyboru są język angielski i język polski
            result = changeSettings(
                { "English", "Polski" },
                settingsMenu,
                2,
                languageIndex,
                T("Settings"),
                T("Use left/right arrows to change language. Press Enter to save.\nPress Esc to cancel."),
                T("Language")
            );

            if (result != -1) {
                polish = (result == 1);
                loadTranslations(polish ? "Polski" : "English");
                saveSettings();
            }
            break;

        case 3: //Zmiana symbolu gracza 1
            consoleClear();
            std::cout << T("Current Player 1 Symbol") << ": " << player1Symbol << "\n";
            std::cout << T("Enter new symbol for Player 1 (exactly one character): ");
            while (true) {
                std::string input;
                std::cin >> input;
                if (input.length() == 1 && input[0] != player2Symbol && input[0] != ' ') {
                    player1Symbol = input[0];
                    break;
                }
                std::cout << T("Invalid symbol. Enter one character different from Player 2's symbol and a space: ");
            }
            saveSettings();
            break;

        case 4: //Zmiana symbolu gracza 2
            consoleClear();
            std::cout << T("Current Player 2 Symbol") << ": " << player2Symbol << "\n";
            std::cout << T("Enter new symbol for Player 2 (exactly one character): ");
            while (true) {
                std::string input;
                std::cin >> input;
                if (input.length() == 1 && input[0] != player1Symbol && input[0] != ' ') {
                    player2Symbol = input[0];
                    break;
                }
                std::cout << T("Invalid symbol. Enter one character different from Player 1's symbol and a space: ");
            }
            saveSettings();
            break;

        case 5: //Zmiana poziomu trudności AI
            result = changeSettings(
                difficultyLevels,
                settingsMenu,
                5,
                difficultyIndex,
                T("Settings"),
                T("Use left/right arrows to change difficulty. Press Enter to save.\nPress Esc to cancel."),
                T("AI Difficulty")
            );

            if (result != -1) {
                aiDifficulty = result + 1;
                saveSettings();
            }
            break;
        }
    }
}

/*Funkcja, która umożliwia dynamiczną zmianę ustawień gry typu zmiana języka czy poziomu trudności
settingsItems - lista dostępnych wartości do wyboru, settingsMenu - aktualne menu ustawień,
selectedIndex - indekst ustawienia, które użytkownik chce zmienić, settingIndex - aktualnie wybrane ustawienie
header, footer, label - dodatkowe opisy, służące do wyświetlania menu*/
int changeSettings(const std::vector<std::string>& settingItems, std::vector<std::string>& settingsMenu, size_t selectedIndex,
    int& settingIndex, const std::string& header, const std::string& footer, const std::string& label) {
    char key;

    while (true) {
        consoleClear();

        if (!header.empty()) {
            std::cout << header << "\n\n";
        }

        //Dynamiczne wyświetlanie zmienianego ustawienia
        std::ostringstream oss;
        oss << std::left
            << std::setw((T(label) == "Język" && polish) ? 33 : ((T(label) == "Poziom trudności" && polish) ? 33 : 32))
            << T(label) + ": "
            << "<" << settingItems[settingIndex] << ">";
        settingsMenu[selectedIndex] = oss.str();

        //Wyświetlanie menu po zmianach
        displayMenu(settingsMenu, selectedIndex);

        if (!footer.empty()) {
            std::cout << "\n" << footer;
        }

        key = getKey();

        if (key == -32) {
            char arrowKey = getKey();
            if (arrowKey == 75) { //Strzałka w prawo
                settingIndex = (settingIndex == 0) ? (int)settingItems.size() - 1 : settingIndex - 1;
            }
            else if (arrowKey == 77) { //Strzałka w lewo
                settingIndex = (settingIndex + 1) % settingItems.size();
            }
        }
        else if (key == '\r' || key == '\n') { //Aby zapisać i wyjść kliknij klawisz Enter
            return settingIndex;
        }
        else if (key == 27) { //Kliknij klawisz Esc aby anulować i wyjść
            return -1;
        }
    }
}