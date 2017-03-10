#ifndef RESOURCE_HPP_
#define RESOURCE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <map>

class Sprite {
public:
    Sprite(SDL_Rect, SDL_Texture*);
    ~Sprite();
    void render(int, int, SDL_Renderer*);
    bool operator <(const Sprite &rhs);
private:
    // The rectangle for the given sprite.
    SDL_Rect rect;
    // The sprite sheet with all the sprites.
    SDL_Texture * sheet;
};

class Resource {
    /* All the resources used in the game. (Audio, sprites, anything else...) */
public:
    Resource();
    ~Resource();
    std::map<std::string, Sprite> sprites; 
    void loadResource(SDL_Renderer*);
private:
    SDL_Texture * sheet;
    int w, h;
    std::string ssheet_path;
    std::string slocations_path;
};

#endif
