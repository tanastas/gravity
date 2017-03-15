#include "ai.hpp"


AI::AI(){
    // init seed
    srand( time(NULL) );
    // Add section functions to addFunctions 
    addFunctions.push_back(&AI::section_A);
    addFunctions.push_back(&AI::section_B);
    addFunctions.push_back(&AI::section_C);
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
    int index = rand() % addFunctions.size(); 
    // Calculate an index from 0 to (addFunctions.size() - 1)
    // as score rises give more higher index levels (higher the number the harder the section)
    // For now, just do a random nnumber.
    return index;
}

// Section functions
void AI::smallLeft(int y, std::vector<Drawable> &objects){
    // renders small block on left side
    //[x]--
    //------ start
    objects.push_back(Drawable(config::smallBox,
			       SDL_Rect({config::gameRect.x, y, 0, 0}),
			       config::fgSpeed));
}
// Section functions
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

