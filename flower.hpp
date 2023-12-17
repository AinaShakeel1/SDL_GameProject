#ifndef FLOWER_HPP
#define FLOWER_HPP

#include "crownComponents.hpp"

class flower : public CrownComponents {
public:
    flower();
    ~flower();

    void create(int x, int y) override;
    void draw(SDL_Renderer* renderer, SDL_Texture* assets) override;
    const SDL_Rect& getMoverRect() const override;
private:
    SDL_Rect flowerRect;
    SDL_Rect moverRect;
};

#endif // FLOWER_HPP
