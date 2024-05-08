cmake_minimum_required(VERSION 3.27)
project(BrickBreaker)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
#set(SDL2_INCLUDE_DIR "G:/Clion projects/${PROJECT_NAME}/SDL2/include")
#set(SDL2_LIB_DIR "G:/Clion projects/${PROJECT_NAME}/SDL2/lib/x64")

include_directories(${SDL2_INCLUDE_DIR})
#link_directories(${SDL2_LIB_DIR})

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

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows)
# Tylko tak mi zadziałało: https://www.youtube.com/watch?v=7sIBklOTImI