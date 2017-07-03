
#ifndef AI_HPP_
#define AI_HPP_


#include "drawable.hpp"
#include "config.cpp"
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>


class AI {
public:
    // Constructor
    AI();
    // Destructor
    ~AI();
    // returns time for section adds vars to vector;
    int addObjects(int, std::vector<Drawable>&);
     
private:
    // vector of drawable sections.
    std::vector<void(*)(std::vector<Drawable>&)> addFunctions;
    //NOTE: vector is of functions which take the vector of drawables
    // returns index given a score.
    int getIndex(int);
    // Section functions added to addFunctions
    static void smallMiddle(int, std::vector<Drawable> &);
    static void smallLeft(int, std::vector<Drawable> &);
    static void smallRight(int, std::vector<Drawable> &);
    static void section_A(std::vector<Drawable> &);
    static void section_B(std::vector<Drawable> &);
    static void section_C(std::vector<Drawable> &);
    static void section_D(std::vector<Drawable> &);
    static void section_E(std::vector<Drawable> &);
    static void section_F(std::vector<Drawable> &);
    static void section_G(std::vector<Drawable> &);
    static void section_H(std::vector<Drawable> &);
    static void section_I(std::vector<Drawable> &);
    static void section_J(std::vector<Drawable> &);
    static void section_K(std::vector<Drawable> &);
    static void section_L(std::vector<Drawable> &);
};


#endif /* AI_HPP_ */
