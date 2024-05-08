#include "Collisions.h"
#include "GameObject.h"
#include "Ball.h"
#include "Brick.h"
#include "Player.h"
#include "macros.h"

Collisions::Collisions() {
    std::cout << "[Collisions] Created Collisions object" << std::endl;
}

Collisions::~Collisions() {
    std::cout << "[Ball] Deleted Collisions object" << std::endl;
}

// AABB
bool Collisions::collisionDetected(GameObject* o1, GameObject* o2) {
    if (o1->posX < o2->posX + o2->w &&
        o1->posX + o1->w > o2->posX &&
        o1->posY < o2->posY + o2->h &&
        o1->posY + o1->h > o2->posY){
        return true;
    }
    return false;
}

void Collisions::playerWallCollision(Player* player) {
    // Przelatywanie przez ściany :)
    if (player->posX < -player->w) { player->posX = WINDOW_WIDTH; } //    if (posX < 0) { posX = 0; }
    if (player->posX >
        WINDOW_WIDTH) { player->posX = -player->w; } //    if (posX > WINDOW_WIDTH - PLAYER_WIDTH) { posX = WINDOW_WIDTH - PLAYER_WIDTH; }
    if (player->posY < 0) { player->posY = 0; }
    if (player->posY > WINDOW_HEIGHT - player->h) { player->posY = WINDOW_HEIGHT - player->h; }
}

void Collisions::ballWallCollision(Ball* ball) {
    // Przelatywanie przez ściany :)
    if (ball->posX < 0) { ball->velX = -ball->velX; } //  if (posX < -w) { posX = WINDOW_WIDTH; }
    if (ball->posX > WINDOW_WIDTH - BALL_WIDTH) { ball->velX = -ball->velX; } //  if (posX > WINDOW_WIDTH) { posX = -w; }
    if (ball->posY < 0) { ball->velY = -ball->velY; }
    if (ball->posY > WINDOW_HEIGHT - ball->h) { ball->velY = -ball->velY; }
};

void Collisions::ballBrickCollision(Ball* ball, Brick* bricks[BRICK_ROWS][BRICK_COLUMNS]) {
    for (int i = 0; i < BRICK_ROWS; ++i) {
        for (int j = 0; j < BRICK_COLUMNS; ++j) {
            if (collisionDetected(ball, bricks[i][j]) && bricks[i][j]->alive) {
                bricks[i][j]->destroy();
                ball->velY *= -1;
                ball->increaseSpeed();
            }
        }
    }
}

void Collisions::ballPlayerCollision(Ball* ball, Player* player) {
    if (collisionDetected(player, ball)) {
        ball->bounceFromPlayer(player);
    };
}

void Collisions::handleAllCollisions(Player* player, Ball* ball, Brick* bricks[BRICK_ROWS][BRICK_COLUMNS]) {
    playerWallCollision(player);
    ballWallCollision(ball);
    ballPlayerCollision(ball, player);
    ballBrickCollision(ball ,bricks);
}