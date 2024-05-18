#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "Ball.h"
#include "GameObject.h"
#include "Player.h"
#include "macros.h"

Ball::Ball(int posX, int posY, int w, int h) : GameObject(posX,posY,w,h, BALL_TEXTURE), velX(2), velY(9), maxSpeed(BALL_MAX_SPEED), speedGain(BALL_SPEED_GAIN) {
    std::cout << "[Ball] Created Ball object" << std::endl;
}

Ball::~Ball() {
    std::cout << "[Ball] Deleted Ball object" << std::endl;
}

void Ball::renderObject(SDL_Renderer* renderer) {
    SDL_Rect rectangle = {posX, posY, w, h};
    if(texture == nullptr) {
        SDL_SetRenderDrawColor(renderer,200,200,200,255);
        SDL_RenderFillRect(renderer, &rectangle);
    } else {
        SDL_RenderCopy(renderer, texture, NULL, &rectangle);
    }
}

void Ball::applyGravity() {
    velY += BALL_GRAVITY;
}

void Ball::increaseSpeed() {
    maxSpeed += speedGain;
        std::cout << "[Ball] Speed increased: " << speedGain + maxSpeed << std::endl;
}

// ChatGPT, Jak zrobić by piłka odbiła się pod zadanym kątem w zależności od pozycji paletki i piłki
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



    double relative = player->posX + (player->w/2.0) - (posX + w/2.0); // Środek gracza - środek piłki = odległość relatywna
    double normalized = relative / (player->w/2.0); // Normalizacja od -1 do 1
    double bounce = normalized * (5* M_PI/12); // Przeliczanie na radiany

    bounce *= 0.8;
    velX = maxSpeed * -sin(bounce);
    velY = -maxSpeed * cos(bounce);
}

void Ball::updateObject() {
//    applyGravity();

    posX += (int)velX;
    posY += (int)velY;

//    std::cout << "[Ball] velX: " << velX << std::endl;
//    std::cout << "[Ball] velY: " << velY << std::endl;
//    std::cout << "[Ball] posX: " << posX << std::endl;
//    std::cout << "[Ball] posY: " << posY << std::endl;
}
