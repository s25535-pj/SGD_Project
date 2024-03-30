#include <SDL.h>
#include <cmath>
#include <vector>
#include <iostream>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

#define BALL_SPEED 12
#define BALL_SIZE 16

#define BRICK_COLUMNS 7
#define BRICK_ROWS 5
#define BRICK_HEIGHT 30
#define SPACING_BETWEEN_BRICKS 16

#define PLAYER_HEIGHT 12
#define PLAYER_WIDTH 100
#define PLAYER_SPEED 13
#define SPACE_FROM_BOTTOM 100

//##################################################

class Player {
private:
    int x, y;
    int width, height;
    int speed;
    int liveCount = 3;

public:
    Player(int x, int y, int height, int width, int speed) : x(x), y(y), width(width), height(height), speed(speed) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getLiveCount() const { return liveCount; }

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }

    void setLiveCount(int lives) {
        this->liveCount = lives;
    }
    void setStartingPosition(int window_width) {
        x = window_width/2 - width/2;
    }

    void reduceLifeCount() {
        liveCount--;
    }

    void moveLeft() {
        x -= speed;
        std::cout << x << std::endl;
    }
    void moveRight() {
        x += speed;
        std::cout << x << std::endl;
    }


};

class Ball {
private:
    int x, y;
    int dx, dy;
    int size;
    float velocity_x, velocity_y;
    int speed;

public:
    Ball(int x, int y, int size, int dx, int dy, int speed) : x(x), y(y), size(size), dx(dx), velocity_x(velocity_x), velocity_y(velocity_y), dy(dy), speed(speed) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return dx; }
    int getHeight() const { return dy; }
    float getVelocity_x() const { return velocity_x; }
    float getVelocity_y() const { return velocity_y; }

    void setVelocity_x(float vel_x) {
        this->velocity_x = vel_x;
    }

    void setVelocity_y(float vel_y) {
        this->velocity_y = vel_y;
    }

    void setStartingPosition(Player player) {
        y = player.getY() - player.getHeight() * 4;
    }

    void resetSpeed(int widow_width,int ball_size, float ball_speed) {
        velocity_y = ball_speed/2;
        velocity_x = 0;
        x = widow_width/2 - (ball_size/2);
    }

    void detectPlayerCollision(Player player, SDL_Rect ball_SDL, SDL_Rect player_SDL) {
        if(SDL_HasIntersection(&ball_SDL, &player_SDL)) {
            // Różnica między środkiem playera a środkiem piłki
            double relative_position = (player.getX() + (player.getWidth()/2)) - (x + (size / 2));
            double norm = relative_position / (player.getWidth()/2);
            double bounce = norm * (5 * M_PI / 12);

            velocity_y = -speed * cos(bounce);
            velocity_x = speed * -sin(bounce);
        }
    }

    bool detectWallCollisionPlayerMissedBall(int window_width ,int window_height) {

        // Piłka uderzyła w sufit
        if(y <= 0) {
            velocity_y = -velocity_y;
        }

        // Piłka uderzyła w podłogę
        if (y + size >= window_height) {
            velocity_y = -velocity_y;
            return true;
        }

        // Piłka uderzyła w boczną ścianę
//        if (x <= 0 || x + size >= window_width) {
////            velocity_x = -velocity_x;
//        }
    }

    void updatePosition() {
        x += velocity_x;
        y += velocity_y;
    }

};


//##################################################

int frameCount, timerFPS, fps;
Uint64 lastFrame;

//float velY, velX;
//int liveCount;
//bool bricks[BRICK_ROWS * BRICK_COLUMNS];

void resetGame(Player player, Ball ball, bool *bricks) {

    player.setLiveCount(3);
    player.setStartingPosition(WINDOW_WIDTH);
    ball.setStartingPosition(player);
    ball.resetSpeed(WINDOW_WIDTH, BALL_SIZE, BALL_SPEED);

    for (int i = 0; i < BRICK_COLUMNS * BRICK_ROWS; i++) {
        bricks[i] = true;
    }

}

void placeOneBrick(int i, SDL_Rect brick_SDL) {
    brick_SDL.w = (WINDOW_WIDTH - (SPACING_BETWEEN_BRICKS * BRICK_COLUMNS)) / BRICK_COLUMNS;
    brick_SDL.h = BRICK_HEIGHT;
    brick_SDL.x = (((i % BRICK_COLUMNS) + 1) * SPACING_BETWEEN_BRICKS) + ((i % BRICK_COLUMNS) * brick_SDL.w) - (SPACING_BETWEEN_BRICKS / 2);
    brick_SDL.y = brick_SDL.h * 3 + (((i % BRICK_ROWS) + 1) * SPACING_BETWEEN_BRICKS) + ((i % BRICK_ROWS) * brick_SDL.h) - (SPACING_BETWEEN_BRICKS / 2);
}

