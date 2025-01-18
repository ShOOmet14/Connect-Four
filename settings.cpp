#include "settings.h"
#include "translations.h"
#include "console.h"
#include "gameplay.h"

int BoardSize = 10;
int CheckSize = 5;
bool Polish = true;
int AnimationSpeed = 100;
char Player1Symbol = 'X';
char Player2Symbol = 'O';
int AIDifficulty = 3; // Default to medium difficulty

void LoadSettings() {
    std::ifstream inFile("settings.txt");
    if (!inFile) {
        std::cerr << T("Error: settings.txt not found. Using default settings.") << "\n";
        return;
    }

    inFile >> BoardSize;
    inFile >> CheckSize;

    std::string language;
    inFile >> language;
    if (language == "Polski") {
        Polish = true;
        LoadTranslations("Polski");
    }
    else {
        Polish = false;
        LoadTranslations("English");
    }

    inFile >> AnimationSpeed;
    inFile >> Player1Symbol;
    inFile >> Player2Symbol;
    inFile >> AIDifficulty; // Load AI difficulty

    inFile.close();
}

void SaveSettings() {
    std::ofstream outFile("settings.txt");
    if (!outFile) {
        std::cerr << T("Error: Failed to save settings to the file.") << "\n";
        return;
    }

    outFile << BoardSize << "\n";
    outFile << CheckSize << "\n";
    outFile << (Polish ? "Polski" : "English") << "\n";
    outFile << AnimationSpeed << "\n";
    outFile << Player1Symbol << "\n";
    outFile << Player2Symbol << "\n";
    outFile << AIDifficulty << "\n"; // Save AI difficulty

    outFile.close();
    std::cout << T("Settings have been saved to settings.txt.") << "\n";
}

void Settings() {
    const std::vector<std::string> difficultyLevels = { "Easy", "Medium", "Hard", "Very Hard", "Insane" };
    int difficultyIndex = AIDifficulty - 1; // Map AIDifficulty (1-5) to index (0-4)
    int languageIndex = Polish ? 1 : 0; // 0 for English, 1 for Polski
    int result;

    while (true) {
        std::ostringstream oss;
        std::vector<std::string> settingsMenu;

        // Dynamically format and display each setting
        oss << std::left << std::setw(32) << T("Board Size") + ": " << std::left << std::setw(5) << BoardSize;
        settingsMenu.push_back(oss.str());
        oss.str("");
        oss.clear();

        oss << std::left << std::setw((Polish) ? 36 : 32) << T("Winning Line Length") + ": " << std::left << std::setw(5) << CheckSize;
        settingsMenu.push_back(oss.str());
        oss.str("");
        oss.clear();

        oss << std::left << std::setw((Polish) ? 33 : 32) << T("Language") + ": " << "<" << (Polish ? "Polski" : "English") << ">";
        settingsMenu.push_back(oss.str());
        oss.str("");
        oss.clear();

        oss << std::left << std::setw((Polish) ? 34 : 32) << T("Animation Speed (ms)") + ": " << std::left << std::setw(5) << AnimationSpeed;
        settingsMenu.push_back(oss.str());
        oss.str("");
        oss.clear();

        oss << std::left << std::setw(32) << T("Player 1 Symbol") + ": " << std::left << std::setw(5) << Player1Symbol;
        settingsMenu.push_back(oss.str());
        oss.str("");
        oss.clear();

        oss << std::left << std::setw(32) << T("Player 2 Symbol") + ": " << std::left << std::setw(5) << Player2Symbol;
        settingsMenu.push_back(oss.str());
        oss.str("");
        oss.clear();

        oss << std::left << std::setw(32) << T("AI Difficulty") + ": " << "<" << difficultyLevels[difficultyIndex] << ">";
        settingsMenu.push_back(oss.str());
        oss.str("");
        oss.clear();

        // Add the return option
        settingsMenu.push_back(T("Return"));

        // Display the menu and allow navigation
        size_t choice = NavigateMenu(
            settingsMenu,
            true,
            T("Settings"),
            T("Use arrows to navigate.\nPress Enter to edit.\nPress Esc to return.")
        );

        if (choice == -1 || choice == settingsMenu.size() - 1) {
            // Exit the settings menu
            return;
        }

        // Handle the user's choice
        switch (choice) {
        case 0: // Edit Board Size
            ConsoleClear();
            std::cout << T("Current Board Size") << ": " << BoardSize << "\n";
            std::cout << T("Enter new board size") << " (>= " << CheckSize * 2 << "): ";
            while (!(std::cin >> BoardSize) || BoardSize < CheckSize * 2) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << T("Invalid size. Enter a number larger than ") << CheckSize * 2 << ": ";
            }
            SaveSettings();
            break;

        case 1: // Edit Winning Line Length
            ConsoleClear();
            std::cout << T("Current Winning Line Length") << ": " << CheckSize << "\n";
            std::cout << T("Enter new winning line length") << " (1-" << BoardSize / 2 << "): ";
            while (!(std::cin >> CheckSize) || CheckSize > BoardSize / 2) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << T("Invalid size. Enter a number between 1 and ") << BoardSize / 2 << ": ";
            }
            SaveSettings();
            break;

        case 2: // Change Language
            result = ChangeSettings(
                { "English", "Polski" }, // The list of language options
                settingsMenu,            // The settings menu to update dynamically
                2,                       // The index of Language in the settings menu
                languageIndex,           // The current language index
                T("Settings"),           // Header
                T("Use left/right arrows to change language. Press Enter to save.\nPress Esc to cancel."),
                T("Language")            // Label for this setting
            );

            if (result != -1) {
                Polish = (result == 1); // Update the language setting (0 for English, 1 for Polski)
                LoadTranslations(Polish ? "Polski" : "English"); // Load the appropriate translations
                SaveSettings();
            }
            break;

        case 3: // Edit Animation Speed
            ConsoleClear();
            std::cout << T("Current Animation Speed") << ": " << AnimationSpeed << " ms\n";
            std::cout << T("Enter new animation speed (0-1000, where 0 disables animation): ");
            while (!(std::cin >> AnimationSpeed) || AnimationSpeed < 0 || AnimationSpeed > 1000) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << T("Invalid value. Enter a number between 0 and 1000: ");
            }
            SaveSettings();
            break;

        case 4: // Edit Player 1 Symbol
            ConsoleClear();
            std::cout << T("Current Player 1 Symbol") << ": " << Player1Symbol << "\n";
            std::cout << T("Enter new symbol for Player 1 (exactly one character): ");
            while (true) {
                std::string input;
                std::cin >> input;
                if (input.length() == 1 && input[0] != Player2Symbol && input[0] != ' ') {
                    Player1Symbol = input[0];
                    break;
                }
                std::cout << T("Invalid symbol. Enter one character different from Player 2's symbol and a space: ");
            }
            SaveSettings();
            break;

        case 5: // Edit Player 2 Symbol
            ConsoleClear();
            std::cout << T("Current Player 2 Symbol") << ": " << Player2Symbol << "\n";
            std::cout << T("Enter new symbol for Player 2 (exactly one character): ");
            while (true) {
                std::string input;
                std::cin >> input;
                if (input.length() == 1 && input[0] != Player1Symbol && input[0] != ' ') {
                    Player2Symbol = input[0];
                    break;
                }
                std::cout << T("Invalid symbol. Enter one character different from Player 1's symbol and a space: ");
            }
            SaveSettings();
            break;

        case 6: // AI Difficulty
            result = ChangeSettings(
                difficultyLevels, // The list of difficulty levels
                settingsMenu,     // The settings menu to update dynamically
                6,                // The index of AI Difficulty in the settings menu
                difficultyIndex,  // The current difficulty index
                T("Settings"),    // Header
                T("Use left/right arrows to change difficulty. Press Enter to save.\nPress Esc to cancel."),
                T("AI Difficulty")   // Label for this setting
            );

            if (result != -1) {
                AIDifficulty = result + 1; // Update the difficulty based on selection
                SaveSettings();
            }
            break;
        }
    }
}

