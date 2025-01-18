#pragma once
#include <vector> //używane do tworzenia dynamicznych tablic, które są potrzebne do przekazywania kontekstu menu, oraz do samej gry
#include <thread> //korzystam z nich aby zatrzymać na chwilę program, przed wyłączeniem go
#include <chrono> //używam chrono i thread, ponieważ są one uniwersalne na każdy system
#include <sstream> //użwam tej biblioteki do poprawnego wyświetlania menu ustawień

extern bool Playing;
extern int currentStartingPlayer;
extern int Player1Score;
extern int Player2Score;

void Play(bool rememberMode = false, bool previousAgainstAI = false);

bool CheckWin(const std::vector<std::vector<char>>& board, char symbol);

int NavigateColumn(std::vector<std::vector<char>>& board, size_t& selectedColumn, const std::string& header = "");

//funkcja umożliwająca nawigowanie w konsoli używając strzałek oraz klawiszy enter i escape
int NavigateMenu(const std::vector<std::string>& menuItems, bool AllowExit, const std::string& header = "", const std::string& footer = "");

void DisplayMenu(const std::vector<std::string>& currentMenuItems, size_t selectedIndex);
