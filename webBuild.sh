#!/bin/bash
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
  --preload-file ./src/presentacion/albert_einstein.json \
  -o ./bin/web/eje2.js

# em++ $1 \
#   -O2 \
#   -s WASM=1 \
#   -s USE_SDL=2 \
#   -s USE_SDL_TTF=2 \
#   -s MIN_WEBGL_VERSION=2 \
#   -s MAX_WEBGL_VERSION=2 \
#   -s ALLOW_MEMORY_GROWTH=1 \
#   -s USE_WEBGL2=1 \
#   --preload-file ./include/EasySDL/shaders/vertexShader.glsl \
#   --preload-file ./include/EasySDL/shaders/fragmentShader.glsl \
#   --preload-file ./include/EasySDL/shaders/vertexTextShader.glsl \
#   --preload-file ./include/EasySDL/shaders/fragmentTextShader.glsl \
#   --preload-file ./include/EasySDL/objects/text/fonts/Poppins-Regular.ttf \
#   --preload-file ./src/presentacion/albert_einstein.json \
#   -o ./bin/web/prueba.js




# em++ $1 \
#   -O2 \
#   -s WASM=1 \
#   -s USE_SDL=2 \
#   -s USE_SDL_TTF=2 \
#   -s MIN_WEBGL_VERSION=2 \
#   -s MAX_WEBGL_VERSION=2 \
#   -s ALLOW_MEMORY_GROWTH=1 \
#   -s USE_WEBGL2=1 \
#   --preload-file ./include/EasySDL/shaders/vertexShader.glsl \
#   --preload-file ./include/EasySDL/shaders/fragmentShader.glsl \
#   -Iinclude \
#   -s EXPORTED_RUNTIME_METHODS="['cwrap','ccall']" \
#   -s EXPORTED_FUNCTIONS="['_main','_setLineWidth','_registerLine']" \
#   -o ./bin/web/prueba.js
