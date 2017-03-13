#include "drawable.hpp"
#include <iostream>

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
    this->renderSpace.w = dSprite.w * Drawable::scale;
    this->renderSpace.h = dSprite.h * Drawable::scale;
    this->velocity = velocity;
    this->baseVelocity = velocity;
    this->realX = renderSpace.x;
    this->realY = renderSpace.y;
}

//destructor
Drawable::~Drawable() {
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
        //COLOR KEY CYAN
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
void Drawable::updatePositionX(std::vector<Drawable> &background, std::vector<Drawable> &obstacles, float tDelta) {
    double tempX = realX;
    realX = realX + tDelta * velocity;
    for (auto it = background.begin(); it != background.end(); it++) {
        if (*(this) < *(it)) {
            realX = tempX;
        }
    }
	for (auto it = obstacles.begin(); it != obstacles.end(); it++) {
        if (*(this) < *(it)) {
            realX = tempX;
        }
    }
    renderSpace.x = (int) realX;
}

void Drawable::updatePositionX(std::vector<Drawable> &background, std::vector<Drawable> &obstacles, float tDelta, float accel) {
    double tempX = realX;
    velocity = std::abs(velocity) * accel;
    realX = (int) (realX + tDelta * velocity);

    for (auto it = background.begin(); it != background.end(); it++) {
        if (*(this) < *(it)) {
            realX = tempX;
            velocity = baseVelocity;
        }
    }
    for (auto it = obstacles.begin(); it != obstacles.end(); it++) {
        if (*(this) < *(it) && *(this) > *(it)) {
            realX = tempX;
            velocity = baseVelocity;
        }
    }
    renderSpace.x = (int) realX;
}

void Drawable::updatePositionY(float tDelta) {
    realY = realY + tDelta * velocity;
    renderSpace.y = (int) realY;
}

bool Drawable::updatePositionY(Drawable &player, float tDelta) {
    double tempY = realY;
    realY = realY + tDelta * velocity;
    if (player < *(this) && player > *(this)) {
        realY = tempY;
        return true;
    }
    renderSpace.y = (int) realY;
    return false;
}

bool Drawable::updatePositionY(Drawable &player, float tDelta, float accel) {
    velocity = velocity * accel;
    double tempY = realY;
    realY = realY + tDelta * velocity;
    if (player < *(this) && player > *(this)) {
        realY = tempY;
        return true;
    }
    renderSpace.y = (int) realY;
    return false;
}

//x collision detection
bool Drawable::operator <(Drawable &rhs) {
    float ldLeft = realX;
    float ldRight = realX + renderSpace.w;
    float rdLeft = rhs.realX;
    float rdRight = rhs.realX + rhs.renderSpace.w;
    if (ldLeft <= rdRight  && ldLeft >= rdLeft)
        return true;
    else if (ldRight <= rdRight  && ldRight >= rdLeft)
        return true;
    else
        return false;
}

//y collision detection
bool Drawable::operator >(Drawable &rhs) {
    float ldTop = realY;
    float ldBot = realY + renderSpace.h;
    float rdTop = rhs.realY;
    float rdBot = rhs.realY + rhs.renderSpace.h;
    if (ldTop <= rdBot && ldTop >= rdTop)
        return true;
    else if (ldBot <= rdBot && ldBot >= rdTop)
        return true;
    else if (ldTop <= rdTop && ldBot >= rdBot)
        return true;
    else
        return false;
}

//spritemap width
int Drawable::getImageWidth() { return imageWidth; }

//spritemap height
int Drawable::getImageHeight() { return imageHeight; }

void Drawable::setSprite(SDL_Rect newSprite) {
    this->dSprite = newSprite;
}

void Drawable::setVel(float v) { velocity = v; }

void Drawable::setX(float x){
    renderSpace.x = x; 
    realX = x;
}

void Drawable::setY(float y){
    renderSpace.y = y;
    realY = y;
}

float Drawable::getX(){
    return realX;
}

float Drawable::getY(){
    return realY;
}

int Drawable::getW(){
    return renderSpace.w;
}

int Drawable::getH(){
    return renderSpace.h;
}

int Drawable::getScale() {
    return scale;
}
