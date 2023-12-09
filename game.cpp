#include "game.hpp"

//#include "HUMania.hpp"

bool Game::init()
{   	
	
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Mermaid Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				Mermaid playerMermaid(500,300);
                mermaidList.push_back(playerMermaid);
				// Create a Mermaid object and add it to the mermaidList
               
			}
		}
		if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
			} 
		else {
				// Load your font
			yourFont = TTF_OpenFont("VT323-Regular.ttf", 24); // Adjust the size as needed

			if (!yourFont) {
					printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
			}
			}
		
	}

	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;
	
	assets = loadTexture("killerfish.png");
	assets2=loadTexture("fish2.png");
	assets3=loadTexture("seashellnew.png");
	assets4=loadTexture("mermaid.png");
	assest5=loadTexture("lives.png");
	assest6=loadTexture("sword.jpg");
    gTexture = loadTexture("underwater.jpg");
	gTextureGameOver = loadTexture("Game Over.png");


	if(assets==NULL || gTexture==NULL || assets2==NULL || assets3==NULL || assets4==NULL || assest5 == NULL || assest6 == NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	
	return success;
}

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(assets);
	SDL_DestroyTexture(assets2);
	SDL_DestroyTexture(assets3);
	SDL_DestroyTexture(assets4);
	SDL_DestroyTexture(assest5);
	SDL_DestroyTexture(assest6);
	assets=NULL;
	assets2=NULL;
	assets3=NULL;
	assets4=NULL;
	assest5=NULL;
	assest6=NULL;
	if (yourFont) {
        TTF_CloseFont(yourFont);
        yourFont = nullptr;
    }

	SDL_DestroyTexture(gTexture);
	SDL_DestroyTexture(gTextureGameOver);
    gTextureGameOver = NULL;

	
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	
}

SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}
bool Game:: checkCollision(const SDL_Rect& rect1, const SDL_Rect& rect2){
	return (
        rect1.x < rect2.x + rect2.w &&
        rect1.x + rect1.w > rect2.x &&
        rect1.y < rect2.y + rect2.h &&
        rect1.y + rect1.h > rect2.y
    );
}

void Game::run( )

