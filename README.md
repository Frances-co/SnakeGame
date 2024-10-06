# Snake Game - README

## Overview
This is a simple Snake game implemented in C using basic console output. The objective of the game is to navigate the snake around the board, eat apples (represented by 'F'), and grow in size. The game ends if the snake collides with the walls or its own body.

## Game Instructions
- **Movement**: Use the arrow keys or **WASD** to move the snake:
  - Up: Arrow up or W
  - Down: Arrow down or S
  - Left: Arrow left or A
  - Right: Arrow right or D
- **Goal**: Move the snake towards the food (marked as 'F'). Each time the snake eats food, it grows by one segment.
- **Game Over**: The game ends if the snake:
  - Collides with the walls (border of the game board).
  - Collides with its own body.

## How to Run the Game
1. **Platform**: The game is designed to run on **Windows** because it uses `windows.h` for some system-specific functionality like clearing the console and handling keyboard inputs.
2. **Compilation**:
   - Use any C compiler that supports Windows-based development, such as GCC (MinGW) or Microsoft Visual Studio.
   - Compile the program by linking the necessary libraries.
   - Example using GCC (MinGW):
     ```bash
     gcc snake_game.c -o snake_game.exe
     ```
3. **Execution**:
   - Run the compiled executable in a Windows terminal:
     ```bash
     ./snake_game.exe
     ```

## Game Features
- **Dynamic Snake Growth**: Each time the snake eats food, it grows by one segment.
- **Random Apple Placement**: The apples spawn at random locations, avoiding the snake's current position.
- **Game Loop**: The game continuously runs, waiting for player input and updating the board in real time.
- **Death Conditions**: The game ends if the snake runs into the wall or itself.

## Functions Overview
- `Print()`: Displays instructions and starts the game.
- `load()`: Shows a simple loading screen.
- `createBoard()`: Initializes the game board with borders and empty spaces.
- `clearConsole()`: Clears the console to update the game display.
- `printBoard()`: Displays the current state of the game board in the console.
- `drawSnake()`: Draws the snake's body on the board.
- `eraseSnake()`: Erases the snake's previous position before moving.
- `moveSnake()`: Moves the snake based on player input.
- `addSegment()`: Adds a new segment to the snake after eating food.
- `getKeyPressed()`: Detects which key is pressed for movement.
- `appleDropper()`: Randomly places the apple (food) on the board.
- `rip()`: Checks if the snake has collided with the wall or itself, which results in game over.

## Future Enhancements (Optional)
- **Scoring**: Implement a scoring system to display how much food the snake has eaten.
- **Levels**: Add difficulty levels where the snake moves faster as it grows.
- **Pause and Restart**: Add options to pause or restart the game.

## Notes
- **Screen Flickering**: As the game continuously updates the console, there may be some screen flickering, especially in the `clearConsole()` function.
- **Performance**: This is a simple console-based game. The `Sleep()` function is used to control the snake's speed.

Enjoy the game!
