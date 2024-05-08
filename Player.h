#ifndef BRICKBREAKER_PLAYER_H
#define BRICKBREAKER_PLAYER_H

#include <SDL2/SDL.h>
#include "GameObject.h"

class Player : public GameObject {
public:
    double velX;
    double velY;
    double acc;
    double maxSpeed;
    double resistance;

    Player(int posX, int posY, int w, int h);
    ~Player();

    void renderObject(SDL_Renderer*) override;
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void applyResistance();
    void limitSpeedToMax();
    void limitUpMovement();
    void updateObject() override;
};

#endif //BRICKBREAKER_PLAYER_H
