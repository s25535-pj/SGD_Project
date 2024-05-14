#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <memory>
#include "macros.h"
#include "Window.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "Collisions.h"


void handleEvents(bool &gameActive, Player* player) {
    SDL_Event event;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameActive = false;
        }
    }
    if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
        gameActive = false;
    }
    if (keystate[SDL_SCANCODE_A]) {
        player->moveLeft();
    }
    if (keystate[SDL_SCANCODE_D]) {
        player->moveRight();
    }
    if (keystate[SDL_SCANCODE_W]) {
        player->moveUp();
    }
    if (keystate[SDL_SCANCODE_S]) {
        player->moveDown();
    }
}

void setUpBricks(Window* window, Brick* bricks[BRICK_ROWS][BRICK_COLUMNS]) {
    for (int i = 0; i < BRICK_ROWS; ++i) {
        for (int j = 0; j < BRICK_COLUMNS; ++j) {
            int brickWidth = (WINDOW_WIDTH / BRICK_COLUMNS) - HORIZONTAL_SPACE_BETWEEN_BRICKS;
            int space_from_screen_sides = (WINDOW_WIDTH - (BRICK_COLUMNS * brickWidth + (BRICK_COLUMNS - 1) * HORIZONTAL_SPACE_BETWEEN_BRICKS)) / 2;

            int x = space_from_screen_sides + j * (brickWidth + HORIZONTAL_SPACE_BETWEEN_BRICKS);
            int y = SPACE_FROM_SCREEN_TOP + i * (BRICK_HEIGHT + VERTICAL_SPACE_BETWEEN_BRICKS);

            bricks[i][j] = new Brick(x, y, brickWidth, BRICK_HEIGHT);
            window->saveObjectToList(bricks[i][j]);
        }
    }
}

void debugBricks(Brick* bricks[BRICK_ROWS][BRICK_COLUMNS]) {
    std::cout <<"============="<< std::endl;
    for (int i = 0; i < BRICK_ROWS; ++i) {
        for (int j = 0; j < BRICK_COLUMNS; ++j) {
            if (bricks[i][j]->alive) {
                std::cout << "1";
            } else {
                std::cout << "0";
            }
        }
        std::cout << std::endl;
    }
    std::cout <<"============="<< std::endl;
}

int main(int argc, char *argv[]) {

    int playerStartingPosX = (WINDOW_WIDTH/2) - (PLAYER_WIDTH/2);
    int playerStartingPosY = WINDOW_HEIGHT - PLAYER_HEIGHT - PLAYER_SPACE_FROM_BOTTOM;

    int ballStartingPosX = (WINDOW_WIDTH/2) - (BALL_WIDTH/2);
    int ballStartingPosY = WINDOW_HEIGHT/2;
    bool gameActive = true;

    std::unique_ptr<Window> window = std::make_unique<Window>();
    std::unique_ptr<Collisions> collisions = std::make_unique<Collisions>();

    auto* player = new Player(playerStartingPosX,playerStartingPosY,PLAYER_WIDTH, PLAYER_HEIGHT);
    window->saveObjectToList(player);

    auto* ball = new Ball(ballStartingPosX,ballStartingPosY, BALL_WIDTH, BALL_HEIGHT);
    window->saveObjectToList(ball);

    Brick* bricks[BRICK_ROWS][BRICK_COLUMNS];
    setUpBricks(window.get(), bricks);

    // Pętla gry
    while (gameActive) {
        Uint64 start = SDL_GetPerformanceCounter();
        //================================

        handleEvents(gameActive, player);

        collisions->handleAllCollisions(player, ball, bricks);
//        player->loadTexture();
        window->updateAllObjects();
        window->drawAllObjects();
//        debugBricks(bricks);

        //================================
        Uint64 end = SDL_GetPerformanceCounter();
        double elapsedMS = (end - start) / SDL_GetPerformanceFrequency() * 1000.0f;
        SDL_Delay(floor(16.666f - elapsedMS));
    }

    SDL_Quit();
    return 0;
}



//class witaj {
//    int number = 0;

//public:
//    witaj();
//    witaj(int number) : number(number){}
//    ~witaj(){
//        number = 0;
//    };
//
//
//
//};

//void fun(witaj* name[TEST][TEST]) {
//    std::unique_ptr<witaj> nazwa = std::make_unique<witaj>();
//    nazwa->std::get();
//
//    int number = rand();
//    std::vector<int> cyfry;
//    cyfry.push_back(1);
//    cyfry.
//}

//int main() {
//    int zmienna_testowa;
//    std::cout << "Press enter to end program" << std::endl;
//    std::cin.get();
//
//    witaj* name[TEST][TEST];
//
//    for (int i = 0; i != TEST; i++) {
//        for (int j = 0; j != TEST; j++) {
//            // Dla każdej kolumny w wierszu
//            witaj* name1 = new witaj(10);
//            name[i][j] = name1;
//        }
//    }
//
//    fun(name);
//    return 0;

//}

//class Functions {
//
//    int number = 0;
//
//public:
//
//    Functions(){
//        number = rand();
//    }
//
//    ~Functions(){
//        number = 0;
//    };
//
//    void printNumber() {
//        std::cout << number << std::endl;
//    }
//    void printHello() {
//        std::cout << "Hello form function" << std::endl;
//    }
//
//};
//
//
//class Manager {
//
//public:
//
//    std::vector<Functions*> funlist;
//
//    Manager(){}
//    ~Manager(){}
//
//    Functions* returnFunction() {
//        Functions* function = new Functions();
//        funlist.push_back(function);
//        return function;
//    }
//
//    void deleteFunction(Functions* function) {
//        delete function;
//        std::cout << "deleted" << std::endl;
//    }
//};

//#include "TestClass.h"
//int main() {
//    TestClass test;
//    test.saySomething("lasvegas");
////    Manager man;
////
////    Functions* fun1 = man.returnFunction();
////    fun1->printNumber();
////    fun1->printHello();
////
////    man.deleteFunction(fun1);
//
//    // Functions fun2;
//    // fun2.printnumber();
//
//    return 0;
//}

