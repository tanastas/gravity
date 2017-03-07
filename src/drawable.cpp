#include "drawable.hpp"

//initialize static variables
SDL_Renderer* Drawable::dRenderer = NULL;
SDL_Texture* Drawable::dTexture = NULL;
int Drawable::imageWidth = 0;
int Drawable::imageHeight = 0;
int Drawable::scale = 10;

//constructor
Drawable::Drawable(SDL_Rect dSprite, SDL_Rect renderSpace, float velocity) { 
    this->dSprite = dSprite;
    this->renderSpace = renderSpace;
    this->velocity = velocity;
    this->realX = renderSpace.x;
    this->realY = renderSpace.y;
}
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
void Drawable::render() {
    if (dRenderer == NULL) {
        printf("Error rendering: Renderer not set\n");
        return;
    }

    SDL_RenderCopy(dRenderer, dTexture, &dSprite, &renderSpace);
}
//updates drawables position
void Drawable::updatePositionX(float tDelta) {
    realX = realX + tDelta * velocity;
    renderSpace.x = (int) realX;
}
void Drawable::updatePositionY(float tDelta) {
    realY = realY + tDelta * velocity;
    renderSpace.y = (int) realY;
}
//x collision detection
bool Drawable::operator <(const Drawable &rhs) {
    if (renderSpace.x < (rhs.renderSpace.x + rhs.renderSpace.w))
        return true;
    else if ((renderSpace.x + renderSpace.w) > rhs.renderSpace.x)
        return true;
    else
        return false;
}
//y collision detection
bool Drawable::operator >(const Drawable &rhs) {
    if (renderSpace.y < (rhs.renderSpace.y + rhs.renderSpace.l))
        return true;
    else if ((renderSpace.y + renderSpace.w) > rhs.renderSpace.y)
        return true;
    else
        return false;
}
//spritemap width
int Drawable::getImageWidth() { return imageWidth; }
//spritemap height
int Drawable::getImageHeight() { return imageHeight; }
