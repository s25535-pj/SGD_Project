#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameObject.h"

GameObject::GameObject(int posX, int posY, int w, int h, const char* texturePath) : posX(posX), posY(posY), w(w), h(h), texturePath(texturePath) {
    std::cout << "[GameObject] Created GameObject object" << std::endl;
}

GameObject::~GameObject() {
    SDL_DestroyTexture(texture);
    std::cout << "[GameObject] Deleted GameObject object" << std::endl;
}

void GameObject::loadTexture(SDL_Renderer* renderer) {
    if(texturePath) {
        texture = IMG_LoadTexture(renderer, texturePath);
        if (texture == nullptr) {
            std::cout << "[GameObject] Texture not loaded: " << SDL_GetError() << std::endl;
        }
    } else {
        std::cout << "[GameObject] No texture path: " << SDL_GetError() << std::endl;
    }
}