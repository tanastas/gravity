#include "drawable.hpp"

SDL_Renderer* Drawable::dRenderer = NULL;
SDL_Texture* Drawable::dTexture = NULL;
int Drawable::imageWidth = 0;
int Drawable::imageHeight = 0;

Drawable::Drawable(SDL_Rect dSprite) { this->dSprite = dSprite; }

Drawable::~Drawable() {
    free();
}

void Drawable::setRenderer(SDL_Renderer* renderer) { dRenderer = renderer; }

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

    dTexture = finalTexture;
    return dTexture != NULL;
}

void Drawable::free() {
    if (dTexture != NULL) {
        SDL_DestroyTexture(dTexture);
        dTexture = NULL;
        imageWidth = 0;
        imageHeight = 0;
    }
}

void Drawable::render(int x, int y, SDL_Rect* sprite) {
    SDL_Rect renderSpace = {x, y, imageWidth, imageHeight};

    if (sprite != NULL) {
        renderSpace.w = sprite->w;
        renderSpace.h = sprite->h;
    }
    SDL_RenderCopy(dRenderer, dTexture, sprite, &renderSpace);
}

int Drawable::getImageWidth() { return imageWidth; }

int Drawable::getImageHeight() { return imageHeight; }
