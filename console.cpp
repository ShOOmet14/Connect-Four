#include <windows.h>
#include <conio.h>

/*Ustawianie kodowania konsoli na UTF-8 w zależności od systemu operacyjnego,
aby poprawnie były wyświetlane polskie znaki*/
void initializeConsole() {
    SetConsoleOutputCP(CP_UTF8);
}

//Funckja czyszcząca konsolę w zależności od systemu operacyjnego
void consoleClear() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    DWORD written;

    if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) {
        COORD homeCoords = {0, 0};
        DWORD consoleSize = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;
        FillConsoleOutputCharacter(hConsole, ' ', consoleSize, homeCoords, &written);
        FillConsoleOutputAttribute(hConsole, consoleInfo.wAttributes, consoleSize, homeCoords, &written);
        SetConsoleCursorPosition(hConsole, homeCoords);
    }
}

//Funkcja pobierająca wciśnięty na klawiaturze znak, potrzebna do zrobienia interaktywnego menu
char getKey() {
    return _getch();
}

//Funkcja zmieniająca kolory konsoli
void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}