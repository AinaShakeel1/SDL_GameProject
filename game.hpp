#ifndef GAME_HPP
#define GAME_HPP
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include "KillerFish.hpp"
#include "harmlessfish.hpp"
#include "seashells.hpp"
#include "Mermaid.hpp"
#include "lives.hpp"
#include "sword.hpp"
// #include "endscreen.hpp"

class Game {
public:
    bool init();
    bool loadMedia();
    void close();
    // void endGame();
    
    SDL_Texture* loadTexture(std::string path);
    void run();
    bool checkCollision(const SDL_Rect& rect1, const SDL_Rect& rect2);

private:
    
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 600;

    SDL_Window* gWindow = nullptr;
    SDL_Renderer* gRenderer = nullptr;
    SDL_Texture* gTexture = nullptr;
    // SDL_Texture* gTexture2 = nullptr; //adding this one for end screen
    SDL_Texture* assets = nullptr;
    SDL_Texture* assets2=nullptr;
    SDL_Texture* assets3=nullptr;
    SDL_Texture* assets4=nullptr;
    SDL_Texture* assest5=nullptr;
	SDL_Texture* assest6=nullptr;
    SDL_Texture* gTextureGameOver = nullptr;
    SDL_Texture* gTextureWinningScreen = nullptr;

    int killerFishCollisionCooldown = 3000;
    Uint32 lastKillerFishCollisionTime = 0; 
    

    std::vector<KillerFish> killerFishList;
    std::vector<HarmlessFish>harmlessfishlist;
    std::vector<Seashell> seashellList;
    std::vector<Mermaid> mermaidList;
    std::vector<Lives> livelist;
    std::vector<Sword> swordlist;
   
    Uint32 lastSeashellSpawnTime;
    Uint32 seashellSpawnInterval;

    Uint32 lastSpawnTime;
    Uint32 spawnInterval;

    Uint32 lastswordspawntime;
	Uint32 swordSpawninterval;

    //font
    TTF_Font* yourFont;
};

#endif // GAME_HPP
