//============================================================================
// Name        : run.cpp
// Author      : 
// Version     :
//============================================================================

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "drawable.hpp"
#include "ai.hpp"
#include "config.cpp"


int main(int argc, char* argv[]){
    // time since last section addition
    int obstDelta = 0;
    // direction of gravity
    float grav = -1.0;
    // Start time
    int startTime;
    // Sides of the bg
    std::vector<Drawable> drawablesBG;
    // Obstacles to avoid
    std::vector<Drawable> drawablesObst;

    // Player drawable
    Drawable player = Drawable(config::playerGLeft,
			       SDL_Rect({config::leftSide.w * config::scale + 1, 500, 0, 0}),
			       config::fgSpeed);
    // Start screen drawable
    Drawable startScreen = Drawable(config::start,
				    SDL_Rect({(config::gameRect.w / 2) - ((config::start.w / 2 )* config::scale) + config::gameRect.x, 10, 0, 0}),
				    0);
    // Background drawable
    Drawable BG = Drawable(config::background,
			   SDL_Rect({config::leftSide.w * config::scale, 0, 0, 0}),
			   config::bgSpeed);
    // SDL Window
    SDL_Window *gWindow = NULL;
    // SDL Renderer
    SDL_Renderer *gRenderer = NULL;
    // Initialise SDL
    SDL_Init(SDL_INIT_VIDEO);
    // AI
    AI ai;
    // Set up the quit boolean
    bool done = false;
    // Starting screen
    bool bStart = true;
    // Set up the event
    SDL_Event event;
    // Time vars
    unsigned int lastTime, currentTime, tDelta;
    // Set up the window
    gWindow = SDL_CreateWindow(
        "Gravity - The Game",              // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        config::width,                     // width, in pixels
        config::height,                    // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    // Left side
    drawablesBG.push_back(Drawable(config::leftSide,
				   SDL_Rect({0, 0, 0, 0}),
				   config::fgSpeed));
    // Right side
    drawablesBG.push_back(Drawable(config::rightSide,
				   SDL_Rect({((config::leftSide.w + config::background.w) * config::scale), 0, 0, 0}),
				   config::fgSpeed));

    //set renderer of drawables
    Drawable::setRenderer(gRenderer);
    //load sprite map
    Drawable::loadFromFile("src/sprite-sheet.png");

    // Check that the window was successfully created
    if (gWindow == NULL) {
        // If not, log error.
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    lastTime = SDL_GetTicks();
    startTime = lastTime;
    while (!done){
        // Start sequence
        currentTime = SDL_GetTicks();
	tDelta = currentTime - lastTime;
	lastTime = currentTime;
	if (bStart) {
		// update sides
		for (auto it = drawablesBG.begin(); it != drawablesBG.end(); it++) {
		    it->updatePositionY(player, tDelta);
		    if (it->getY() > 0.0) {
		        it->setY(it->getY() - config::bgOffset);
		    }
		}
		// Update BG
		BG.updatePositionY(tDelta);
		if (BG.getY() > 0.0) {
		    BG.setY(BG.getY() - config::bgOffset);
		}
		BG.render();
		for (auto it = drawablesBG.begin(); it != drawablesBG.end(); it++) {
		    it->render();
		}
		// obstacles
		for (auto it = drawablesObst.begin(); it != drawablesObst.end(); it++) {
		    it->render();
		}
		player.render();
		// Start screen
		startScreen.render();
		while (SDL_PollEvent(&event)){
		    if(event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE){
			done = true;
		    }
		    else if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE){ 
			bStart = false;
		    }
		}
		SDL_RenderPresent(gRenderer);
		continue;
	}
    	// quit
    	while (SDL_PollEvent(&event)){
	    if(event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE){
                done = true;
    	    }
            else if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE){ 
                //if spacebar is pressed
                // swap gravity and swap player direction
                
                grav = grav * (-1);
                if (grav > 0) {
		    player.setVel(config::fgSpeed);
                    player.setSprite(config::playerGRight);
                }
                else {
		    player.setVel(config::fgSpeed);
                    player.setSprite(config::playerGLeft);
                }
            }
        }
        // Update BG
        BG.updatePositionY(tDelta);
        if (BG.getY() > 0.0) {
	    BG.setY(BG.getY() - config::bgOffset);
        }
	// Add obstacles
	obstDelta += tDelta;
	if (obstDelta > config::obstFreq){
	    // Use AI
	    // return int is added to obstDela
	    obstDelta += ai.addObjects(currentTime, drawablesObst);
	    obstDelta -= config::obstFreq;
	}
	// Update Obstacles
	for (auto it = drawablesObst.begin(); it != drawablesObst.end(); it++) {
	    bool collision = false;
            collision = it->updatePositionY(player, tDelta);
	    if (collision) {
		std::cout << "Game Over!: " << currentTime - startTime << std::endl;
		done = true;
		break;
	    }
	    // remove it out of game. note: gameRect.y == 0
	    if (it->getY() > config::gameRect.h) {
	        drawablesObst.erase(it);
		it--;
	    }
	}
    	// Update player
        player.updatePositionX(drawablesBG, drawablesObst, tDelta, grav * config::gravity);
        //Update Background
	for (auto it = drawablesBG.begin(); it != drawablesBG.end(); it++) {
	    it->updatePositionY(player, tDelta);
	    if (it->getY() > 0.0) {
	        it->setY(it->getY() - config::bgOffset);
	    }
	}
        // clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        // Render objects
        // BG
        BG.render();
        for (auto it = drawablesBG.begin(); it != drawablesBG.end(); it++) {
            it->render();
        }
        // obstacles
        for (auto it = drawablesObst.begin(); it != drawablesObst.end(); it++) {
            it->render();
        }
        // player
        player.render();
        // render display
        SDL_RenderPresent(gRenderer);
    }//end top while loop

    // Close and destroy the window
    SDL_DestroyWindow(gWindow);

    // Clean up
    SDL_Quit();
    return 0;
}
