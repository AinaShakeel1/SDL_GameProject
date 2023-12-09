// Mermaid.hpp
#ifndef MERMAID_HPP
#define MERMAID_HPP

#include "fish.hpp"
#include <iostream>
#include <SDL.h>

class Mermaid : public Fish {
public:
    Mermaid(int x, int y);
    ~Mermaid();

    void handleInput(SDL_Event& e);
    void update();
    void drawObjects(SDL_Renderer* renderer, SDL_Texture* assets);
    void pushToVector();
    const SDL_Rect& getMoverRect() const;

private:
    int speed; // Adjust the speed as needed
    int frameleft; // Current animation frame
    int frameright;
    std::vector<Mermaid> mermaidList;
};

#endif // MERMAID_HPP
