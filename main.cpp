//W trakcie pisania kodu odkryłem, że taka gra już istniała i po angielsku nazwya się "Connect four" a po polsku "Czwórki"
//https://github.com/nlohmann/json/tree/v3.11.3 - stąd biorę bibliotekę dodającą możliwość korzystania z plików Json

#include "console.h"
#include "gameplay.h"
#include "menu.h"
#include "settings.h"
#include "translations.h"

int main() {
    InitializeConsole();
    LoadSettings(); //Wczytanie ustawień zapisanych w pliku

    while (Playing == true) {
        MainMenu();
    }

    ConsoleClear();
    std::cout << T("Thank you for playing!") << "\n" << T("The program will close in a few seconds.") << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));
    return 0;
}