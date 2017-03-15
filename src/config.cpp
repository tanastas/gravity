#ifndef CONFIG
#define CONFIG

#include <SDL2/SDL.h>

namespace config {
    // game width
    static int width = 450;
    // game height
    static int height = 800;
    // Scale to enlarge sprites
    static int scale = 10;
    // bg offset
    static int bgOffset = 60;
    // forground speed
    static float fgSpeed = .2;
    // background speed
    static float bgSpeed = .1;
    // obst frequency (how long to wait to add another section)
    static int obstFreq = 1000;
    // Gravity (acceleration for player only)
    static float gravity = 1.025;
    // start sprite
    static SDL_Rect start = {49, 47, 33, 26};
     // left side sprite rect
    static SDL_Rect leftSide = {2, 2, 4, 97};
    // right side sprite rect
    static SDL_Rect rightSide = {43, 2, 4, 97};
    // BG sprite
    static SDL_Rect background = {6, 2, 37, 97};
    // player gravity left
    static SDL_Rect playerGLeft = {49, 15, 7, 13};
    // plater gravity right
    static SDL_Rect playerGRight = {57, 15, 7, 13};
    // long box sprite
    static SDL_Rect longBox = {49, 2, 24, 10};
    // small box
    static SDL_Rect smallBox = {69, 18, 10, 10};
    // the game portion rectangle
    static SDL_Rect gameRect = {leftSide.w * scale,
				0,
				background.w * scale,
				height};
}



#endif /* CONFIG */

