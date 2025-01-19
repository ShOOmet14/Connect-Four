#pragma once
#include <string>
#include <vector>

extern bool playing; //Zmienna określająca czy gra jest w trakcie, główna pętla gry
extern int currentStartingPlayer; //Zmienna przechowująca informacje, który gracz zaczyna aktualną rundę
extern int player1Score; //Przechowuje aktualny wynik gracza 1
extern int player2Score; //Przechowuje aktualny wynik gracza 2
extern int lastMoveRow;
extern int lastMoveCol;

/*Funkcja ta rozpoczyna rozgrywkę, można grać na innego gracza albo AI.
rememberMode - jeżeli prawidziwa, to gra używa poprzedniego trybu (hot seat / vs AI)
previousAgainstAI - określa czy ostatnia gra była przeciwko AI*/
void play(bool rememberMode = false, bool previousAgainstAI = false);

//Funkcja, która sprawdza czy dany symbol ułożył ciąg wystarczającej długości w pionie, poziomie i na ukos, aby wygrać
bool checkWin(const std::vector<std::vector<char>>& board, char symbol);

/*Funckja, która umożliwia użytkownikowi nawigowanie między kolumnami planszy przy użyciu strzałek.
board - aktualny stan planszy, selectedColumn - wybrana/podświetlona kolumna, header - nagłówek wyświetlany nad planszą*/
int navigateColumn(std::vector<std::vector<char>>& board, size_t& selectedColumn, const std::string& header = "");

/*Umożliwia użytkownikowi nawigowanie w między opcjami menu.
menuItems - lista opcji w menu, allowExit - zezwolenie na wyjście z konkretnego menu, header/footer - nagłówek nad menu/stopka pod menu*/
int navigateMenu(const std::vector<std::string>& menuItems, bool allowExit, const std::string& header = "", const std::string& footer = "");

/*Funckja ta wyświetla menu na ekranie z podświetleniem aktualnie wybranej opcji.
currentMenuItems - lista opcji w menu, selectedIndex - indeks aktualnie wybranej opcji*/
void displayMenu(const std::vector<std::string>& currentMenuItems, size_t selectedIndex);
