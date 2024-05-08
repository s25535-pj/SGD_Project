#ifndef BRICKBREAKER_WINDOW_H
#define BRICKBREAKER_WINDOW_H

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "macros.h"
#include "GameObject.h"


class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<GameObject*> List;

public:
    Window();
    ~Window();

    SDL_Window* createWindow();
    SDL_Renderer* createRenderer();
    void destroyWindow();
    void destroyRenderer();
    void saveObjectToList(GameObject*);
    void deleteAllObjects();
    void updateAllObjects();
    void drawAllObjects();
};


#endif //BRICKBREAKER_WINDOW_H