int ChangeSettings(const std::vector<std::string>& settingItems, std::vector<std::string>& settingsMenu, size_t selectedIndex,
    int& settingIndex, const std::string& header, const std::string& footer, const std::string& label) {
    char key;

    while (true) {
        ConsoleClear();

        if (!header.empty()) {
            std::cout << header << "\n\n";
        }

        // Update the selected setting in the settingsMenu dynamically
        std::ostringstream oss;
        oss << std::left << std::setw((T(label) == "Język" && (Polish))?33:32) << T(label) + ": " << "<" << settingItems[settingIndex] << ">";
        settingsMenu[selectedIndex] = oss.str();

        // Display the updated menu
        DisplayMenu(settingsMenu, selectedIndex);

        if (!footer.empty()) {
            std::cout << "\n" << footer;
        }

        key = GetKey();

#ifdef _WIN32
        if (key == -32) { // Arrow keys for Windows
            char arrowKey = GetKey();
            if (arrowKey == 75) { // Left Arrow
                settingIndex = (settingIndex == 0) ? settingItems.size() - 1 : settingIndex - 1;
            }
            else if (arrowKey == 77) { // Right Arrow
                settingIndex = (settingIndex + 1) % settingItems.size();
            }
        }
#else
        if (key == '\033') { // Arrow keys for Linux/Mac
            GetKey(); // Skip '['
            char arrowKey = GetKey();
            if (arrowKey == 'D') { // Left Arrow
                settingIndex = (settingIndex == 0) ? settingItems.size() - 1 : settingIndex - 1;
            }
            else if (arrowKey == 'C') { // Right Arrow
                settingIndex = (settingIndex + 1) % settingItems.size();
            }
        }
#endif
        else if (key == '\r' || key == '\n') { // Enter key to save and exit
            return settingIndex;
        }
        else if (key == 27) { // Escape key to cancel
            return -1; // Exit without changes
        }
    }
}