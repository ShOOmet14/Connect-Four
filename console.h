#pragma once

/*Ustawianie kodowania konsoli na UTF-8 w zależności od systemu operacyjnego, 
aby poprawnie były wyświetlane polskie znaki*/
void initializeConsole();

//Funckja czyszcząca konsolę w zależności od systemu operacyjnego
void consoleClear();

//Funkcja pobierająca wciśnięty na klawiaturze znak, potrzebna do zrobienia interaktywnego menu
char getKey();