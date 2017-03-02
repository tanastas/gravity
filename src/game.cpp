#include "game.hpp"

Game::Game() {
    this->res = Resource();
    this->renderer = NULL;
    this->side_speed = 0.1;
    this->bg_speed = this->side_speed / 2;
    this->side_y = 0;
    this->bg_y = 0;
}

Game::~Game(){
}

void Game::init(SDL_Renderer * renderer) {
    this->res.loadResource(renderer);
    this->renderer = renderer;
}

void Game::renderBG(unsigned int tDelta) {
    std::cout <<  "delta: "<<tDelta << std::endl;
    int y, x;
    // Set X
    x = 0;
    // Calculate side Y
    this->side_y = this->side_y + float(tDelta) * this->side_speed;
    if (this->side_y > 0.0) {
        this->side_y -= 170.0;
    }
    // Calculate BG Y
    this->bg_y = this->bg_y + float(tDelta) * this->bg_speed;
    if (this->bg_y > 0.0) {
        this->bg_y -= 170.0;
    }
    // Render left side
    y = int(this->side_y);
    this->res.sprites.find("left-side")->second.render(x, y, this->renderer);
    // Render right side
    x = 410;
    this->res.sprites.find("right-side")->second.render(x, y, this->renderer);
    // Render BG
    x = 40;
    y = int(this->bg_y);
    this->res.sprites.find("background")->second.render(x, y, this->renderer);
}