{
	//HUMania humania;
	//Mermaid mer(500,300);
	bool quit = false;
	SDL_Event e;

	Uint32 lastkillerspawntime=SDL_GetTicks();
	Uint32 spawnkillerinterval=3000;
	Uint32 lastHarmlessSpawnTime = SDL_GetTicks();
    Uint32 harmlessSpawnInterval = 5000; // Adjust the interval as needed

	lastSeashellSpawnTime = SDL_GetTicks();

	int score=0;

	while( !quit )
	{
		
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}

			Uint32 currenttime=SDL_GetTicks();
			//for shells
			if (currenttime - lastSeashellSpawnTime >= seashellSpawnInterval) {
            lastSeashellSpawnTime = currenttime;

            int x = rand() % SCREEN_WIDTH;
            int y = rand() % SCREEN_HEIGHT;

            Seashell newSeashell;
            newSeashell.createSeashell(x, y);
            seashellList.push_back(newSeashell);

            // Generate a new random interval for the next seashell spawn
            seashellSpawnInterval = rand() % 10000 + 3000; // Random interval between 3000 and 13000 milliseconds
        }

			//killer fish spwans
			 if (currenttime - lastkillerspawntime >= spawnkillerinterval)
			{
				lastkillerspawntime = currenttime;
				int x = rand() % SCREEN_WIDTH;
				int y = rand() % SCREEN_HEIGHT;
				KillerFish newKillerFish(x, y);
				killerFishList.push_back(newKillerFish);
			}

			if (currenttime - lastHarmlessSpawnTime >= harmlessSpawnInterval)
			{
				lastHarmlessSpawnTime = currenttime;
				int x = rand() % SCREEN_WIDTH;
				int y = rand() % SCREEN_HEIGHT;
				HarmlessFish newHarmlessFish(x, y);
				harmlessfishlist.push_back(newHarmlessFish);
			}

			int c=0; //counter for lives
			for (int i=0; i<3; i++){
				Lives heart;
				heart.createLives(910+c, 40);
				livelist.push_back(heart);
				c=c+20;
			}
		
		for (size_t i = 0; i < mermaidList.size(); ++i) {
            mermaidList[i].handleInput(e);
        }
			// Update objects
        for (size_t i = 0; i < killerFishList.size(); ++i)
		{
			killerFishList[i].update();
		}
		for (size_t i = 0; i < harmlessfishlist.size(); ++i)
		{
			harmlessfishlist[i].update();
		}
		// Update the mermaid
        for (size_t i = 0; i < mermaidList.size(); ++i) {
             mermaidList[i].update();
         }

		for (size_t i = 0; i < mermaidList.size(); ++i) {
            for (size_t j = 0; j < killerFishList.size(); ++j) {
              if (checkCollision(mermaidList[i].getMoverRect(), killerFishList[j].getMoverRect())) {
                Uint32 currentTime = SDL_GetTicks();
                  if (currentTime - lastKillerFishCollisionTime >= killerFishCollisionCooldown) {
                    // Sufficient cooldown time has passed, process the collision
                    lastKillerFishCollisionTime = currentTime; // Update the last collision time

                    std::cout << "Collision between Mermaid and KillerFish!\n";
                    // Collision detected, handle it as needed
                    mermaidList[i].decreasedLives();
                    std::cout << "Lives Left:" << mermaidList[i].getLives() << std::endl;
                    if (mermaidList[i].getLives() <= 0)
					{
						SDL_RenderClear(gRenderer);
						SDL_RenderCopy(gRenderer, gTextureGameOver, NULL, NULL);
						SDL_RenderPresent(gRenderer);
						SDL_Delay(5000);  // Adjust the delay as needed
						quit = true;
					}
                 }
             }
         }
     }
		//collision for seashell and mermaid
		for (size_t i = 0; i < mermaidList.size(); ++i) {
			for (size_t j = 0; j < seashellList.size(); ++j) {
				if (checkCollision(mermaidList[i].getMoverRect(), seashellList[j].getMoverRect())) {
					// Collision detected, handle it as needed
					std::cout << "Collision between Mermaid and Seashell!\n";
					// Increment the score
					mermaidList[i].increaseScore(5);
					// Optionally, remove the seashell from the list or mark it as collected
					seashellList.erase(seashellList.begin() + j);
				}
			}
		}
		SDL_RenderClear(gRenderer); //removes everything from renderer
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
		//***********************draw the objects here********************
		
		//drawObjects(gRenderer, assets);
		// humania.drawObjects(gRenderer, assets);

		SDL_Color textColor = {255, 255, 255}; // White color
		std::string scoreText = "Score: " + std::to_string(mermaidList[0].getScore());
		SDL_Surface* textSurface = TTF_RenderText_Solid(yourFont, scoreText.c_str(), textColor);
		SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

		// Assuming SCREEN_WIDTH and SCREEN_HEIGHT are the dimensions of your screen
		int textWidth = textSurface->w;
		int textHeight = textSurface->h;
		SDL_Rect scoreRect = {SCREEN_WIDTH - textWidth - 10, 10, textWidth, textHeight};

		SDL_RenderCopy(gRenderer, scoreTexture, NULL, &scoreRect);

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(scoreTexture);
		// Draw the objects
        for (size_t i = 0; i < killerFishList.size(); ++i)
		{
			killerFishList[i].drawObjects(gRenderer, assets);
		}

// Draw HarmlessFish objects using a traditional for loop
		for (size_t i = 0; i < harmlessfishlist.size(); ++i)
		{
			harmlessfishlist[i].drawObjects(gRenderer, assets2);
		}

		//draw seashells
		// Draw the seashells
        for (size_t i = 0; i < seashellList.size(); ++i) {
            seashellList[i].draw(gRenderer, assets3);
        }
		//drawing mermaid

		for (size_t i = 0; i < mermaidList.size(); ++i)
        {
            mermaidList[i].drawObjects(gRenderer, assets4);
        }

		for (size_t i = 0; i < livelist.size(); i++){
			livelist[i].draw(gRenderer, assest5);
		}

		for (size_t i = 0; i < swordlist.size(); i++){
			swordlist[i].draw(gRenderer, assest6);
		}

		// Handle input for the mermaid
        // for (size_t i = 0; i < mermaidList.size(); ++i) {
        //     mermaidList[i].handleInput(e);
		// 	mermaidList[i].update();
        // }

		//****************************************************************
    	SDL_RenderPresent(gRenderer); //displays the updated renderer

	    SDL_Delay(200);	//causes sdl engine to delay for specified miliseconds
	}
			
}
