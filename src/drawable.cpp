#include "drawable.hpp"

//initialize static variables
SDL_Renderer* Drawable::dRenderer = NULL;
SDL_Texture* Drawable::dTexture = NULL;
int Drawable::imageWidth = 0;
int Drawable::imageHeight = 0;

//constructor
Drawable::Drawable(SDL_Rect dSprite) { this->dSprite = dSprite; }
//destructor
Drawable::~Drawable() {
    free();
}
//sets static renderer
void Drawable::setRenderer(SDL_Renderer* renderer) { dRenderer = renderer; }
//loads spritemap
bool Drawable::loadFromFile(std::string path) {
    free(); //clear pre-loaded image
    SDL_Surface* loadedImage = IMG_Load(path.c_str());
    SDL_Texture* finalTexture = NULL;
    
    if (loadedImage == NULL) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else {
        SDL_SetColorKey( loadedImage, SDL_TRUE, SDL_MapRGB( loadedImage->format, 0, 0xFF, 0xFF ) );
        finalTexture = SDL_CreateTextureFromSurface(dRenderer, loadedImage);

        if ( finalTexture == NULL ) {
             printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else {
			//Get image dimensions
			imageWidth = loadedImage->w;
			imageHeight = loadedImage->h;
		}

    SDL_FreeSurface(loadedImage);

    }
    //sets the actual static member
    dTexture = finalTexture;
    return dTexture != NULL;
}
//clears dTexture
void Drawable::free() {
    if (dTexture != NULL) {
        SDL_DestroyTexture(dTexture);
        dTexture = NULL;
        imageWidth = 0;
        imageHeight = 0;
    }
}
//renders a sprite from dTexture to x, y in frame
void Drawable::render(int x, int y) {
    if (dRenderer == NULL) {
        printf("Error rendering: Renderer not set\n");
        return;
    }
    //scale for display
    int scale = 10;

    renderSpace.x = x;
    renderSpace.y = y;

    renderSpace.w = dSprite.w * scale;
    renderSpace.h = dSprite.h * scale;

    SDL_RenderCopy(dRenderer, dTexture, &dSprite, &renderSpace);
}
//x collision detection
bool Drawable::operator <(const Drawable &rhs) {
    if (dSprite.x < (rhs.dSprite.x + rhs.dSprite.w))
        return true;
    else if ((dSprite.x + dSprite.w) > rhs.dSprite.x)
        return true;
    else
        return false;
}
//y collision detection
bool Drawable::operator >(const Drawable &rhs) {
    if (dSprite.y < (rhs.dSprite.y + rhs.dSprite.l))
        return true;
    else if ((dSprite.y + dSprite.w) > rhs.dSprite.y)
        return true;
    else
        return false;
}
//spritemap width
int Drawable::getImageWidth() { return imageWidth; }
//spritemap height
int Drawable::getImageHeight() { return imageHeight; }
