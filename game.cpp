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
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
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
	assest6=loadTexture("sword.png");
	asset7=loadTexture("flower.png");
    gTexture = loadTexture("underwater.jpg");
	gTextureGameOver = loadTexture("Game Over.png");
	gTextureWinningScreen = loadTexture("WinningScreen.png");
	gTextureGameStart = loadTexture("Game Start.png");

	if(assets==NULL || gTexture==NULL || assets2==NULL || assets3==NULL || assets4==NULL || assest5 == NULL || assest6 == NULL || asset7==NULL || gTextureWinningScreen == NULL || gTextureGameOver == NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	backgroundMusic = Mix_LoadMUS("Sakura-Girl-Beach-chosic.com_.mp3"); 
	 if (!backgroundMusic) {
        printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    } else {
        // Play the background music in a loop (-1 means loop indefinitely)
        Mix_PlayMusic(backgroundMusic, -1);
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
	SDL_DestroyTexture(asset7);
	assets=NULL;
	assets2=NULL;
	assets3=NULL;
	assets4=NULL;
	assest5=NULL;
	assest6=NULL;
	asset7=NULL;
	if (yourFont) {
        TTF_CloseFont(yourFont);
        yourFont = nullptr;
    }
	Mix_FreeMusic(backgroundMusic);
	backgroundMusic = nullptr;

	SDL_DestroyTexture(gTexture);
	SDL_DestroyTexture(gTextureGameOver);
	SDL_DestroyTexture(gTextureWinningScreen);
	SDL_DestroyTexture(gTextureGameStart);
    gTextureGameOver = NULL;
	gTextureWinningScreen = NULL;
	gTextureGameStart = NULL;
	
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

void Game::run( )

{
	bool quit = false;
	SDL_Event e;

	Uint32 lastkillerspawntime=SDL_GetTicks();
	Uint32 spawnkillerinterval=3000;
	Uint32 lastHarmlessSpawnTime = SDL_GetTicks();
    Uint32 harmlessSpawnInterval = 5000; // Adjust the interval as needed
	Uint32 lastswordspawntime= SDL_GetTicks();
	Uint32 swordSpawninterval = 5000;
	lastflowerSpawnTime=SDL_GetTicks();
	lastSeashellSpawnTime = SDL_GetTicks();

	bool collected = false;


	int c=0; //counter for lives
	bool removelife;
	for (int i=0; i<mermaidList[0].getLives(); i++)
	{
		Lives heart;
		heart.createLives(910+c, 40);
		livelist.push_back(heart);
		c=c+20;
	}
	
	// variable to track whether the game is in the start state
	bool inStartScreen = true;

	while( !quit )
	{
		
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			// Check if the user clicks on the start screen
            if (inStartScreen && e.type == SDL_MOUSEBUTTONDOWN)
            {
                // Transition to the main game loop
                inStartScreen = false;
            }
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}
			// Render the start screen if still in the start state
        if (inStartScreen)
        {
            // Draw the start screen texture
            SDL_RenderCopy(gRenderer, gTextureGameStart, NULL, NULL);
            // Present the renderer
            SDL_RenderPresent(gRenderer);
            // Continue to the next iteration of the game loop
            continue;
        }
			Uint32 currenttime=SDL_GetTicks();
			//for shells
			if (currenttime - lastSeashellSpawnTime >= seashellSpawnInterval) {
            lastSeashellSpawnTime = currenttime;

			const int seashellPadding = 100; // Adjust the padding as needed
            int x = rand() % (SCREEN_WIDTH-50);
            int y = rand() % (SCREEN_HEIGHT-50);

            Seashell newSeashell;
            newSeashell.createSeashell(x, y);
            seashellList.push_back(newSeashell);

            // Generate a new random interval for the next seashell spawn
            seashellSpawnInterval = rand() % 10000 + 3000;
        }
		//for flowers
		if (currenttime - lastflowerSpawnTime >= flowerSpawnInterval) {
		lastflowerSpawnTime = currenttime;

		int x = rand() % (SCREEN_WIDTH-50);
        int y = rand() % (SCREEN_HEIGHT-50);

		flower newFlower;
		newFlower.createflower(x, y);
		flowerlist.push_back(newFlower);

		// Generate a new random interval for the next flower spawn
		flowerSpawnInterval = rand() % 10000 + 3000;
	}
		//killer fish spwans
			if (currenttime - lastkillerspawntime >= spawnkillerinterval)
		{
			lastkillerspawntime = currenttime;
			int x = rand() % (SCREEN_WIDTH-50);
            int y = rand() % (SCREEN_HEIGHT-100);
			KillerFish newKillerFish(x, y);
			killerFishList.push_back(newKillerFish);
		}

		if (currenttime - lastHarmlessSpawnTime >= harmlessSpawnInterval)
		{
			lastHarmlessSpawnTime = currenttime;
			int x = rand() % (SCREEN_WIDTH-50);
            int y = rand() % (SCREEN_HEIGHT-50);
			HarmlessFish newHarmlessFish(x, y);
			harmlessfishlist.push_back(newHarmlessFish);
		}

		if (mermaidList[0].getScore()>=20){
			if (currenttime - lastswordspawntime >= swordSpawninterval) 
			{
				lastswordspawntime = currenttime;
				int x = rand() % (SCREEN_WIDTH-50);
            	int y = rand() % (SCREEN_HEIGHT-50);

				Sword sword;
				sword.createSword(x, y);
				swordlist.push_back(sword);

				// Generate a new random interval for the next seashell spawn
				swordSpawninterval = rand() % 10000 + 30000; // Random interval between 1 and 5 mins (these are miliseconds)
			}
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

		// //update the sword object
		// for (size_t i = 0; i < swordlist.size(); i++) {
    	// 	swordlist[i].update();
		// }

		if (mermaidList[0].getScore() >= 100) {
            SDL_RenderClear(gRenderer);
            SDL_RenderCopy(gRenderer, gTextureWinningScreen, NULL, NULL);
            SDL_RenderPresent(gRenderer);
            SDL_Delay(5000);  // Adjust the delay as needed
            quit = true;
        }

		for (size_t i = 0; i < mermaidList.size(); ++i) {
            for (size_t j = 0; j < killerFishList.size(); ++j) {
              if (mermaidList[i].checkCollision(mermaidList[i].getMoverRect(), killerFishList[j].getMoverRect())) {
                Uint32 currentTime = SDL_GetTicks();
                  if (currentTime - lastKillerFishCollisionTime >= killerFishCollisionCooldown) {
                    // Sufficient cooldown time has passed, process the collision
                    lastKillerFishCollisionTime = currentTime; // Update the last collision time

                    std::cout << "Collision between Mermaid and KillerFish!\n";
                    // Collision detected, handle it as needed
					if (collected == false){
                    mermaidList[i].decreasedLives();
					// Remove a life from the livelist
                    killerFishList.erase(killerFishList.begin() + j);
					livelist.pop_back(); //erase the last element
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
					else if (collected == true){
						killerFishList.erase(killerFishList.begin() + j);
						mermaidList[i].increaseScore(15);
						collected = false;
					}
                 }
             }
         }
    }
		//collision for seashell and mermaid
		for (size_t i = 0; i < mermaidList.size(); ++i) {
			for (size_t j = 0; j < seashellList.size(); ++j) {
				if (mermaidList[i].checkCollision(mermaidList[i].getMoverRect(), seashellList[j].getMoverRect())) {
					// Collision detected, handle it as needed
					std::cout << "Collision between Mermaid and Seashell!\n";
					// Increment the score
					mermaidList[i] += 5;
					// Optionally, remove the seashell from the list or mark it as collected
					seashellList.erase(seashellList.begin() + j);
				}
			}
		}
		//collision for flower and mermaid
		for (size_t i = 0; i < mermaidList.size(); ++i) {
			for (size_t j = 0; j < flowerlist.size(); ++j) {
				if (mermaidList[i].checkCollision(mermaidList[i].getMoverRect(), flowerlist[j].getMoverRect())) {
					// Collision detected, handle it as needed
					std::cout << "Collision between Mermaid and Seashell!\n";
					// Increment the score
					mermaidList[i] += 1;
					// Optionally, remove the seashell from the list or mark it as collected
					flowerlist.erase(flowerlist.begin() + j);
				}
			}
		}
		//collision for sword and mermaid
		if (!swordlist.empty()) {
    		if (mermaidList[0].checkCollision(mermaidList[0].getMoverRect(), swordlist[0].getMoverRect())) {
				std::cout << "Collision between Mermaid and Sword!\n";
				// Handle the collision between the mermaid and the sword here
				// For example: mermaidList[0].handleSwordCollision();
				// Remove the sword from the list
				swordlist.clear();
				collected = true;
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
		 for (size_t i = 0; i < flowerlist.size(); ++i) {
            flowerlist[i].draw(gRenderer, asset7);
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
