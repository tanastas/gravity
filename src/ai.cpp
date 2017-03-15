#include "ai.hpp"


// Small box sprite location
SDL_Rect AI::smallBox = {69, 18, 10, 10};
SDL_Rect AI::gameRect = {40, 0, 370, 800};
int AI::fullPause = 1000;
float AI::objSpeed = .15;

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
    time = time / objSpeed; // time = px * speed
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
    objects.push_back(Drawable(AI::smallBox,
			       SDL_Rect({AI::gameRect.x, y, 0, 0}),
			       0.15));
}
// Section functions
void AI::smallRight(int y, std::vector<Drawable> &objects){
    // renders small block on left side
    //[x]--
    //------ start
    objects.push_back(Drawable(AI::smallBox,
			       SDL_Rect({AI::gameRect.x + gameRect.w - (smallBox.w * 10), y, 0, 0}),
			       0.15));
}

void AI::section_A(std::vector<Drawable> &objects){
    // renders small block on left side
    // --[x]
    //[x]--
    //------ start
    int y = AI::smallBox.h * -10;
    AI::smallLeft(y, objects);
    y -= fullPause/2;
    AI::smallRight(y, objects);
}

void AI::section_B(std::vector<Drawable> &objects){
    // renders small block on left side
    // --[x]
    //[x]--
    //------ start
    int y = AI::smallBox.h * -10;
    AI::smallLeft(y, objects);
    y -= fullPause/4;
    AI::smallRight(y, objects);
}

void AI::section_C(std::vector<Drawable> &objects){
    // renders small block on left side
    // --[x]
    //[x]--
    //------ start
    int y = AI::smallBox.h * -10;
    AI::smallLeft(y, objects);
    y -= fullPause/4;
    AI::smallRight(y, objects);
    y -= fullPause/2;
    AI::smallRight(y, objects);
    y -= fullPause/6;
    AI::smallLeft(y, objects);
}

