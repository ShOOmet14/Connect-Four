#pragma once
#include <string>
#include <vector>

extern int boardSize; //Rozmiar planszy gry
extern int checkSize; //Liczba symboli w rzędzie, która wymagana jest do wygrania
extern bool polish; //Zmienna, która ustawią język na polski, albo angielski
extern int animationSpeed; //prędkość animacji (spadania symboli) w milisekundach
extern char player1Symbol; //symbol gracza 1
extern char player2Symbol; //symbol gracza 2
extern int aiDifficulty; //poziom trudności AI, w skali 1-5

/*Funkcja ta wczytuje ustawienia z pliku settings.txt i przypisuje je do 
odpowiadających zmiennych ustawień*/
void loadSettings();

/*Funkcja zapisująca ustawienia do pliku settings.txt, aby nie było trzeba 
za każdym razem zmieniać przy włączaniu gry*/
void saveSettings();

/*Funcjka, która stanowi główne menu ustawień gry, umożliwia zmianę różnych ustawień*/
void settings();

/*Funkcja, która umożliwia dynamiczną zmianę ustawień gry typu zmiana języka czy poziomu trudności
settingsItems - lista dostępnych wartości do wyboru, settingsMenu - aktualne menu ustawień, 
selectedIndex - indekst ustawienia, które użytkownik chce zmienić, settingIndex - aktualnie wybrane ustawienie
header, footer, label - dodatkowe opisy, służące do wyświetlania menu*/
int changeSettings(const std::vector<std::string>& settingItems,
    std::vector<std::string>& settingsMenu,
    size_t selectedIndex,
    int& settingIndex,
    const std::string& header,
    const std::string& footer,
    const std::string& label);