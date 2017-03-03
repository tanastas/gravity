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
    
    bool operator <(const Drawable &rhs); //used for x collision detection
    bool operator >(const Drawable &rhs); //used for y collision detection

    static int getImageWidth();
    static int getImageHeight();
    

private:
    static SDL_Renderer* dRenderer;
    static SDL_Texture* dTexture;
    static int imageWidth, imageHeight;

    SDL_Rect dSprite; //contains sprite x, y coords on spritemap, w, h
    SDL_Rect renderSpace; //contains frame render coords
    
};

#endif /* DRAWABLE_HPP_ */
