// sword.cpp
#include "sword.hpp"

Sword::Sword() {
    // Set initial pose and size for the seashell
    swordRect = { 0, 0, 73, 73 };
    moverRect=swordRect;
}

Sword::~Sword() {
    // Destructor (if needed)
}
const SDL_Rect& Sword::getMoverRect() const { // Add Mermaid:: here
    return moverRect;
}
void Sword::createSword(int x, int y) {
    // Create a new seashell at the specified position
    swordRect.x = x;
    swordRect.y = y;
    moverRect = swordRect;
}

void Sword::draw(SDL_Renderer* renderer, SDL_Texture* assets) {
    // Draw the seashell
    SDL_RenderCopy(renderer, assets, nullptr, &swordRect);
}