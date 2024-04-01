#ifndef BB3_BRICK_H
#define BB3_BRICK_H

#include <SDL_rect.h>
#include <iostream>

class Brick {
private:
    SDL_Rect rect;
    bool isVisible;

public:
    Brick(int x, int y, int w, int h) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        isVisible = true;

    }

    bool getIsVisible() const { return isVisible; }

    void setIsVisible(bool new_isVisible)  {
        isVisible = new_isVisible;
    }
};

#endif //BB3_BRICK_H
