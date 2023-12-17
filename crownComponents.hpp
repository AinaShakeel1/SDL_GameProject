#ifndef CROWNCOMPONENTS_HPP
#define CROWNCOMPONENTS_HPP

#include <SDL.h>
#include <SDL_image.h>

class CrownComponents {
public:
    virtual ~CrownComponents() {}

    virtual void create(int x, int y) = 0;
    virtual void draw(SDL_Renderer* renderer, SDL_Texture* assets) = 0;
    virtual const SDL_Rect& getMoverRect() const = 0;
};

#endif // CROWNCOMPONENTS_HPP
