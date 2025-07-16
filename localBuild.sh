#!/bin/bash
# g++ src/pruebas/main.cpp -o ./bin/app $(pkg-config --cflags --libs sdl2 glew SDL2_ttf)


g++ $1 -o ./bin/app \
    $(pkg-config --cflags --libs sdl2 SDL2_ttf) \
    -lGLEW -lGL
