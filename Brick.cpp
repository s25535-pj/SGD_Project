#include <iostream>
#include <SDL2/SDL.h>
#include "Brick.h"

Brick::Brick(int posX, int posY, int w, int h) : GameObject(posX,posY,w,h), alive(true) {
    std::cout << "[Brick] Created Brick object" << std::endl;
}

Brick::~Brick() {
    std::cout << "[Brick] Deleted Brick object" << std::endl;
}

void Brick::renderObject(SDL_Renderer* renderer) {
    if (alive) {
        SDL_Rect rectangle = {posX, posY, w, h};
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &rectangle);
    }
}

void Brick::destroy() {
    alive = false;
    std::cout << "[Brick] Destroyed Brick" << std::endl;
}

void Brick::updateObject() {}