//============================================================================
// Name        : SDL2Test.cpp
// Author      : Tristan Anastas
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
// Example program:
// Using SDL2 to create an application window

#include "SDL.h"
#include <iostream>


int main(int argc, char* argv[]){

	/* Initialise what is needed.
	 * */
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
    // Set up the window
    gWindow = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

    // Check that the window was successfully created
    if (gWindow == NULL) {
        // In the case that the window could not be made...
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    while( !done ){
    	// check events
    	while(SDL_PollEvent(&event)){
    		if(event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE){
    			done = true;
    		}
    	}
    	// do calculations

    	// clear screen
    	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    	SDL_RenderClear( gRenderer );
    	// render display
    	SDL_RenderPresent( gRenderer );
    }

    // Close and destroy the window
    SDL_DestroyWindow(gWindow);

    // Clean up
    SDL_Quit();
    return 0;
}
