#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <string>
#include "SDL.h"
#include "SDL_image.h"

class Drawable {
public:
    Drawable(SDL_Rect dSprite);
    ~Drawable();

    static void setRenderer(SDL_Renderer* dRenderer);

    static bool loadFromFile( std::string path );

	static void free();

	void render( int x, int y, SDL_Rect* sprite = NULL );

    static int getImageWidth();
    static int getImageHeight();
    

private:
    static SDL_Renderer* dRenderer = NULL;
    static SDL_Texture* dTexture = NULL;
    static int imageWidth = 0, imageHeight = 0;

    SDL_Rect dSprite; //contains sprite x, y coords on spritemap, w, h
    
}

#endif /* DRAWABLE_HPP_ */
