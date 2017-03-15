#include "ai.hpp"


// Small box sprite location
SDL_Rect AI::smallBox = {69, 18, 10, 10};
SDL_Rect AI::gameRect = {40, 0, 410, 800};

AI::AI(){
    // Add section functions to addFunctions 
    addFunctions.push_back(&AI::section_A);
}

AI::~AI(){
    // I dunno if we need...
}

int AI::addObjects(int score, std::vector<Drawable> &objects){
    int time = 0;
    // Get the index of the level to add
    int index = this->getIndex(score);
    // add it to the vector
    this->addFunctions[0](objects);
    // Get distance in time (length added / velocity of obj)
    time = objects.back().getY();
    return time;
}

int AI::getIndex(int score){
    // Calculate an index from 0 to (addFunctions.size() - 1)
    // as score rises give more higher index levels (higher the number the harder the section)
    return 0;
}

// Section functions
void AI::section_A(std::vector<Drawable> &objects){
    // renders small block on left side
    //[x]--
    //------ start
    std::cout << " REALLY adding!\n";
    objects.push_back(Drawable(AI::smallBox,
			       SDL_Rect({AI::gameRect.x, AI::smallBox.h * -10, 0, 0}),
			       0.15));
}
