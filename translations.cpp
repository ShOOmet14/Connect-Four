#include <unordered_map>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "translations.h"

/*Funkcja ta przechowuje wszystkie słowa kluczowe i ich odpowiadające wartości / tłumaczenia
pozwala funkcji T dynamicznie zwracać odpowiednie tłumaczenie*/
std::unordered_map<std::string, std::string> translations;

/*Ta funkcja otwiera plik translations.json, następnie wczytuje plik jako obiekt JSON,
sprawdza czy plik zawiera tłumaczenia do danego języka i zapisuje je do globalnej mapy "translations"*/
void loadTranslations(const std::string& language) {
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
    catch (const std::exception& e) { //Jeżeli coś pójdzie nie tak, wypisuje błąd i czyści globalną mapę "translations"
        std::cerr << T("Error: ") << e.what() << "\n";
        translations.clear(); 
    }
}

/*Funkcja ta szuka tłumaczenia w mapie "translations" na podstawie słowa kluczowego, jeżeli istnieje 
to zwraca jego wartość, a jak nie istnieje to zwraca słowo kluczowe*/
std::string T(const std::string& key) {
    if (translations.find(key) != translations.end()) {
        return translations[key];
    }
    return key;
}