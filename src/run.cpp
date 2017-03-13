//============================================================================
// Name        : SDL2Test.cpp
// Author      : Tristan Anastas
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
// Example program:
// Using SDL2 to create an application window

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "drawable.hpp"


int main(int argc, char* argv[]){
    //scale for screen dimensions
    int scale = 10;
    // obstacle vars
    int obstFreq = 8000;
    int obstDelta = 0;
    //gravity constant
    float grav = -1.025;
    //Rects for our seven sprites
    SDL_Rect leftSide = {2, 2, 4, 97};
    SDL_Rect rightSide = {43, 2, 4, 97};
    SDL_Rect background = {6, 2, 37, 97};
    SDL_Rect playerGLeft = {49, 15, 7, 13};
    SDL_Rect playerGRight = {57, 15, 7, 13};
    SDL_Rect longBox = {49, 2, 24, 10};
    SDL_Rect smallBox = {69, 18, 10, 10};
    SDL_Rect gameRect = {leftSide.w * 10, 0, background.w * 10, background.h * 10};
    std::vector<Drawable> drawablesBG;
    std::vector<Drawable> drawablesObst;

    Drawable player = Drawable(playerGLeft, SDL_Rect({leftSide.w * scale + 1, 400, 0, 0}), 0.05);

    // SDL Window
    SDL_Window *gWindow = NULL;
    // SDL Renderer
    SDL_Renderer *gRenderer = NULL;
    // Initialise SDL
    SDL_Init(SDL_INIT_VIDEO);
    // Set up the quit boolean
    bool done = false;
    // Set up the event
    SDL_Event event;
    // Time vars
    unsigned int lastTime, currentTime, tDelta;
    // Set up the window
    gWindow = SDL_CreateWindow(
        "Gravity - The Game",              // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        450,                               // width, in pixels
        800,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

    // Left side
    drawablesBG.push_back(Drawable(leftSide,
				   SDL_Rect({0, 0, 0, 0}),
				   0.05));
    // Background
    //drawablesBG.push_back(Drawable(background,
	//			   SDL_Rect({leftSide.w * 10, 0, 0, 0}),
	//			   0.025));
    // Right side
    drawablesBG.push_back(Drawable(rightSide,
				   SDL_Rect({((leftSide.w + background.w) * 10), 0, 0, 0}),
				   0.05));

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
    while(!done){
    	// quit
    	while(SDL_PollEvent(&event)){
	        if(event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE){
                done = true;
    	    }
            else if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE){ 
                //if spacebar is pressed
                // swap gravity and swap player direction
                grav = grav * (-1);
                if (grav > 0)
                    player.setSprite(playerGRight);
                else
                    player.setSprite(playerGLeft);
            }
        }
        currentTime = SDL_GetTicks();
	tDelta = currentTime - lastTime;
	lastTime = currentTime;
        //TODO:
        // Update BG
	for (auto it = drawablesBG.begin(); it != drawablesBG.end(); it++) {
	    it->updatePositionY(player, tDelta);
	    // update to start
	    if (it->getY() > 0.0) {
	        it->setY(it->getY() - 60.0);
	    }
	}
	// Add obstacles
	obstDelta += tDelta;
	if (obstDelta > obstFreq){
	    std::cout << "Adding obst!\n";
	    std::cout << "Number of obst: " << drawablesObst.size() << std::endl;
	    // remeber gameRect.y == 0
	    drawablesObst.push_back(Drawable(smallBox,
					     SDL_Rect({gameRect.x, smallBox.h * -10, 0, 0}),
					     0.05));
	    //set renderer of drawables
	    Drawable::setRenderer(gRenderer);
	    //load sprite map
	    Drawable::loadFromFile("src/sprite-sheet.png");
	    obstDelta -= obstFreq;
	}
	// Update Obstacles
	for (auto it = drawablesObst.begin(); it != drawablesObst.end(); it++) {
	    bool collision = it->updatePositionY(player, tDelta);
        if (collision) {
            std::cout << "Game Over!: " << currentTime << std::endl;
            done = true;
            break;
        }
	    // remove it out of game. note: gameRect.y == 0
	    if (it->getY() > gameRect.h ) {
	        drawablesObst.erase(it);
	    }
	}
    	// Update player
        player.updatePositionX(drawablesBG, drawablesObst, tDelta, grav);
        //Update Background
	    for (auto it = drawablesBG.begin(); it != drawablesBG.end(); it++) {
	        it->updatePositionY(player, tDelta);
	        if (it->getY() > 0.0) {
	            it->setY(it->getY() - 60.0);
	        }
	    }
        // Add obstacles
        obstDelta += tDelta;
        if (obstDelta > obstFreq){
            std::cout << "Adding obst!\n";
            // remeber gameRect.y == 0
            drawablesObst.push_back(Drawable(smallBox, SDL_Rect({gameRect.x, smallBox.h * scale * (-1), 0, 0}), 0.05));
            obstDelta -= obstFreq;
        }
        // Update Obstacles
        for (auto it = drawablesObst.begin(); it != drawablesObst.end(); it++) {
            it->updatePositionY(player, tDelta);
            // remove it out of game. note: gameRect.y == 0
            if (it->getY() > gameRect.h ) {
                drawablesObst.erase(it);
            }
        }
        // clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        // Render objects
        // BG
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
        SDL_RenderPresent( gRenderer );
    }//end top while loop

    // Close and destroy the window
    SDL_DestroyWindow(gWindow);

    // Clean up
    SDL_Quit();
    return 0;
}