void runOneFrame(SDL_Rect player_SDL, SDL_Rect ball_SDL, SDL_Rect brick_SDL, Player player, Ball ball,  bool *bricks) {

    if(player.getLiveCount() < 0) {
        resetGame(player, ball, bricks);
    }
    ball.detectPlayerCollision(player, ball_SDL, player_SDL);


//    if(ball.detectWallCollisionPlayerMissedBall(WINDOW_WIDTH, WINDOW_HEIGHT)) {
//        player.reduceLifeCount();
//    }

    ball.updatePosition();

    // Player went off board
    if (player.getX() < 0) {
        player.setX(0);
    }
    if (player.getX() + player.getWidth() > WINDOW_WIDTH) {
        player.setX(WINDOW_WIDTH - player.getWidth());
    }

    bool reset = true;

    for(int i=0; i < BRICK_COLUMNS * BRICK_ROWS; i++) {
        placeOneBrick(i, brick_SDL);
        if(SDL_HasIntersection(&ball_SDL, &brick_SDL) && bricks[i]) {
            bricks[i] = false;
            if(ball.getX() >= brick_SDL.x) {ball.setVelocity_x(-ball.getVelocity_x());}
            if(ball.getX() <= brick_SDL.x) {ball.setVelocity_x(-ball.getVelocity_x());}
            if(ball.getY() <= brick_SDL.y) {ball.setVelocity_y(-ball.getVelocity_y());}
            if(ball.getY() >= brick_SDL.y) {ball.setVelocity_y(-ball.getVelocity_y());}
        }
        if(bricks[i]) {
            reset = false;
        }
    }
    if (reset) {
        resetGame(player,ball, bricks);
    }
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
        player.moveLeft();
    }
    if (keystate[SDL_SCANCODE_D]) {
        player.moveRight();
        std::cout << "right" << std::endl;
    }

}

void render(SDL_Renderer *renderer_SDL, SDL_Rect &bricks_SDL, SDL_Rect &player_SDL, SDL_Rect &ball_SDL, Player &player, Ball &ball, bool *bricks) {
    // Czyszczenie ekranu co każdy raz
    SDL_SetRenderDrawColor(renderer_SDL, 120, 125, 125, 255);
    SDL_RenderClear(renderer_SDL);

    frameCount++;
    timerFPS=SDL_GetTicks64()-lastFrame;
    if(timerFPS<(1000/60)) {
        SDL_Delay((1000/60)-timerFPS);
    }
//    std::cout << "Drawing" << std::endl;
    SDL_SetRenderDrawColor(renderer_SDL, 255, 255, 255, 255);

    std::cout << player.getX() << std::endl;
    player_SDL.x = player.getX();



    SDL_RenderFillRect(renderer_SDL, &player_SDL);
    SDL_RenderFillRect(renderer_SDL, &ball_SDL);

    for(int i=0; i < BRICK_COLUMNS * BRICK_ROWS; i++) {
        SDL_SetRenderDrawColor(renderer_SDL, 255, 0, 0, 255);
        if(i%2==0)SDL_SetRenderDrawColor(renderer_SDL, 0,255, 0, 255);
        if(bricks[i]) {
            placeOneBrick(i, bricks_SDL);
            SDL_RenderFillRect(renderer_SDL, &bricks_SDL);
        }
    }
//    std::cout << "Presenting" << std::endl;
    SDL_RenderPresent(renderer_SDL);
}
//#########################################################################################################################

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

//#########################################################################################################################


int main(int argc, char *argv[]) {

    SDL_Window* window = createWindow();
    SDL_Renderer* renderer_SDL = createRenderer(window);
    bool game_active = true;

    Player player(WINDOW_WIDTH/2 - PLAYER_WIDTH/2, WINDOW_HEIGHT - SPACE_FROM_BOTTOM - PLAYER_HEIGHT, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_SPEED);
    Ball ball(BALL_SIZE, BALL_SIZE, BALL_SIZE, 1, 1, BALL_SPEED);
    bool bricks[BRICK_ROWS * BRICK_COLUMNS];

    SDL_Rect player_SDL ={player.getX(), player.getY(), player.getWidth(), player.getHeight()};
    SDL_Rect ball_SDL = {ball.getX(), ball.getY(), ball.getWidth(), ball.getHeight()};
    SDL_Rect brick_SDL;

//    resetGame(player, ball, bricks);

    static int lastTime=0;
    while(game_active) {
        lastFrame = SDL_GetTicks64();
        if(lastFrame >= lastTime+1000) {
            lastTime = lastFrame;
            fps = frameCount;
            frameCount = 0;
        }

        handleEvents(game_active, player);
//        player_SDL.x = player.getX();
//        if(player.getLiveCount() < 0) {
//            resetGame(player, ball, bricks);
//        }
//        ball.detectPlayerCollision(player, ball_SDL, player_SDL);



//        runOneFrame(player_SDL, ball_SDL, brick_SDL, player, ball, bricks);
        render(renderer_SDL, brick_SDL, player_SDL, ball_SDL, player, ball, bricks);

    }

    SDL_DestroyRenderer(renderer_SDL);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}