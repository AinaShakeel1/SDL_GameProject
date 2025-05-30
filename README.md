# Mermaid Crown Quest — SDL Game Project

**A C++ SDL2 game created for our Object-Oriented Programming course (Fall 2023)**  
By: Kulsoom Asim, Sara Baloch, Aina Shakeel

---

## Storyline

You play as a mermaid destined to become the queen of the ocean — but to earn your crown, you must prove your worth in a sea full of peril.  
Your goal is to **collect flowers scattered across the screen** while avoiding **dangerous sharks**. Friendly creatures like dolphins swim by peacefully, but if a **shark hits you**, you **lose a life**. Lose all 3 lives and the game is over.

If you collect all the flowers, you earn your **flower crown** and win the game!

---

## Gameplay Features

- Collectible **flowers** for victory
- **3 lives** system shown on screen
- Randomly spawning **sharks** (lose life on collision)
- Friendly **dolphins** that don’t hurt you
- Counter for both flowers collected and lives remaining

---

## OOP Concepts Used

- **Classes** for characters and items:
  - `Mermaid`, `Fish`, `Flower`, `Shark`, `Dolphin`
- **Inheritance & Polymorphism**: Shark and Dolphin classes derive from Fish
- **Operator Overloading** and **Encapsulation**
- Modular structure using `.hpp` and `.cpp` files

---

## Requirements

- C++ Compiler (e.g., MinGW on Windows)
- SDL2 Library
- SDL2_image Library
- (Optional) CMake
- VSCode or other IDE

---

## Manual Compilation (Windows)

Open the folder in VSCode, then open the terminal and run:

g++ *.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

Run the game:

.\a.exe

This is mentioned in How to Compile.txt

⸻

Project Structure

.
├── *.cpp, *.hpp        # Source and headers
├── *.png, *.ttf, *.mp3 # Assets
├── CMakeLists.txt
├── how to compile.txt
├── a.exe               # Windows binary
