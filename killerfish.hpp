// KillerFish.hpp
#ifndef KILLERFISH_HPP
#define KILLERFISH_HPP

#include "fish.hpp"
#include <vector>

class KillerFish : public Fish {
public:
    KillerFish(int x, int y);
    ~KillerFish(); 

    void update(); // Override the virtual functions from the base class
    void drawObjects(SDL_Renderer* renderer, SDL_Texture* assets);
    const SDL_Rect& getMoverRect() const;

private:
    
    int frame;
    void pushToVector();
    std::vector<KillerFish> killerFishList;
};

#endif // KILLERFISH_HPP


