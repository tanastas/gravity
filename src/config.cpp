#ifndef CONFIG
#define CONFIG

#include <SDL2/SDL.h>

namespace config {
    // game width
    const int width = 450;
    // game height
    const int height = 800;
    // Scale to enlarge sprites
    const int scale = 10;
    // bg offset
    const int bgOffset = 120;
    // forground speed
    const float fgSpeed = .3;
    // background speed
    const float bgSpeed = .15;
    // obst frequency (how long to wait to add another section)
    const int obstFreq = 1000;
    // Gravity (acceleration for player only)
    const float gravity = 1.025;
    // start sprite
    const SDL_Rect start = {49, 47, 33, 26};
     // left side sprite rect
    const SDL_Rect leftSide = {2, 2, 4, 97};
    // right side sprite rect
    const SDL_Rect rightSide = {43, 2, 4, 97};
    // BG sprite
    const SDL_Rect background = {6, 2, 37, 97};
    // player gravity left
    const SDL_Rect playerGLeft = {49, 15, 7, 13};
    // plater gravity right
    const SDL_Rect playerGRight = {57, 15, 7, 13};
    // long box sprite
    const SDL_Rect longBox = {49, 2, 24, 10};
    // small box
    const SDL_Rect smallBox = {69, 18, 10, 10};
    // the game portion rectangle
    const SDL_Rect gameRect = {leftSide.w * scale,
			       0,
			       background.w * scale,
			       height};
}


#endif /* CONFIG */

