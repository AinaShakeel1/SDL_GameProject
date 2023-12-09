// Mermaid.hpp
#ifndef MERMAID_HPP
#define MERMAID_HPP

#include "fish.hpp"
#include <vector>
#include <iostream>
#include <SDL.h>
#include "SDL_ttf.h"

class Mermaid : public Fish {
public:
    Mermaid(int x, int y);
    ~Mermaid();

    void handleInput(SDL_Event& e);
    void update();
    void drawObjects(SDL_Renderer* renderer, SDL_Texture* assets);
    void pushToVector();
    const SDL_Rect& getMoverRect() const;

    int getLives() const;
    int getScore() const;

    void decreasedLives();
    void increaseScore(int points);

private:
    int lives;
    int score;
    int speed; // Adjust the speed as needed
    int frameleft; // Current animation frame
    int frameright;
    static std::vector<Mermaid> mermaidList;
};

#endif // MERMAID_HPP
