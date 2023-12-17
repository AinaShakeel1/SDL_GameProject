#ifndef SEASHELL_HPP
#define SEASHELL_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>

#include "crownComponents.hpp"

class Seashell : public CrownComponents {
public:
    Seashell();
    ~Seashell();

    void create(int x, int y) override;
    void draw(SDL_Renderer* renderer, SDL_Texture* assets) override;
    const SDL_Rect& getMoverRect() const override;
private:
    SDL_Rect seashellRect;
    SDL_Rect moverRect;
};

#endif // SEASHELL_HPP
