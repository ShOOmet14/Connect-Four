#include "console.h"

void InitializeConsole() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8); //do włączenia kodowania utf-8 na Windows-ie, niezależnie jakie w ustawieniach jest włączone locale (u mnie nie działało locale)
    #else
        setlocale(LC_ALL, "pl_PL.UTF-8"); //tak samo ale dla systemów Linux i MacOS
    #endif
}

void ConsoleClear() { //funkcja służąca do czyszczenia konsoli, bierze pod uwagę system operacyjny
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

char GetKey() { //to jest funkcja która pobiera wciśnięty klawisz, zrobiona osobno, aby działała na Windows i Linux
#ifdef _WIN32
    return _getch(); //to pozwala na pobieranie klawisza z klawiatury bez buforowania konsoli
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