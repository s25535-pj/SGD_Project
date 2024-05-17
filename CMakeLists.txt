cmake_minimum_required(VERSION 3.27)
project(BrickBreaker)

set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} main.cpp
        Window.h
        Window.cpp
        GameObject.h
        GameObject.cpp
        Player.h
        Player.cpp
        Ball.cpp
        Ball.h
        Brick.cpp
        Brick.h
        Collisions.cpp
        Collisions.h
)

set(TEXTURES_DIR "${CMAKE_SOURCE_DIR}/textures/")
target_compile_definitions(${PROJECT_NAME} PRIVATE TEXTURES_DIR="${TEXTURES_DIR}")
target_link_libraries(${PROJECT_NAME} -lmingw32 -lSDL2main -lSDL2_image -lSDL2 -mwindows)
