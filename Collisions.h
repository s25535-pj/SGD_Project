#ifndef BRICKBREAKER_COLLISIONS_H
#define BRICKBREAKER_COLLISIONS_H

#include "GameObject.h"
#include "Ball.h"
#include "Brick.h"
#include "Player.h"
#include "macros.h"

class Collisions {
public:

    Collisions();
    ~Collisions();

    bool collisionDetected(GameObject*, GameObject*);
    int collisionDirection(GameObject*, GameObject*);
    void playerWallCollision(Player*);
    void ballWallCollision(Ball*);
    void ballBrickCollision(Ball*, Brick* [BRICK_ROWS][BRICK_COLUMNS]);
    void ballPlayerCollision(Ball*, Player*);
    void handleAllCollisions(Player*, Ball*, Brick* [BRICK_ROWS][BRICK_COLUMNS]);

};


#endif //BRICKBREAKER_COLLISIONS_H
