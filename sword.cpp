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

// void Sword::update(){
//     // Move the sword horizontally
//     moverRect.x += swordSpeed;

//     // Reset to left side if it goes beyond the right boundary
//     if (moverRect.x >= 1000)
//         moverRect.x = 0;

//     // Adjust the flying direction based on the current position
//     if (moverRect.y >= 600) {
//         flyingUp = true; // Start flying upward
//     } else if (moverRect.y <= 0) {
//         flyingUp = false; // Start flying downward
//     }

//     // Update the vertical position based on the flying direction
//     if (flyingUp) {
//         moverRect.y -= swordSpeedVertical;
//     } else {
//         moverRect.y += swordSpeedVertical;
//     }
// }

void Sword::draw(SDL_Renderer* renderer, SDL_Texture* assets) {
    // Draw the seashell
    SDL_RenderCopy(renderer, assets, nullptr, &swordRect);
}