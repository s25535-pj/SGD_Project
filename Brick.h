#ifndef BRICKBREAKER_BRICK_H
#define BRICKBREAKER_BRICK_H

#include <SDL2/SDL.h>
#include "GameObject.h"

class Brick : public GameObject {
public:
    bool alive;

    Brick(int posX, int posY, int w, int h);
    ~Brick();

    void renderObject(SDL_Renderer*) override;
    void updateObject() override;
    void destroy();
};


#endif //BRICKBREAKER_BRICK_H
