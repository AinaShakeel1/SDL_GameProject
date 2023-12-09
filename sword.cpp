// sword.cpp
#include "sword.hpp"

Sword::Sword() {
    // Set initial pose and size for the seashell
    seashellRect = { 0, 0, 73, 93 };
    moverRect=seashellRect;
}

Sword::~Seashell() {
    // Destructor (if needed)
}
const SDL_Rect& Sword::getMoverRect() const { // Add Mermaid:: here
    return moverRect;
}
void Sword::createSword(int x, int y) {
    // Create a new seashell at the specified position
    seashellRect.x = x;
    seashellRect.y = y;
    moverRect = seashellRect;
}

void Sword::draw(SDL_Renderer* renderer, SDL_Texture* assets) {
    // Draw the seashell
    SDL_RenderCopy(renderer, assets, nullptr, &seashellRect);
}