#include "ai.hpp"


AI::AI(){
    // init seed
    srand( time(NULL) );
    // Add section functions to addFunctions **by dificulty harder at the bottom 
    /* TODO Remove commets below; Debug only */
    addFunctions.push_back(&AI::section_A);
    addFunctions.push_back(&AI::section_B);
    addFunctions.push_back(&AI::section_I);
    addFunctions.push_back(&AI::section_C);
    addFunctions.push_back(&AI::section_D);
    addFunctions.push_back(&AI::section_E);
    addFunctions.push_back(&AI::section_F);
    addFunctions.push_back(&AI::section_H);
    addFunctions.push_back(&AI::section_K);
    addFunctions.push_back(&AI::section_L);  
    addFunctions.push_back(&AI::section_J);
    addFunctions.push_back(&AI::section_G);
}

AI::~AI(){
    // I dunno if we need...
}

int AI::addObjects(int score, std::vector<Drawable> &objects){
    int time = 0;
    // Get the index of the level to add
    int index = this->getIndex(score);
    // add it to the vector
    this->addFunctions[index](objects);
    // Get distance in time (length added / velocity of obj)
    time = objects.back().getY();
    time = time / config::fgSpeed; // time = px * speed
    return time;
}

int AI::getIndex(int score){
    int index = 0;
    if (score < 5000) {
	// training wheels 
	index = rand() % 5;
    } else if (score < 10000){
	// getting better
	index = rand() % 10;
    } else { 
	// have 'em all!!!
	index = rand() % addFunctions.size(); 
    }
    // Calculate an index from 0 to (addFunctions.size() - 1)
    // as score rises give more higher index levels (higher the number the harder the section)
    // For now, just do a random nnumber.
    
    return index;
}

// Section functions
void AI::smallMiddle(int y, std::vector<Drawable> &objects){
    // Adds a small box at the given x, y
    objects.push_back(Drawable(config::smallBox,
			       SDL_Rect({config::gameRect.x + (config::gameRect.w / 2) - (config::smallBox.w / 2) * config::scale, y, 0, 0}),
			       config::fgSpeed));
}

void AI::smallLeft(int y, std::vector<Drawable> &objects){
    // renders small block on left side
    //[x]--
    //------ start
    objects.push_back(Drawable(config::smallBox,
			       SDL_Rect({config::gameRect.x, y, 0, 0}),
			       config::fgSpeed));
}

void AI::smallRight(int y, std::vector<Drawable> &objects){
    // renders small block on left side
    //[x]--
    //------ start
    objects.push_back(Drawable(config::smallBox,
			       SDL_Rect({config::gameRect.x + config::gameRect.w - (config::smallBox.w * config::scale), y, 0, 0}),
			       config::fgSpeed));
}

void AI::section_A(std::vector<Drawable> &objects){
    // renders small block on left side
    // --[x]
    //[x]--
    //------ start
    int y = config::smallBox.h * (-1 * config::scale);
    AI::smallLeft(y, objects);
    y -= config::obstFreq / 2;
    AI::smallRight(y, objects);
}

void AI::section_B(std::vector<Drawable> &objects){
    // renders small block on left side
    // --[x]
    //[x]--
    //------ start
    int y = config::smallBox.h * (-1 * config::scale);;
    AI::smallLeft(y, objects);
    y -= config::obstFreq / 4;
    AI::smallRight(y, objects);
}

void AI::section_C(std::vector<Drawable> &objects){
    // renders small block on left side
    //[x]--
    // --[x]
    // --[x]
    //[x]--
    //------ start
    int y = config::smallBox.h * (-1 * config::scale);
    AI::smallLeft(y, objects);
    y -= config::obstFreq / 4;
    AI::smallRight(y, objects);
    y -= config::obstFreq / 2;
    AI::smallRight(y, objects);
    y -= config::obstFreq / 6;
    AI::smallLeft(y, objects);
}

void AI::section_D(std::vector<Drawable> &objects){
    // renders small block on left side
    //[x]--
    // --[x]
    // --[x]
    //[x]--
    //------ start
    int y = config::smallBox.h * (-1 * config::scale);
    AI::smallMiddle(y, objects);
    y -= config::smallBox.h * config::scale; 
    AI::smallLeft(y, objects);
    y -= config::obstFreq / 6;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale / 2; 
    AI::smallLeft(y, objects);
    y -= config::obstFreq / 4;
    AI::smallRight(y, objects);
    y -= config::obstFreq / 6;
    AI::smallMiddle(y, objects);
}

void AI::section_E(std::vector<Drawable> &objects){
    // [x]--
    // --[x]
    // -[x]
    int y = config::smallBox.h * (-1 * config::scale);
    AI::smallMiddle(y, objects);
    y -= config::obstFreq / 6;
    AI::smallRight(y, objects);
    y -= config::obstFreq / 4;
    AI::smallLeft(y, objects);
}

void AI::section_F(std::vector<Drawable> &objects){
    // [x]--
    // --[x]
    // -[x]
    int y = config::smallBox.h * (-1 * config::scale);
    AI::smallMiddle(y, objects);
    y -= config::obstFreq / 6;
    AI::smallLeft(y, objects);
    y -= config::obstFreq / 4;
    AI::smallRight(y, objects);
}

void AI::section_G(std::vector<Drawable> &objects){
    // [x]--
    // --[x]
    // [x]--
    // --[x]
    // [x]--
    int y = config::smallBox.h * (-1 * config::scale);
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
}

void AI::section_H(std::vector<Drawable> &objects){
  // --[x]
  // [x]--
  // -[x]-
  // [x]--
    int y = config::smallBox.h * (-1 * config::scale);
    AI::smallMiddle(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallMiddle(y, objects);
}
    
void AI::section_I(std::vector<Drawable> &objects){
  // --[x]
  // [x]--
  // -[x]-
  // [x]--
    int y = config::smallBox.h * (-1 * config::scale);
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
}
  
void AI::section_J(std::vector<Drawable> &objects){
  // [x]--
  // --[x]
  // [x]--
  // -[x]-
  // [x]--
    int y = config::smallBox.h * (-1 * config::scale);
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallMiddle(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
} 

void AI::section_K(std::vector<Drawable> &objects){
  // [x][x]-
  // [x]-[x]
  // [x]-[x]
  // [x][x]-
  // [x]-[x]
    int y = config::smallBox.h * (-1 * config::scale);
    AI::smallLeft(y, objects);
    AI::smallMiddle(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    AI::smallMiddle(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    AI::smallMiddle(y, objects);
} 

void AI::section_L(std::vector<Drawable> &objects){
  // [x][x]-
  // [x]-[x]
  // [x]-[x]
  // [x][x]-
  // [x]-[x]
    int y = config::smallBox.h * (-1 * config::scale);
    AI::smallRight(y, objects);
    AI::smallMiddle(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    AI::smallMiddle(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallRight(y, objects);
    y -= config::smallBox.h * config::scale * 1.5;
    AI::smallLeft(y, objects);
    AI::smallRight(y, objects);
} 
