
#ifndef GAME_HPP_
#define GAME_HPP_

#include <SDL2/SDL.h>
#include <iostream>
#include <map>

#include "resource.hpp"

class Game {
public:
    Game();
    ~Game();
    void init(SDL_Renderer*);
    void renderBG(unsigned int);
private:
    Resource res;
    SDL_Renderer * renderer;
    // both speeds are in px per second
    float side_speed;
    float bg_speed;
    float side_y;
    float bg_y;
};


#endif
