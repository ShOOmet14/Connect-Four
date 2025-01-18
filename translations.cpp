#include "translations.h"
#include "settings.h"

std::unordered_map<std::string, std::string> translations;

void LoadTranslations(const std::string& language) {
    try {
        std::ifstream file("resources/translations.json");
        if (!file.is_open()) {
            throw std::runtime_error(T("Unable to open translations.json file."));
        }

        nlohmann::json jsonFile;
        file >> jsonFile;

        if (jsonFile.contains(language)) {
            translations = jsonFile[language].get<std::unordered_map<std::string, std::string>>();
        }
        else {
            throw std::runtime_error(T("Translations not found for the language: ") + language);
        }
    }
    catch (const std::exception& e) {
        std::cerr << T("Error: ") << e.what() << "\n";
        translations.clear(); // Clear translations on failure
    }
}

std::string T(const std::string& key) {
    if (translations.find(key) != translations.end()) {
        return translations[key];
    }
    return key; // W przypadku braku tłumaczenia zwróć klucz.
}