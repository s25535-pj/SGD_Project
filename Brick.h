#ifndef BB3_BRICK_H
#define BB3_BRICK_H
//#define TEXTURE_PATH "G:/Clion projects/BB3/textures/gray_brick_wall.bmp"
//#define TEXTURE_PATH "G:/Clion projects/BB3/textures/test1.bmp"
//#define TEXTURE_PATH "G:/Clion projects/BB3/textures/hit4.bmp"
#define TEXTURE_PATH "G:/Clion projects/BB3/textures/brick24.bmp"
#include <SDL_rect.h>
#include <iostream>

class Brick {
private:
    SDL_Rect rect;
    SDL_Surface *surface;
    SDL_Texture *texture;
    bool isVisible;

public:
    Brick() {
        rect.x = 0;
        rect.y = 0;
        rect.w = 0;
        rect.h = 0;
        isVisible = true;
        surface = nullptr;
        texture = nullptr;

    }
    Brick(int x, int y, int w, int h) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        isVisible = true;
    }

    ~Brick() {
        SDL_DestroyTexture(texture);
        std::cout << "Destroyed Texture" << std::endl;
    }

    const SDL_Rect* getRect() const { return &rect; }
    int getX() const { return rect.x; }
    int getY() const { return rect.y; }
    int getW() const { return rect.w; }
    int getH() const { return rect.h; }
    bool getIsVisible() const { return isVisible; }
    SDL_Texture* getTexture() const { return texture; }

    void setIsVisible(bool value)  {
        isVisible = value;
        std::cout << "changed visibility" << std::endl;
    }

    void initTexture(SDL_Renderer *renderer) {
        surface = SDL_LoadBMP(TEXTURE_PATH);
        if (!surface) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
            std::cout << "Created surface" << std::endl;
        }

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
            std::cout << "Created Texture" << std::endl;
        }
        SDL_FreeSurface(surface);
    }
};

#endif //BB3_BRICK_H
