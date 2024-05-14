#ifndef BRICKBREAKER_GAMEOBJECT_H
#define BRICKBREAKER_GAMEOBJECT_H

#include <iostream>
#include <SDL2/SDL.h>

class GameObject {
public:
    int posX;
    int posY;
    int w;
    int h;
    const char* texturePath;
    SDL_Texture* texture;

    GameObject(int posX, int posY, int w, int h);
    ~GameObject();

/* A virtual function (also known as virtual methods) is a member function that is declared within a base class and is re-defined (overridden)
 * by a derived class. When you refer to a derived class object using a pointer or a reference to the base class,
 * you can call a virtual function for that object and execute the derived class’s version of the method.
 * Używane w oknie przy renderingu */
    virtual void renderObject(SDL_Renderer*) = 0;
    virtual void updateObject() = 0;
//    virtual SDL_Texture* loadTexture(SDL_Renderer*) = 0;
};


#endif //BRICKBREAKER_GAMEOBJECT_H
