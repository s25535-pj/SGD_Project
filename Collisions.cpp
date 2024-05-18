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
    std::cout << "[Collisions] Deleted Collisions object" << std::endl;
}

// AABB To za słabe, nie sprawdza kierunku.
bool Collisions::collisionDetected(GameObject* o1, GameObject* o2) {
    if (o1->posX < o2->posX + o2->w &&  //  lewy < prawy    | lewa strona o1
        o1->posX + o1->w > o2->posX &&  //  prawy > lewy    | prawa strona o1
        o1->posY < o2->posY + o2->h &&  //  górny < dolny   | górna strona o1
        o1->posY + o1->h > o2->posY) {  //  dolny > górny   | dolna strona o1

        return true;
    }
    return false;
}

//  Funkcja zakłada że do kolizji już doszło, sprawdza jedynie kierunek
int Collisions::collisionDirection(GameObject * o1, GameObject * o2) {
    int o1right = o1->posX + o1->w; // prawa strona o1
    int o2right = o2->posX + o2->w; // prawa strona o2
    int o1bottom = o1->posY + o1->h; // dół o1
    int o2bottom = o2->posY + o2->h; // dół o2

    int overlapX = (o1right - o2->posX) - (o2right - o1->posX); // (prawa o1 - lewa o2) - (prawa o2 - lewa o1) =
    int overlapY = (o1bottom - o2->posY) - (o2bottom - o1->posY);

    // Określ gdzie kolizja zaszła
    if (std::abs(overlapX) < std::abs(overlapY)) {
        if (overlapY > 0) {
            return 0; // z góry
        } else {
            return 2; // dół
        }
    } else {
        if (overlapX > 0) {
            return 1; // z lewej
        } else {
            return 3; // z prawej
        }
    }
}

// Po kolei kolizje z gracza ze ścianą i jak się zachować
void Collisions::playerWallCollision(Player* player) {
    // Przelatywanie przez ściany :)
    if (player->posX < -player->w) { player->posX = WINDOW_WIDTH; } //    if (posX < 0) { posX = 0; }
    if (player->posX > WINDOW_WIDTH) { player->posX = -player->w; } //    if (posX > WINDOW_WIDTH - PLAYER_WIDTH) { posX = WINDOW_WIDTH - PLAYER_WIDTH; }
    if (player->posY < 0) { player->posY = 0; }
    if (player->posY > WINDOW_HEIGHT - player->h) { player->posY = WINDOW_HEIGHT - player->h; }
}

// Po kolei kolizje z piłki ze ścianą i jak się zachować
void Collisions::ballWallCollision(Ball* ball) {
    // Przelatywanie przez ściany :)
    if (ball->posX < 0) { ball->velX = -ball->velX; } //  if (posX < -w) { posX = WINDOW_WIDTH; }
    if (ball->posX > WINDOW_WIDTH - BALL_WIDTH) { ball->velX = -ball->velX; } //  if (posX > WINDOW_WIDTH) { posX = -w; }
    if (ball->posY < 0) { ball->velY = -ball->velY; }
    if (ball->posY > WINDOW_HEIGHT - ball->h) { ball->velY = -ball->velY; }
};

// Kolizje z każdą cegłą i jak ma się zachować
void Collisions::ballBrickCollision(Ball* ball, Brick* bricks[BRICK_ROWS][BRICK_COLUMNS]) {
    for (int i = 0; i < BRICK_ROWS; ++i) {
        for (int j = 0; j < BRICK_COLUMNS; ++j) {
            if (collisionDetected(ball, bricks[i][j]) && bricks[i][j]->alive) {
                if(collisionDirection(ball, bricks[i][j]) % 2 == 1) {
                    ball->velX *= -1;
                }
                if(collisionDirection(ball, bricks[i][j]) % 2 == 0) {
                    ball->velY *= -1;
                }
                bricks[i][j]->destroy();
                ball->increaseSpeed();
            }
        }
    }
}

void Collisions::ballPlayerCollision(Ball* ball, Player* player) {
    if(collisionDetected(player, ball)) {
        ball->bounceFromPlayer(player);
    };
}

bool Collisions::checkIfGameOver(Ball* ball) {
    if(ball->posY + ball->h >= WINDOW_HEIGHT) {
        return true;
    }
    return false;
}

void Collisions::handleAllCollisions(Player* player, Ball* ball, Brick* bricks[BRICK_ROWS][BRICK_COLUMNS]) {
    playerWallCollision(player);
    ballWallCollision(ball);
    ballPlayerCollision(ball, player);
    ballBrickCollision(ball ,bricks);
}