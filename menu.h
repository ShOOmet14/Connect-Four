#pragma once

/*Wyświetla główne menu gry z następującymi opcjami: Graj, Ustawienia, Pokaż wynik, Samouczek, Wyjście.
W zależności od wyboru obsługike odpowiednią funkcję*/
void mainMenu();

//Funkcja ta wyświetla aktualne wyniki graczy, punkty dla gracza 1 i gracza 2
void showScores();

/*Funkcja ta wyświetla zasady i instrukcje dotyczące gry, są w nich między innymi: 
cel gry, zasady wykonywania ruchów, kontrolowanie*/
void showTutorial();

//Pyta się użytkownika czy chce wyjść, jeżeli chce to kończy główną pętlę gry i zamyka program
void exit();