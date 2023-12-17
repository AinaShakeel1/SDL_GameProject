#ifndef FLOWER_HPP
#define FLOWER_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>

class flower {
public:
    flower();
    ~flower();

    void createflower(int x, int y);
    void draw(SDL_Renderer* renderer, SDL_Texture* assets);
    const SDL_Rect& getMoverRect() const;
private:
    SDL_Rect flowerRect;
    SDL_Rect moverRect;
};
#endif // FLOWER_HPP