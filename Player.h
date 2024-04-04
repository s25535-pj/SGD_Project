#ifndef BB3_PLAYER_H
#define BB3_PLAYER_H

#include <SDL_rect.h>
#include <iostream>

struct Color {
    int r;
    int g;
    int b;
};

class Player {
private:
    SDL_Rect rect;
    int speed;
    int lives = 3;
    Color color {64,255,0};

public:
    Player(int x, int y,int w, int h, int speed) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        this->speed = speed;
    }

    const SDL_Rect* getRect() const { return &rect; }
    int getX() const { return rect.x; }
    int getY() const { return rect.y; }
    int getW() const { return rect.w; }
    int getH() const { return rect.h; }
    Color getColor() const { return color; }

    void setX(int x) { rect.x = x; }
    void setY(int y) { rect.y = y; }

    int reduceLives() {
        lives--;
        switch (lives){
            case 2: {color.r = 255;break;}
            case 1: {color.g = 77; color.b = 77; break;}
        }
        std::cout << "Player lost one life" << std::endl;
        return lives;
    }

    void moveLeft() {
        rect.x -= speed;
//        std::cout << "Player moved left: " << rect.x << std::endl;
    }

    void moveRight() {
        rect.x += speed;
//        std::cout << "Player moved right: " << rect.x << std::endl;
    }


};

#endif //BB3_PLAYER_H
