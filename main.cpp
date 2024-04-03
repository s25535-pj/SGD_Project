#include <SDL.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <memory>
#include "Player.h"
#include "Ball.h"
#include "Brick.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

#define PLAYER_WIDTH 150
#define PLAYER_HEIGHT 12
#define PLAYER_SPEED 10
#define PLAYER_SPACE_FROM_BOTTOM 100

#define BALL_SPEED 10
#define BALL_SIZE 30

#define MAX_BALL_SIDEWAYS_BOUNCE_OF_PLAYER 0.5 // Jak mocno piłkę może odbić w bok max: 1

#define BRICK_COLUMNS 10
#define BRICK_ROWS 5
#define BRICK_HEIGHT 30
#define VERTICAL_SPACE_BETWEEN_BRICKS 30
#define HORIZONTAL_SPACE_BETWEEN_BRICKS 30

#define SPACE_FROM_SCREEN_TOP 20

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
void drawObjects(SDL_Renderer *renderer, Player &player, Ball &ball, Brick (bricks)[][BRICK_COLUMNS]) {

    //Czyszczenie ekranu
    SDL_SetRenderDrawColor(renderer, 120, 125, 125, 255);
    SDL_RenderClear(renderer);

    // Narysuj gracza
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, player.getRect());

    // Narysuj piłkę

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, ball.getRect());

    // Narysuj cegły

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//    for (auto& row : bricks) {
//        for (Brick brick : row) {
//            if (brick.getIsVisible()) {
//                SDL_RenderFillRect(renderer, brick.getRect());
////                std::cout << "x,y: " << brick.getX() << " " << brick.getY() << std::endl;
////                std::cout << "w,z: " << brick.getW() << " " << brick.getH() << std::endl;
//            }
//        }
////        std::cout << std::endl;
//    }

    for (int i = 0; i < BRICK_ROWS; ++i) {
        for (int j = 0; j < BRICK_COLUMNS; ++j) {
            if (bricks[i][j].getIsVisible()) {
                SDL_RenderFillRect(renderer, bricks[i][j].getRect());
            }
        }
    }


    // Wyświetl na ekran
    SDL_RenderPresent(renderer);
}
void handleCollisions(int window_width, int window_height, double maxSidewaysBounce, Player &player,  Ball &ball, Brick (bricks)[][BRICK_COLUMNS]) {
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
        // Liczenie odległości między graczem a piłką
        double relative = player.getX() + (player.getW()/2) - (ball.getX() + ball.getSize()/2);
        // Skalowanie od -1 do 1
        double normalized = relative / (player.getW()/2);

        if (normalized > maxSidewaysBounce) {
            normalized = maxSidewaysBounce;
        } else if (normalized < -maxSidewaysBounce) {
            normalized = -maxSidewaysBounce;
        }
//        std::cout << normalized << std::endl;
        double bounce = normalized * (5* M_PI/12);

        ball.setDx(ball.getSpeed() * -sin(bounce));
        ball.setDy(-ball.getSpeed() * cos(bounce));

//        std::cout << ball.getDx() << ":" << ball.getDy() << ":" << ball.getSpeed()  << std::endl;
    }

    // Kolizja piłki z cegłami
    for (int i = 0; i < BRICK_ROWS; ++i) {
        for (int j = 0; j < BRICK_COLUMNS; ++j) {
            if (bricks[i][j].getIsVisible() && SDL_HasIntersection(ball.getRect(), bricks[i][j].getRect())) {
                std::cout << "Ball killed brick: " << bricks[i][j].getX() << " " << bricks[i][j].getY() << std::endl;
                bricks[i][j].setIsVisible(false);
                ball.flipVertically();
            }
        }
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

//    std::vector<std::vector<Brick>> *bricks;
//
////     Tworzenie Cegieł
//    for (int i = 0; i < BRICK_ROWS; ++i) {
//        std::vector<Brick> row;
//        for (int j = 0; j < BRICK_COLUMNS; ++j) {
//            int brickWidth = (WINDOW_WIDTH / BRICK_COLUMNS) - HORIZONTAL_SPACE_BETWEEN_BRICKS;
//            int space_from_screen_sides = (WINDOW_WIDTH - (BRICK_COLUMNS * brickWidth + (BRICK_COLUMNS - 1) * HORIZONTAL_SPACE_BETWEEN_BRICKS)) / 2;
//
//            int x = space_from_screen_sides + j * (brickWidth + HORIZONTAL_SPACE_BETWEEN_BRICKS);
//            int y = SPACE_FROM_SCREEN_TOP + i * (BRICK_HEIGHT + VERTICAL_SPACE_BETWEEN_BRICKS);
//
//            row.push_back(Brick(x, y, brickWidth, BRICK_HEIGHT));
//        }
//        bricks.push_back(row);
//    }

    Brick bricks[BRICK_ROWS][BRICK_COLUMNS];
//     Tworzenie Cegieł
    for (int i = 0; i < BRICK_ROWS; ++i) {
        for (int j = 0; j < BRICK_COLUMNS; ++j) {
            int brickWidth = (WINDOW_WIDTH / BRICK_COLUMNS) - HORIZONTAL_SPACE_BETWEEN_BRICKS;
            int space_from_screen_sides = (WINDOW_WIDTH - (BRICK_COLUMNS * brickWidth + (BRICK_COLUMNS - 1) * HORIZONTAL_SPACE_BETWEEN_BRICKS)) / 2;

            int x = space_from_screen_sides + j * (brickWidth + HORIZONTAL_SPACE_BETWEEN_BRICKS);
            int y = SPACE_FROM_SCREEN_TOP + i * (BRICK_HEIGHT + VERTICAL_SPACE_BETWEEN_BRICKS);

            bricks[i][j] = Brick(x, y, brickWidth, BRICK_HEIGHT);
        }
    }

    while (game_active) {
        Uint64 start = SDL_GetPerformanceCounter();

        handleEvents(game_active, player);
        handleCollisions(WINDOW_WIDTH, WINDOW_HEIGHT, MAX_BALL_SIDEWAYS_BOUNCE_OF_PLAYER, player, ball, bricks);
        updateObjects(ball);
        drawObjects(renderer, player, ball, bricks);


        // Cap framerate
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        SDL_Delay(floor(16.666f - elapsedMS));
//        SDL_Delay(3000);
//        game_active = false;
    }



    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
