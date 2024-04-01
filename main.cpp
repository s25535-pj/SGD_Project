#include <SDL.h>
#include <cmath>
#include <iostream>
#include "Player.h"
#include "Ball.h"
#include "Brick.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 12
#define PLAYER_SPEED 15
#define PLAYER_SPACE_FROM_BOTTOM 100

#define BALL_SPEED 10
#define BALL_SIZE 30

#define MAX_BALL_SIDEWAYS_BOUNCE_FROM_PLAYER_ANGLE 3 // Piłkę odbija od ścian bocznych w sytuacji jak odbijemy krawendzą paletki.
#define MIN_BALL_UP_BOUNCE_FROM_PLAYER_ANGLE 2       // Piłkę odbija od ścian bocznych w sytuacji jak odbijemy bokiem paletki a nie górą.

#define BRICK_COLUMNS 7
#define BRICK_ROWS 5
#define BRICK_HEIGHT 30
#define SPACE_BETWEEN_BRICKS 16

// Tego nie tykać, wylicza się z poprzednich.
#define PLAYER_START_POS_X (( WINDOW_WIDTH - PLAYER_WIDTH )/2 )
#define PLAYER_START_POS_Y ( WINDOW_HEIGHT - PLAYER_HEIGHT - PLAYER_SPACE_FROM_BOTTOM )

#define BALL_START_POS_X (( WINDOW_WIDTH - BALL_SIZE )/2 )
#define BALL_START_POS_Y ( PLAYER_START_POS_Y - BALL_SIZE - 10)

#define BRICK_WIDTH ( WINDOW_WIDTH - ((SPACE_BETWEEN_BRICKS * BRICK_COLUMNS) / BRICK_COLUMNS ))


SDL_Window* createWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_Window* window = SDL_CreateWindow("BlockBreaker",SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(2);
    }
    return window;
}
SDL_Renderer* createRenderer(SDL_Window* window) {

// SDL_RENDERER_ACCELERATED używanie karty graficznej
// SDL_RENDERER_PRESENTVSYNC wyrównaj do odświerzania monitora

    SDL_Renderer* renderer_SDL = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_SDL == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(3);
    }
    return renderer_SDL;
}
void handleEvents(bool &game_active, Player &player) {
    SDL_Event e;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            game_active = false;
        }
    }
    if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
        game_active = false;
    }
    if (keystate[SDL_SCANCODE_A]) {
        std::cout << "left" << std::endl;
        // Nie wylataj za mapę
        player.moveLeft();
    }
    if (keystate[SDL_SCANCODE_D]) {
        std::cout << "right" << std::endl;
        player.moveRight();
    }
}
void drawObjects(SDL_Renderer *renderer, Player &player, Ball &ball) {

    //Czyszczenie ekranu
    SDL_SetRenderDrawColor(renderer, 120, 125, 125, 255);
    SDL_RenderClear(renderer);

    // Narysuj gracza
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, player.getRect());

    // Narysuj piłkę

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, ball.getRect());



    // Wyświetl na ekran
    SDL_RenderPresent(renderer);
}
void handleCollisions(int window_width, int window_height, int maxAngleX, int maxAngleY, Player &player,  Ball &ball) {
    // Odbicia piłki od ścian
    ////Sufit
    if (ball.getY() <= 0) {
        ball.flipVertically();
    }
    //// Podłoga
    if (ball.getY() + ball.getSize() >= window_height) {
        ball.flipVertically();
        player.reduceLives();
    }
    //// Boki
    if (ball.getX() <= 0 || ball.getX() + ball.getSize() >= window_width) {
        ball.flipHorizontally();
    }
    // By gracz nie wylatał za mapę
    if (player.getX() < 0) {
        player.setX(0);
    }
    if (player.getX() + player.getW() > window_width) {
        player.setX(window_width - player.getW());
    }

    // Kolizja piłki z graczem
    if (SDL_HasIntersection(ball.getRect(), player.getRect())) {
//        ball.flipVertically();
        double relative = player.getX() + (player.getW()/2) - (ball.getX() + ball.getSize()/2);
        double normalized = relative / (player.getW()/2);
        double bounce = normalized * (5* M_PI/12);

        double new_dx = ball.getSpeed() * -sin(bounce);
        double new_dy = -ball.getSpeed() * cos(bounce);
        double transfer_speed;

        // By mi piłkę na maksa w ściany nie odbijało bo to denerwuje
//        if (new_dx > maxAngleX) {
////            1 = 8 - 7
//            transfer_speed = new_dx - maxAngleX; // zmniejsz
//            new_dx = maxAngleX;
//        }
//        else if (new_dx < -maxAngleX) {
////            -1 = -8 + 7
//            transfer_speed = -new_dx + maxAngleX;  // zwiększ
//            new_dx = -maxAngleX;
//        }
//        new_dy = new_dy - transfer_speed;
//        if (new_dy > maxAngleY) {
//            new_dx = maxAngleY;
//        }
//        else if (new_dy < -maxAngleY) {
//            new_dy = -maxAngleY;
//        }
        ball.setDx(new_dx);
        ball.setDy(new_dy);

        std::cout << ball.getDx() << ":" << ball.getDy() << ":" << ball.getSpeed()  << std::endl;
    }

}
void updateObjects(Ball &ball) {
    ball.updatePostion();
}

int main(int argc, char *argv[]) {
//    std::cout << "Hello, World!" << std::endl;

    SDL_Window* window = createWindow();
    SDL_Renderer* renderer = createRenderer(window);
    bool game_active = true;

    Player player(PLAYER_START_POS_X, PLAYER_START_POS_Y, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_SPEED);
    Ball ball(BALL_START_POS_X, BALL_START_POS_Y, BALL_SIZE, BALL_SPEED);
    Brick bricks[BRICK_COLUMNS * BRICK_ROWS];

    for ()
    Brick brick(0,0, BRICK_WIDTH, BRICK_HEIGHT);


    void setBricks(int i) {
        bricks[i].rect.x = (((i % COL) + 1) * SPACING) + ((i % COL) * bricks[i].rect.w) - (SPACING / 2);
        bricks[i].rect.y = bricks[i].rect.h * 3 + (((i % ROW) + 1) * SPACING) + ((i % ROW) * bricks[i].rect.h) - (SPACING / 2);
    }

    while (game_active) {
        Uint64 start = SDL_GetPerformanceCounter();


        handleEvents(game_active, player);
        handleCollisions(WINDOW_WIDTH, WINDOW_HEIGHT, MAX_BALL_SIDEWAYS_BOUNCE_FROM_PLAYER_ANGLE,
                         MIN_BALL_UP_BOUNCE_FROM_PLAYER_ANGLE, player, ball);
        updateObjects(ball);


        drawObjects(renderer, player, ball);




        // Cap framerate
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        SDL_Delay(floor(16.666f - elapsedMS));
//        SDL_Delay(300);
//        game_active = false;
    }



    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
