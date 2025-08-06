#!/bin/bash
# em++ src/pruebas/main.cpp -O2 -s WASM=1 -s USE_SDL=2 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2  -s ALLOW_MEMORY_GROWTH=1 -s USE_WEBGL2=1 --preload-file ./include/EasySDL/shaders/vertexShader.glsl --preload-file ./include/EasySDL/shaders/fragmentShader.glsl -o ./bin/web/prueba.js
em++ $1 \
  -O2 \
  -s WASM=1 \
  -s USE_SDL=2 \
  -s USE_SDL_TTF=2 \
  -s MIN_WEBGL_VERSION=2 \
  -s MAX_WEBGL_VERSION=2 \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s USE_WEBGL2=1 \
  --preload-file ./include/EasySDL/shaders/vertexShader.glsl \
  --preload-file ./include/EasySDL/shaders/fragmentShader.glsl \
  --preload-file ./include/EasySDL/shaders/vertexTextShader.glsl \
  --preload-file ./include/EasySDL/shaders/fragmentTextShader.glsl \
  --preload-file ./include/EasySDL/objects/text/fonts/Poppins-Regular.ttf \
  -o ./bin/web/prueba.js
