
#ifndef AI_HPP_
#define AI_HPP_


#include "drawable.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>


class AI {
public:
    // Constructor
    AI();
    // Destructor
    ~AI();
    // returns time for section adds vars to vector;
    int addObjects(int, std::vector<Drawable>&);
    // box for small box sprite
    static SDL_Rect smallBox;
    static SDL_Rect gameRect;
  
private:
    // vector of drawable sections.
    std::vector<void(*)(std::vector<Drawable>&)> addFunctions;
    // returns index given a score.
    int getIndex(int);
    // Section functions added to addFunctions
    static void section_A(std::vector<Drawable> &);
    //void section_B(std::vector<Drawable> &);
    //void section_C(std::vector<Drawable> &);
};


#endif /* AI_HPP_ */
