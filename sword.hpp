// sword.hpp
#ifndef SWORD_HPP
#define SWORD_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>

class Sword {
public:
    Sword();
    ~Sword();

    void createSword(int x, int y);
    // void update();
    void draw(SDL_Renderer* renderer, SDL_Texture* assets);
    const SDL_Rect& getMoverRect() const;
private:
    SDL_Rect swordRect;
    SDL_Rect moverRect;
//     bool flyingUp;
//     int swordSpeed;
//     int swordSpeedVertical;
};

#endif // sword_hpp