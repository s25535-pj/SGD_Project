#include <iostream>
#include <SDL2/SDL.h>
#include "GameObject.h"

GameObject::GameObject(int posX, int posY, int w, int h) : posX(posX), posY(posY), w(w), h(h) {
    std::cout << "[GameObject] Created GameObject object" << std::endl;
}

GameObject::~GameObject() {
    if(texture) {
        std::cout << "[GameObject] Destroyed texture" << std::endl;
//        SDL_DestroyTexture(texture);
    }
    std::cout << "[GameObject] Deleted GameObject object" << std::endl;
}

//SDL_Texture *GameObject::loadTexture(SDL_Renderer* renderer) {
//        SDL_Surface* surface = SDL_LoadBMP(texturePath);
//        if (!surface) {
//            std::cout << "[GameObject] Surface not created" << std::endl;
//        }
//
//        texture = SDL_CreateTextureFromSurface(renderer, surface);
//        if (!texture) {
//            std::cout << "[GameObject] Texture not created" << std::endl;
//        }
//        SDL_FreeSurface(surface);
//}