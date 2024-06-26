#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "macros.h"
#include "Window.h"
#include "Player.h"

Window::Window() : window(nullptr), renderer(nullptr) {
        createWindow();
        createRenderer();
        loadBackgroundTexture();
        std::cout << "[Window] Created Window object" << std::endl;
    }
Window::~Window() {
        deleteAllObjects();
        destroyRenderer();
        destroyWindow();
        std::cout << "[Window] Deleted Window object" << std::endl;
}

SDL_Window* Window::createWindow() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cout << "[Window] Init unsuccessful : " << SDL_GetError() << std::endl;
            exit(1);
        }
        std::cout << "[Window] Init successfull" << std::endl;
        window = SDL_CreateWindow("BlockBreaker",SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);

        if (window == nullptr) {
            std::cout << "[Window] Window not created: " << SDL_GetError() << std::endl;
            SDL_Quit();
            exit(2);
        }
        std::cout << "[Window] Created SDL Window" << std::endl;
        return window;
}

SDL_Renderer* Window::createRenderer() {
        // SDL_RENDERER_ACCELERATED używanie karty graficznej
        // SDL_RENDERER_PRESENTVSYNC wyrównaj do odświerzania monitora
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) {
            std::cout << "[Window] Renderer not created: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(3);
        }
        std::cout << "[Window] Created SDL Renderer" << std::endl;
        return renderer;
}

void Window::destroyWindow() {
    SDL_DestroyWindow(window);
    std::cout << "[Window] Destroyed SDL Window" << std::endl;
}

void Window::destroyRenderer() {
    SDL_DestroyRenderer(renderer);
    std::cout << "[Window] Destroyed SDL Renderer" << std::endl;
}

void Window::saveObjectToList(GameObject* object) {
    List.push_back(object);
    std::cout << "[Window] Added object to list" << std::endl;
}

void Window::deleteAllObjects() {
    for (auto o : List) {
        delete o;
    }
    List.clear();
    std::cout << "[Window] Deleted all objects from list" << std::endl;
}

void Window::updateAllObjects() {
    for (auto o : List) {
        o->updateObject();
    }
}

void Window::loadTextures() {
    for (auto o : List) {
        o->loadTexture(renderer);
    }
}

void Window::loadBackgroundTexture() {
    backgroundTexture = IMG_LoadTexture(renderer, backgroundTexturePath);
    if (backgroundTexture == nullptr) {
        std::cout << "[GameObject] Texture not loaded: " << SDL_GetError() << std::endl;
        SDL_DestroyTexture(backgroundTexture);
    }
}
void Window::drawAllObjects() {
    // Czyszczenie ekranu
    if(backgroundTexture == nullptr) {
        SDL_SetRenderDrawColor(renderer,122,122,122,255);
        SDL_RenderClear(renderer);
    } else {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }

    // Wyrenderuj wszystkie obiekty z listy
    for (auto o : List) {
        o->renderObject(renderer);
    }
    SDL_RenderPresent(renderer);
}

void Window::showGameOver() {
    SDL_Texture* gameOverTexture = IMG_LoadTexture(renderer, gameOverTexturePath);
    if (gameOverTexture == nullptr) {
        std::cout << "[GameObject] Texture not loaded: " << SDL_GetError() << std::endl;
        SDL_DestroyTexture(gameOverTexture);
    } else {
        SDL_Rect rectangle = {WINDOW_WIDTH/2-WINDOW_WIDTH/4,WINDOW_HEIGHT/2-WINDOW_HEIGHT/4,WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
        SDL_RenderCopy(renderer, gameOverTexture, NULL, &rectangle);
        SDL_RenderPresent(renderer);
        std::cout << "[GameObject] Game Over"<< std::endl;
    }
}
