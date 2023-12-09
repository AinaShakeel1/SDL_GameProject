// Seashell.cpp
#include "lives.hpp"

Lives::Lives() {
    // Set initial pose and size for the seashell
    livesRect = { 0, 0, 20, 20 };
    moverRect=livesRect;
}

Lives::~Lives() {
    // Destructor (if needed)
}
const SDL_Rect& Lives::getMoverRect() const { // Add Mermaid:: here
    return moverRect;
}
void Lives::createLives(int x, int y) {
    // Create a new heart at the specified position
    livesRect.x = x;
    livesRect.y = y;
    moverRect = livesRect;
}

void Lives::draw(SDL_Renderer* renderer, SDL_Texture* assets) {
    // Draw the hearts
    SDL_RenderCopy(renderer, assets, nullptr, &livesRect);
}
