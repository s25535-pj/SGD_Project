#ifndef BRICKBREAKER_BALL_H
#define BRICKBREAKER_BALL_H

#include <SDL2/SDL.h>
#include "GameObject.h"
#include "Player.h"

class Ball : public GameObject {
public:
    double velX;
    double velY;

    Ball(int posX, int posY, int w, int h);
    ~Ball();

    void renderObject(SDL_Renderer*) override;
    void handleWallCollision();
    void applyGravity();
    void limitSpeedToMax();
    void bounceFromPlayer(Player*);
    void updateObject() override;
};


#endif //BRICKBREAKER_BALL_H
