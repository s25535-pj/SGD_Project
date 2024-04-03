#ifndef BB3_BRICK_H
#define BB3_BRICK_H

#include <SDL_rect.h>
#include <iostream>

class Brick {
private:
    SDL_Rect rect;
    bool isVisible;

public:
    Brick() {
        rect.x = 0;
        rect.y = 0;
        rect.w = 0;
        rect.h = 0;
        isVisible = true;
    }
    Brick(int x, int y, int w, int h) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        isVisible = true;

    }
    const SDL_Rect* getRect() const { return &rect; }
    int getX() const { return rect.x; }
    int getY() const { return rect.y; }
    int getW() const { return rect.w; }
    int getH() const { return rect.h; }
    bool getIsVisible() const { return isVisible; }

    void setIsVisible(bool value)  {
        isVisible = value;
        std::cout << "changed visibility" << std::endl;
    }
};

#endif //BB3_BRICK_H
