#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>

class Lives {
public:
    Lives();
    ~Lives();

    void createLives(int x, int y);
    void draw(SDL_Renderer* renderer, SDL_Texture* assets);
    const SDL_Rect& getMoverRect() const;
private:
    SDL_Rect livesRect;
    SDL_Rect moverRect;
};