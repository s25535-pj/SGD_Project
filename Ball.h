#ifndef BB3_BALL_H
#define BB3_BALL_H

#include <SDL_rect.h>
#include <iostream>

class Ball {
private:
    SDL_Rect rect;
    double dx, dy;
    int speed;

public:
    Ball(int x, int y, int size, int speed) {
        rect.x = x;
        rect.y = y;
        rect.w = size;
        rect.h = size;
        dx = 1;
        dy = 1;
        this->speed = speed;
    }

    const SDL_Rect* getRect() const { return &rect; }
    int getX() const { return rect.x; }
    int getY() const { return rect.y; }
    int getSize() const { return rect.w; }
    double getDx() const { return dx; }
    double getDy() const { return dy; }
    int getSpeed() const { return speed; }

    void setDx(float new_dx) {
        dx = new_dx;
    }

    void setDy(float new_dy) {
        dy = new_dy;
    }

    void flipVertically() {
        dy = -dy;
        std::cout << "Flipped vertically" << std::endl;
    }

    void flipHorizontally() {
        dx = -dx;
        std::cout << "Flipped horizontally" << std::endl;
    }

    void updatePostion() {
        rect.x += (int)dx;
        rect.y += (int)dy;
//        std::cout << "Updated ball position: " << rect.x << ":" << rect.y << std::endl;
    }

//    void setStartingPosition(Player player) {
//        y = player.getY() - player.getHeight() * 4;
//    }
//

};

#endif //BB3_BALL_H
