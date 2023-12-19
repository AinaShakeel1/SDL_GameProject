#include "Mermaid.hpp"

std::vector<Mermaid> Mermaid::mermaidList;

Mermaid::Mermaid(int x, int y) : Fish(x, y, 51, 29, 3, 104), frameleft(0), lives(3), score(0) {
    // Set initial pose or any other initialization logic
    srcRect = {3, 104, 51, 28};
    speed = 40; // Adjust the speed as needed
}

Mermaid::~Mermaid() {
    // Cleanup if necessary
}

int Mermaid::getLives() const {
    return lives;
}

int Mermaid::getScore() const {
    return score;
}

void Mermaid::decreasedLives() {
    if(lives > 0) 
        lives--;
}

void Mermaid::increaseScore(int points) {
    score += points;
}

const SDL_Rect& Mermaid::getMoverRect() const { // Add Mermaid:: here
    return moverRect;
}

void Mermaid::handleInput(SDL_Event& e) {
    // Handle input events for movement
    if (e.type == SDL_KEYDOWN) {
        int newPosX = moverRect.x;
        int newPosY = moverRect.y;

        if (e.key.keysym.sym == SDLK_UP) {
            newPosY -= speed;
        } 
        if (e.key.keysym.sym == SDLK_DOWN) {
            newPosY += speed;
        }
        if (e.key.keysym.sym == SDLK_LEFT) {
            newPosX -= speed;
            frameleft = 0;
        }
        if (e.key.keysym.sym == SDLK_RIGHT) {
            newPosX += speed;
            frameleft = 1;
        }

        // Check if the new position is within the screen boundaries
        if (newPosX >= 0 && newPosX + moverRect.w <= 1000 &&
            newPosY >= 0 && newPosY + moverRect.h <= 600) {
            // Update the position only if within boundaries
            moverRect.x = newPosX;
            moverRect.y = newPosY;
        }
    }
}
void Mermaid::update() {
    // Update logic for the mermaid (if needed)

    // Update the frame for animation
    const Uint32 animationSpeed = 300; // milliseconds per frame
    frameright = int(((SDL_GetTicks() / animationSpeed) % 3));

    // Set srcRect based on the current frame and direction
    if (frameleft == 0) {
        // Facing left
        srcRect = {2 + frameright * 53, 58, 53, 29};
    } else {
        // Facing right
        srcRect = {3 + frameright * 53, 104, 51, 28};
    }
    std::cout << "frameright: " << frameright << ", frameleft: " << frameleft << ", srcRect.x: " << srcRect.x << std::endl;
}
bool Mermaid:: checkCollision(const SDL_Rect& rect1, const SDL_Rect& rect2){
	return (
        rect1.x < rect2.x + rect2.w &&
        rect1.x + rect1.w > rect2.x &&
        rect1.y < rect2.y + rect2.h &&
        rect1.y + rect1.h > rect2.y
    );
}
Mermaid& Mermaid::operator+=(int points) {
    this->score += points;
    return *this;
}

void Mermaid::drawObjects(SDL_Renderer* renderer, SDL_Texture* assets) {
    // Set srcRect based on the current frame

    if (frameleft == 0) {
        // Mermaid facing left
        srcRect = { 114, 58, 53, 29 };
    } else {
        // Mermaid facing right
        srcRect = { 3, 104, 51, 28 };
    }

    // Draw logic goes here
    SDL_RenderCopy(renderer, assets, &srcRect, &moverRect);
}
void Mermaid::pushToVector() {
    // Push the current object to its own vector
     mermaidList.push_back(*this);
}