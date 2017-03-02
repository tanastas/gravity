#include "resource.hpp"

Resource::Resource(){
    this->ssheet_path = "src/sprite-sheet.png";
    this->slocations_path = "src/sprite-sheet.txt";

    this->sprites = std::map<std::string, Sprite>();
    this->sheet = NULL;
}

Resource::~Resource(){
}

void Resource::loadResource(SDL_Renderer * renderer){
    // Create surface from img
    SDL_Surface * surface = IMG_Load(this->ssheet_path.c_str());  
    // Check surface
    if (surface == NULL) {
        std::cout << "Error opening sprite sheet." << std::endl;
	return;
    }
    // Loaded the sheet
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
    // Create the texture
    this->sheet = SDL_CreateTextureFromSurface(renderer, surface);
    // Check texture
    if (this->sheet == NULL) {
        std::cout << "Unable to create texture for sprite sheet." << std::endl;
	return;
    }
    // Sprite sheet dimensions
    w = surface->w;
    h = surface->h;
    // Free the surface
    SDL_FreeSurface(surface);

    // Now load the sprites
    SDL_Rect rect;
    std::ifstream locationsFile;
    std::string name;
    // Open location file
    locationsFile.open(this->slocations_path);
    // File is open
    if (locationsFile.is_open()) {
	locationsFile >> name;
        while (!locationsFile.eof()) {
	    locationsFile >> rect.x >> rect.y >> rect.w >> rect.h;
	    // add the sprite
	    Sprite sprite = Sprite(rect, this->sheet);
	    std::cout << name << std::endl;
	    this->sprites.insert(std::make_pair(name, sprite));
	    // Get next name
	    locationsFile >> name;
        }
	for (auto ii = this->sprites.begin(); ii != this->sprites.end(); ii++) {
	    std::cout << ii->first << std::endl;
	}
	// Close the file
	locationsFile.close();
    } else {
        std::cout << "Error, could not open sprite location file." << std::endl;
	// Set the Texture to Null, (sprites not available)
	this->sheet = NULL;
	return;
    }
}

/*
  Sprite class
*/

Sprite::Sprite(SDL_Rect rect, SDL_Texture * sheet) {
    // Constructor for Sprite Class
    this->rect = rect;
    this->sheet = sheet;
}

Sprite::~Sprite() {

}

void Sprite::render(int x, int y, SDL_Renderer * renderer) {
    // Zoom for the display
    int zoom = 10;
    // Create the display rect
    SDL_Rect rrect = {x, y, this->rect.w*zoom, this->rect.h*zoom};
    // Copy clip to display rext
    SDL_RenderCopy(renderer, this->sheet, &this->rect, &rrect);
    return;
}

bool Sprite::operator <(const Sprite &rhs){
    if (rhs.rect.x > this->rect.x)
    {
        return true;
    } else {
        return false;
    }
}
