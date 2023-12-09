// Seashell.cpp
#include "seashells.hpp"

Seashell::Seashell() {
    // Set initial pose and size for the seashell
    seashellRect = { 0, 0, 73, 93 };
    moverRect=seashellRect;
}

Seashell::~Seashell() {
    // Destructor (if needed)
}
const SDL_Rect& Seashell::getMoverRect() const { // Add Mermaid:: here
    return moverRect;
}
void Seashell::createSeashell(int x, int y) {
    // Create a new seashell at the specified position
    seashellRect.x = x;
    seashellRect.y = y;
    moverRect = seashellRect;
}

void Seashell::draw(SDL_Renderer* renderer, SDL_Texture* assets) {
    // Draw the seashell
    SDL_RenderCopy(renderer, assets, nullptr, &seashellRect);
}
