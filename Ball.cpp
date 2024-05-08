#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "Ball.h"
#include "GameObject.h"
#include "Player.h"
#include "macros.h"

Ball::Ball(int posX, int posY, int w, int h) : GameObject(posX,posY,w,h), velX(10), velY(10) {
    std::cout << "[Ball] Created Ball object" << std::endl;
}

Ball::~Ball() {
    std::cout << "[Ball] Deleted Ball object" << std::endl;
}

void Ball::renderObject(SDL_Renderer* renderer) {
    SDL_Rect rectangle = {posX, posY, w, h};
    SDL_SetRenderDrawColor(renderer,200,200,200,255);
    SDL_RenderFillRect(renderer, &rectangle);
}

void Ball::handleWallCollision() {
    // Przelatywanie przez ściany :)
    if (posX < 0) { velX = -velX; } //  if (posX < -w) { posX = WINDOW_WIDTH; }
    if (posX > WINDOW_WIDTH - BALL_WIDTH) { velX = -velX; } //  if (posX > WINDOW_WIDTH) { posX = -w; }
    if (posY < 0) { velY = -velY; }
    if (posY > WINDOW_HEIGHT - h) { velY = -velY; }
};


void Ball::applyGravity() {
    velY += BALL_GRAVITY;
}

void Ball::bounceFromPlayer(Player* player) {
//    int relativeCollisionPosition = posX - player->posX;
//    // Przeliczenie pozycji kolizji na wartość w zakresie od 0 do 100
//
//    int collisionPosition = (relativeCollisionPosition * 100) / player->w;
//    // Zmiana kierunku ruchu piłki w zależności od pozycji kolizji na paletce
//    int maxDeflection = 5; // Maksymalna wartość zmiany prędkości w bok
//    int deflection = (collisionPosition - 50) * maxDeflection / (player->w / 2);
//    velX += deflection; // Dodanie zmiany prędkości w zależności od pozycji kolizji
//    velY = -velY; // Zmiana kierunku ruchu piłki (odbicie od paletki)



    double relative = player->posX + (player->w/2.0) - (posX + w/2.0); // Wyliczanie środka gracza
    double normalized = relative / (player->w/2.0); // Normalizacja od -1 do 1

//        if (normalized > maxSidewaysBounce) {
//            normalized = maxSidewaysBounce;
//        } else if (normalized < -maxSidewaysBounce) {
//            normalized = -maxSidewaysBounce;
//        }
//        std::cout << normalized << std::endl;
    double bounce = normalized * (5* M_PI/12);

    bounce *= 0.9;
    velX = 10 * -sin(bounce);
    velY = -10 * cos(bounce);
}

void Ball::updateObject() {
//    applyGravity();
    handleWallCollision();

    posX += (int)velX;
    posY += (int)velY;

//    std::cout << "[Ball] velX: " << velX << std::endl;
//    std::cout << "[Ball] velY: " << velY << std::endl;
//    std::cout << "[Ball] posX: " << posX << std::endl;
//    std::cout << "[Ball] posY: " << posY << std::endl;
}