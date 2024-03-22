//#include <iostream>
//#include <SDL2/SDL.h>
//
//int main(int argc, char* args[]) {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}

#include <SDL.h>
int main( int argc, char* args[] ) {
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );
    auto window = SDL_CreateWindow( "Okienko SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );
    SDL_Delay(3000);
    SDL_DestroyWindow( window );
    //Quit SDL
    SDL_Quit();
    return 0;
}
