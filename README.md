# Connect Four Game

## Overview

This project is a **console-based implementation of the popular game Connect Four**. It was developed as part of an introduction to programming class, it was also my first bigger project 😊. The game can be played in either **Player vs Player** mode or **Player vs AI** mode with adjustable difficulty. The project also includes **settings customization** and **multi-language support** (English and Polish).

## Features

- **Two Game Modes**: Play against another player or challenge the AI.
- **AI Implementation**: Uses the Minimax algorithm with alpha-beta pruning for efficient decision-making.
- **Settings Customization**: Adjust board size, winning line length, player symbols, and AI difficulty.
- **Multilingual Support**: Currently supports English and Polish.
- **Interactive Console Menu**: Navigate through the game options using keyboard controls.

## How to Play

1. Run the game from the console.
2. Choose your preferred game mode from the main menu:
   - Hot Seat (Player vs Player)
   - Play Against AI
3. Place your symbols by selecting a column. The symbols will drop to the lowest available position in that column.
4. Win the game by aligning the required number of symbols vertically, horizontally, or diagonally.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/ShOOmet14/Connect-Four.git
   ```
2. Navigate to the project folder:
   ```bash
   cd Connect-Four
   ```
3. Compile the project using a C++ compiler like `g++`:
   ```bash
   g++ -std=c++17 -o connect_four main.cpp AI.cpp console.cpp gameplay.cpp menu.cpp settings.cpp translations.cpp
   ```
4. Run the compiled program:
   ```bash
   ./connect_four
   ```

## Files

- **main.cpp**: Entry point of the application.
- **AI.cpp**: Contains AI logic, including Minimax algorithm with alpha-beta pruning.
- **console.cpp**: Handles console-related operations like clearing the screen and setting colors.
- **gameplay.cpp**: Manages the game flow and checks for win conditions.
- **menu.cpp**: Implements the main menu and navigation.
- **settings.cpp**: Handles settings such as board size and player symbols.
- **translations.cpp**: Provides multilingual support by loading translations from a JSON file.

## Customization

### Settings

Settings can be adjusted through the "Settings" menu in the game. Alternatively, you can manually edit `settings.txt` to:

- Change the board size
- Adjust the winning line length
- Modify player symbols
- Set the AI difficulty
- Switch the language

## Dependencies

- C++17 or higher
- [nlohmann/json](https://github.com/nlohmann/json) library for handling JSON files

## Future Enhancements

- As I learn Object Oriented Programming, I will implement it in the code, by rewriting the entire code.
- I want to add deep learning for my AI, to make game harder and the AI smarter.

## Acknowledgments

This project was inspired by the classic game "Connect Four." Special thanks to [nlohmann/json](https://github.com/nlohmann/json) for providing the JSON library used in this project.
