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
        HANDLE                     hStdOut;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD                      count;
        DWORD                      cellCount;
        COORD                      homeCoords = { 0, 0 };

        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hStdOut == INVALID_HANDLE_VALUE) return;

        /* Get the number of cells in the current buffer */
        if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
        cellCount = csbi.dwSize.X * csbi.dwSize.Y;

        /* Fill the entire buffer with spaces */
        if (!FillConsoleOutputCharacter(
            hStdOut,
            (TCHAR)' ',
            cellCount,
            homeCoords,
            &count
        )) return;

        /* Fill the entire buffer with the current colors and attributes */
        if (!FillConsoleOutputAttribute(
            hStdOut,
            csbi.wAttributes,
            cellCount,
            homeCoords,
            &count
        )) return;

        /* Move the cursor home */
        SetConsoleCursorPosition(hStdOut, homeCoords);
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