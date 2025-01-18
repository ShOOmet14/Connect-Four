#pragma once
#ifdef _WIN32
#include <windows.h> //do kodowania utf-8 w konsoli systemu Windows
#include <conio.h> //używam, aby sprawdzać jaki klawisz klawiatury jest naciskany, używając _getch(), do stworzenia interaktywnego menu
#else
#include <locale> //do kodowania utf-8 w systemach Linux i MacOS
#include <termios.h> //używam tej biblioteki, aby przełączyć terminal w tryb, w którym Enter nie jest wymagane do odczytywania klawiszy
#include <unistd.h>
#endif //nie deklaruję przestrzeni nazw std, ponieważ przy dużych projektach i posiadaniu wielu przestrzeni nazw ciężko określić co jest z jakiej przestrzeni nazw

//funkcja zmieniająca kodowanie w konsoli na utf-8
void InitializeConsole();

//funckja czyszcząca konsolę
void ConsoleClear();

//funkcja służąca do rejestrowania klawiszy bez buforowania konsoli
char GetKey();