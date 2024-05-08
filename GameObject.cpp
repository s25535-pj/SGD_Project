#include <iostream>
#include "GameObject.h"

GameObject::GameObject(int posX, int posY, int w, int h) : posX(posX), posY(posY), w(w), h(h) {
    std::cout << "[GameObject] Created GameObject object" << std::endl;
}

GameObject::~GameObject() {
    std::cout << "[GameObject] Deleted GameObject object" << std::endl;
}