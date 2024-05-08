#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "Player.h"
#include "GameObject.h"
#include "macros.h"

Player::Player(int posX, int posY, int w, int h) : GameObject(posX,posY,w,h), velX(0), velY(0) {
    std::cout << "[Player] Created Player object" << std::endl;
}

Player::~Player() {
    std::cout << "[Player] Deleted Player object" << std::endl;
}

void Player::renderObject(SDL_Renderer* renderer) {
    SDL_Rect rectangle = {posX, posY, w, h};
    SDL_SetRenderDrawColor(renderer,200,200,200,255);
    SDL_RenderFillRect(renderer, &rectangle);
}

void Player::moveLeft() {
    velX -= PLAYER_ACCELERATION_VALUE;
}

void Player::moveRight() {
    velX += PLAYER_ACCELERATION_VALUE;
}

void Player::moveUp() {
    velY -= PLAYER_ACCELERATION_VALUE;
}

void Player::moveDown() {
    velY += PLAYER_ACCELERATION_VALUE;
}

void Player::handleWallCollision() {
    // Przelatywanie przez ściany :)
    if (posX < -w) { posX = WINDOW_WIDTH; } //    if (posX < 0) { posX = 0; }
    if (posX > WINDOW_WIDTH) { posX = -w; } //    if (posX > WINDOW_WIDTH - PLAYER_WIDTH) { posX = WINDOW_WIDTH - PLAYER_WIDTH; }
    if (posY < 0) { posY = 0; }
    if (posY > WINDOW_HEIGHT - h) { posY = WINDOW_HEIGHT - h; }
};

void Player::applyResistance() {
    if (velX < 0) { velX += PLAYER_RESISTANCE; }
    if (velX > 0) { velX -= PLAYER_RESISTANCE; }
    if (velY < 0) { velY += PLAYER_RESISTANCE; }
    if (velY > 0) { velY -= PLAYER_RESISTANCE; }
}

void Player::limitSpeedToMax() {
    // Granica pędkości, Poruszanie na ukos jest szybsze trzeba odpowiednio zmiejszyć, nie chcemy liczyć bardzo zmiennoprzecinkowych
    // a^2 + b^2 = c^2
    double speed = std::sqrt(velX * velX + velY * velY);
    if (speed > PLAYER_MAX_SPEED) {
        velX = (velX / speed) * PLAYER_MAX_SPEED;
        velY = (velY / speed) * PLAYER_MAX_SPEED;
        velX = round(velX * 100.0) / 100.0;
        velY = round(velY * 100.0) / 100.0;
    }
}

void Player::updateObject() {
    applyResistance();
    limitSpeedToMax();
    posX += (int)velX;
    posY += (int)velY;
    handleWallCollision();


//    std::cout << "[Player] velX: " << velX << std::endl;
//    std::cout << "[Player] velY: " << velY << std::endl;
//    std::cout << "[Player] posX: " << posX << std::endl;
}