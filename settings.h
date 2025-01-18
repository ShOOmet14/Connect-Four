#pragma once
#include <fstream> //użwana do zapisywania i wczytywania ustawień gry z pliku
#include <iomanip> //używam tej biblioteki do wyświetlania konkretnych ustawień w tej samej kolumnie
#include <limits> //używam w trakcie sprawdzania czy użytkownik wpisał odpowiednią wartość
#include "gameplay.h"
#include "translations.h"

#define NOMINMAX   // Wyłączenie makr min i max w windows.h, ponieważ wywołują konflikt, a ich nie potrzebuję

//zmienne ustawień
extern int BoardSize;
extern int CheckSize;
extern bool Polish;
extern int AnimationSpeed;
extern char Player1Symbol;
extern char Player2Symbol;
extern int AIDifficulty;

//Ładowanie ustawień programu z pliku
void LoadSettings();

//Zapisywanie ustawienia programu do pliu
void SaveSettings();

//Główna funkcja interfejsu ustawień
void Settings();

int ChangeSettings(const std::vector<std::string>& settingItems,
    std::vector<std::string>& settingsMenu,
    size_t selectedIndex,
    int& settingIndex,
    const std::string& header,
    const std::string& footer,
    const std::string& label);