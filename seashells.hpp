// Seashell.hpp
#ifndef SEASHELL_HPP
#define SEASHELL_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>

class Seashell {
public:
    Seashell();
    ~Seashell();

    void createSeashell(int x, int y);
    void draw(SDL_Renderer* renderer, SDL_Texture* assets);
    const SDL_Rect& getMoverRect() const;
private:
    SDL_Rect seashellRect;
    SDL_Rect moverRect;
};

#endif // SEASHELL_HPP
