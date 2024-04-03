c++ SDL, jak zaimplementować objianie piłki od paletki w grze pong w zależności w którym miejscu paletki piłka uderzy
ChatGPT
Implementacja odbijania piłki od paletki w grze Pong przy użyciu biblioteki SDL w C++ może być zrealizowana w następujący sposób. Zakładam, że masz już zaimplementowaną logikę ruchu piłki i paletki oraz inicjalizację biblioteki SDL. Poniżej znajduje się kod, który demonstrowałby obsługę odbijania piłki w zależności od tego, w którym miejscu paletki piłka uderzy.

cpp
Copy code
#include <SDL.h>

// Wymiary okna
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Wymiary paletki
const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 100;

// Wymiary piłki
const int BALL_SIZE = 15;

// Prędkość piłki
const int BALL_SPEED = 5;

// Struktura opisująca obiekt paletki
struct Paddle {
int x, y; // Pozycja paletki
int w, h; // Wymiary paletki
};

// Struktura opisująca obiekt piłki
struct Ball {
int x, y; // Pozycja piłki
int dx, dy; // Prędkość piłki
};

// Funkcja sprawdzająca kolizję między dwoma prostokątami
bool checkCollision(SDL_Rect rectA, SDL_Rect rectB) {
int leftA = rectA.x;
int rightA = rectA.x + rectA.w;
int topA = rectA.y;
int bottomA = rectA.y + rectA.h;

    int leftB = rectB.x;
    int rightB = rectB.x + rectB.w;
    int topB = rectB.y;
    int bottomB = rectB.y + rectB.h;

    // Brak kolizji
    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
        return false;
    }

    // Kolizja
    return true;
}

int main(int argc, char* args[]) {
// Inicjalizacja SDL
SDL_Init(SDL_INIT_VIDEO);

    // Utworzenie okna
    SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Inicjalizacja paletki i piłki
    Paddle paddle;
    paddle.x = 50;
    paddle.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    paddle.w = PADDLE_WIDTH;
    paddle.h = PADDLE_HEIGHT;

    Ball ball;
    ball.x = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
    ball.y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;
    ball.dx = BALL_SPEED;
    ball.dy = BALL_SPEED;

    // Pętla główna
    bool quit = false;
    while (!quit) {
        // Obsługa zdarzeń
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Ruch paletki
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_UP] && paddle.y > 0) {
            paddle.y -= 5;
        }
        if (currentKeyStates[SDL_SCANCODE_DOWN] && paddle.y < SCREEN_HEIGHT - PADDLE_HEIGHT) {
            paddle.y += 5;
        }

        // Ruch piłki
        ball.x += ball.dx;
        ball.y += ball.dy;

        // Kolizja z górną i dolną krawędzią okna
        if (ball.y <= 0 || ball.y >= SCREEN_HEIGHT - BALL_SIZE) {
            ball.dy = -ball.dy;
        }

        // Kolizja z paletką
        SDL_Rect ballRect = {ball.x, ball.y, BALL_SIZE, BALL_SIZE};
        SDL_Rect paddleRect = {paddle.x, paddle.y, PADDLE_WIDTH, PADDLE_HEIGHT};
        if (checkCollision(ballRect, paddleRect)) {
            // Odbicie piłki w zależności od miejsca uderzenia na paletce
            int relativeIntersectY = (paddle.y + PADDLE_HEIGHT / 2) - (ball.y + BALL_SIZE / 2);
            float normalizedRelativeIntersectionY = (float)relativeIntersectY / (PADDLE_HEIGHT / 2);
            float bounceAngle = normalizedRelativeIntersectionY * (M_PI / 4); // M_PI to stała reprezentująca wartość liczby pi

            ball.dx = BALL_SPEED * cos(bounceAngle);
            ball.dy = BALL_SPEED * -sin(bounceAngle);
        }

        // Wyczyszczenie renderera
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Narysowanie paletki
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect paddleRectSDL = {paddle.x, paddle.y, PADDLE_WIDTH, PADDLE_HEIGHT};
        SDL_RenderFillRect(renderer, &paddleRectSDL);

        // Narysowanie piłki
        SDL_Rect ballRectSDL = {ball.x, ball.y, BALL_SIZE, BALL_SIZE};
        SDL_RenderFillRect(renderer, &ballRectSDL);

        // Odświeżenie renderera
        SDL_RenderPresent(renderer);
    }

    // Zwolnienie pamięci i zamknięcie SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
W tym kodzie funkcja checkCollision sprawdza kolizję między dwoma prostokątami, co jest używane do wykrycia kolizji między paletką a piłką. Następnie, w przypadku kolizji, kąt odbicia piłki jest obliczany na podstawie miejsca uderzenia piłki na paletce. W końcu, piłka jest odbijana w odpowiednim kierunku na podstawie tego kąta.