#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <locale>
#include <termios.h>
#include <unistd.h>
#endif
#include "console.h"

/*Ustawianie kodowania konsoli na UTF-8 w zależności od systemu operacyjnego,
aby poprawnie były wyświetlane polskie znaki*/
void initializeConsole() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #else
        setlocale(LC_ALL, "pl_PL.UTF-8");
    #endif
}

//Funckja czyszcząca konsolę w zależności od systemu operacyjnego
void consoleClear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//Funkcja pobierająca wciśnięty na klawiaturze znak, potrzebna do zrobienia interaktywnego menu
char getKey() {
#ifdef _WIN32
    return _getch();
#else
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}