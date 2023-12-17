#include "flower.hpp"

flower::flower() {
    // Set initial pose and size for the flower
    flowerRect = { 4, 30, 50, 50 };
    moverRect = flowerRect;
}

flower::~flower() {
    // Destructor (if needed)
}

void flower::create(int x, int y) {
    // Create a new flower at the specified position
    flowerRect.x = x;
    flowerRect.y = y + 90;
    moverRect = flowerRect;
}

void flower::draw(SDL_Renderer* renderer, SDL_Texture* assets) {
    // Draw the flower
    SDL_RenderCopy(renderer, assets, nullptr, &moverRect);
}

const SDL_Rect& flower::getMoverRect() const {
    return moverRect;
}
