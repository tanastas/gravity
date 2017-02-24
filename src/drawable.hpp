#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "SDL.h"
#include "SDL_image.h"

class Drawable {
public:
    Drawable(); //TODO: arguments??
    ~Drawable();

    bool loadFromFile( std::string path );

	void free();

	void render( int x, int y, SDL_Rect* sprite = NULL );

    int getImageWidth();
    int getImageHeight();
    

private:
    SDL_Renderer* dRenderer
    SDL_Texture* dTexture;

    SDL_Rect dSprite; //contains sprite x, y coords on spritemap, w, h
    
    int imageWidth, imageHeight;
}

#endif /* DRAWABLE_HPP_ */
