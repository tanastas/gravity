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

#include "resource.hpp"
#include "game.hpp"


int main(int argc, char* argv[]){
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
    // Resources
    Game game;
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

    // Check that the window was successfully created
    if (gWindow == NULL) {
        // If not, log error.
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    // Load resources
    game = Game();
    game.init(gRenderer);
    lastTime = SDL_GetTicks();
    while(!done){
    	// quit
    	while(SDL_PollEvent(&event)){
	    if(event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE){
      		done = true;
    	    }
	    // Get user commands here ...
    	}
    	// Update player
	// Update objects (player + map)

	// TODO give render its own function
	currentTime = SDL_GetTicks();
	tDelta = currentTime - lastTime;
	lastTime = currentTime;
    	// clear screen
    	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    	SDL_RenderClear( gRenderer );
    	// render display
	game.renderBG(tDelta);
    	SDL_RenderPresent( gRenderer );
    }

    // Close and destroy the window
    SDL_DestroyWindow(gWindow);

    // Clean up
    SDL_Quit();
    return 0;
}
