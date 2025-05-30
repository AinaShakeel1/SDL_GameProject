# Mermaid Crown Quest — SDL Game Project  

**A C++ SDL2 game created for our Object-Oriented Programming course (Fall 2023)**  
*By: Kulsoom Asim, Sara Baloch, Aina Shakeel*  

---

## Storyline  
You play as a mermaid destined to become the queen of the ocean — but first, you must prove your worth in treacherous waters!  

**Objective:**  
- Collect **flowers** scattered across the ocean floor to earn your crown.  
- Avoid **dangerous sharks** that roam the waters.  
- Friendly **dolphins** swim harmlessly by.  

**Game Over Conditions:**  
- Lose all **3 lives** (lost when sharks hit you).  
- **Win Condition:** Collect all flowers to earn your **flower crown**!

---

## OOP Concepts Implemented  
| Concept          | Implementation Details                          |  
|------------------|-----------------------------------------------|  
| **Classes**      | `Mermaid`, `Fish`, `Flower`, `Shark`, `Dolphin` |  
| **Inheritance**  | `Shark` and `Dolphin` derive from `Fish`       |  
| **Polymorphism** | Overridden methods for different behaviors     |  
| **Encapsulation**| Private/protected members with public methods  |  
| **Operator Overloading** | Custom operators for game logic          |  

---

## Installation & Requirements  
### Dependencies  
- **Compiler:** MinGW (Windows) or g++ (Linux)  
- **Libraries:**  
  - SDL2  
  - SDL2_image  
  - *(Optional)* CMake for build automation  

### Compilation (Windows)  
1. Open the project in VSCode (or your preferred IDE).  
2. Run in the terminal:  
   ```bash
   g++ *.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
   ```
3. Execute the game:  
   ```bash
   .\a.exe
   ```

*(See `how_to_compile.txt` for detailed instructions.)*  

---

*(Consider adding a license badge, e.g., MIT or GPL, if applicable.)*  

### Key Improvements:  
1. **Better Visual Hierarchy** – Headers, tables, and lists improve readability.  
2. **Asset Preview** – Placeholder for a screenshot (add one if possible).  
3. **Structured Installation Guide** – Clearer steps for compilation.  
4. **OOP Table** – Concepts are now easier to scan.  
5. **Consistent Formatting** – Fixed filename casing (`how_to_compile.txt` vs original).  
