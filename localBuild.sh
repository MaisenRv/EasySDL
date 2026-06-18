#!/bin/bash
# g++ src/pruebas/main.cpp -o ./bin/app $(pkg-config --cflags --libs sdl2 glew SDL2_ttf)


# g++ $1 -o ./bin/app \
#     $(pkg-config --cflags --libs sdl2 SDL2_ttf) \
#     -lGLEW -lGL


# Uso: ./localBuild.sh Pendulum  o  ./localBuild.sh interpolation
DEMO_SELECCIONADO=${1:-"template"} # Si no pasas nada, usa template

mkdir -p build_local
cd build_local

# Pasamos el nombre del demo a CMake usando -DDEMO=...
cmake -DCMAKE_BUILD_TYPE=Release -DDEMO=$DEMO_SELECCIONADO ..
cmake --build .
