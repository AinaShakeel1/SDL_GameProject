

#include "flower.hpp"

flower::flower() {
    // Set initial pose and size for the seashell
    flowerRect = { 4, 30, 50, 50 };
    moverRect=flowerRect;
}

flower::~flower() {
    // Destructor (if needed)
}
const SDL_Rect& flower::getMoverRect() const { // Add Mermaid:: here
    return moverRect;
}
void flower::createflower(int x, int y) {
    // Create a new flower at the specified position
    flowerRect.x = x;
    flowerRect.y = y + 90;
    moverRect = flowerRect;
}

void flower::draw(SDL_Renderer* renderer, SDL_Texture* assets) {
    // Draw the seashell
    SDL_RenderCopy(renderer, assets, nullptr, &moverRect);
}