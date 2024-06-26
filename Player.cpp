#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "Player.h"
#include "GameObject.h"
#include "macros.h"

Player::Player(int posX, int posY, int w, int h) : GameObject(posX,posY,w,h, PLAYER_TEXTURE), velX(0), velY(0),
acc(PLAYER_ACCELERATION), maxSpeed(PLAYER_MAX_SPEED), resistance(PLAYER_RESISTANCE) {
    std::cout << "[Player] Created Player object" << std::endl;
}

Player::~Player() {
    std::cout << "[Player] Deleted Player object" << std::endl;
}

void Player::renderObject(SDL_Renderer* renderer) {
    SDL_Rect rectangle = {posX, posY, w, h};
    if(texture == nullptr) {
        SDL_SetRenderDrawColor(renderer,200,200,200,255);
        SDL_RenderFillRect(renderer, &rectangle);
    } else {
        SDL_RenderCopy(renderer, texture, NULL, &rectangle);
    }
}

void Player::moveLeft() {
    velX -= acc;
}

void Player::moveRight() {
    velX += acc;
}

void Player::moveUp() {
    velY -= acc;
}

void Player::moveDown() {
    velY += acc;
}

// Dodaj oprór powietrza dla platformy
void Player::applyResistance() {
    if (velX < 0) { velX += resistance; }
    if (velX > 0) { velX -= resistance; }

    if (velY < 0) { velY += resistance; }
    if (velY > 0) { velY -= resistance; }
}

// ChatGPT, dopasuj prędkość gracza by nie były szybszy na ukos
void Player::limitSpeedToMax() {
    // Granica pędkości, Poruszanie na ukos jest szybsze trzeba odpowiednio zmiejszyć
    // a^2 + b^2 = c^2 Pitagorasem oblicz prędkość po ukosie
    double speed = std::sqrt(velX * velX + velY * velY);
    if (speed > maxSpeed) {
        velX = (velX / speed) * maxSpeed;
        velY = (velY / speed) * maxSpeed;
        // Zaokrąglanie. Nie chcemy liczyć bardzo zmiennoprzecinkowych bo mi zmienna nie wyrabia
        velX = round(velX * 100.0) / 100.0;
        velY = round(velY * 100.0) / 100.0;
    }
}

// Granica dla gracza w ruchu do góry
void Player::limitUpMovement() {
    if (posY < WINDOW_HEIGHT * 2/3) {
        velY += PLAYER_GRAVITY;
    }
}

void Player::updateObject() {
    applyResistance();
    limitSpeedToMax();
    limitUpMovement();
    posX += (int)velX;
    posY += (int)velY;
}
