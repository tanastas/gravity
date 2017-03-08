#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Drawable {
public:
    Drawable(SDL_Rect dSprite, SDL_Rect renderSpace, float velocity);
    ~Drawable();

    static void setRenderer(SDL_Renderer* dRenderer);

    static bool loadFromFile( std::string path );

    static void free();

    void render();

    void updatePositionX(float tDelta);
    void updatePositionX(float tDelta, float accel);
   
    void updatePositionY(float tDelta);
    void updatePositionY(float tDelta, float accel);

    bool operator <(const Drawable &rhs); //used for x collision detection
    bool operator >(const Drawable &rhs); //used for y collision detection

    void setX(float);
    void setY(float);
    float getX();
    float getY();
    
  
    static int getImageWidth();
    static int getImageHeight();
    

private:
    static SDL_Renderer* dRenderer;
    static SDL_Texture* dTexture;
    static int imageWidth, imageHeight, scale;

    bool solid;

    float velocity, realX, realY;
    
    SDL_Rect dSprite; //contains sprite x, y coords on spritemap, w, h
    SDL_Rect renderSpace; //contains frame render coords
    
};

#endif /* DRAWABLE_HPP_ */
