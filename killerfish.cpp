// KillerFish.cpp
#include "killerfish.hpp"
#include <vector>

KillerFish::KillerFish(int x, int y) : Fish(0, rand()%600, 50, 50,201,97), frame(0) {
    // Set initial pose
    srcRect = {201, 97, 49, 39};
}

KillerFish::~KillerFish() {
    // If there's any cleanup needed when a KillerFish object is destroyed, you can put it here.
}
const SDL_Rect& KillerFish::getMoverRect() const { // Add Mermaid:: here
    return moverRect;
}

void KillerFish::update() {
    // Update logic goes here (if needed)
    moverRect.x += 10;

    // Update the frame
    frame = (frame + 1) % 3;

    // Update the vector
   
}

void KillerFish::drawObjects(SDL_Renderer* renderer, SDL_Texture* assets)  {
    // Set srcRect based on the current frame
    if (frame == 1) {
        srcRect = {257, 98, 61, 38};
    } else if (frame == 2) {
        srcRect = {320, 98, 62, 38};
    }

    SDL_RenderCopy(renderer, assets, &srcRect, &moverRect);
}

void KillerFish::pushToVector() {
    // Push the current object to its own vector
    killerFishList.push_back(*this);
}