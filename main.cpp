/*W trakcie pisania kodu odkryłem, że taka gra już istniała i po angielsku nazwya się "Connect four" a po polsku "Czwórki"
https://github.com/nlohmann/json/tree/v3.11.3 - stąd biorę bibliotekę dodającą możliwość korzystania z plików Json
Projekt na zajęcia z wstępu do programowania, nie jest skończony, chciałbym jeszcze dodać dużo do programu i spróbować więcej rzeczy,
typu */

#include <iostream>
#include <chrono>
#include <thread>
#include <nlohmann/json.hpp>
#include "translations.h"
#include "settings.h"
#include "console.h"
#include "menu.h"
#include "gameplay.h"

int main() {
    initializeConsole(); //Funkcja, która ustawia kodowanie konsoli na utf-8
    loadSettings(); //Wczytanie ustawień zapisanych w pliku settings.txt

    while (playing == true) {
        mainMenu();
    }

    consoleClear(); //Funkcja, która czyści konsolę
    std::cout << T("Thank you for playing!") << "\n" << T("The program will close in a few seconds.") << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));
    return 0;
}