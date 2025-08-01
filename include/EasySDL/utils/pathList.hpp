#pragma once
#include <string>
#include <SDL2/SDL.h>

namespace EasySDL{
    // Shaders
    const std::string BASIC_VERTEX_SHADER_PATH = "./include/EasySDL/shaders/vertexShader.glsl";
    const std::string BASIC_FRAGMENT_SHADER_PATH = "./include/EasySDL/shaders/fragmentShader.glsl";
    const std::string BASIC_VERTEX_TEXT_SHADER_PATH = "./include/EasySDL/shaders/vertexTextShader.glsl";
    const std::string BASIC_FRAGMENT_TEXT_SHADER_PATH = "./include/EasySDL/shaders/fragmentTextShader.glsl"; 
    const std::string SHIFT_VERTEX_SHADER_PATH = "./include/EasySDL/shaders/shiftVertexShader.glsl";
    // Fonts
    const std::string POPPINS_REGULAR = "./include/EasySDL/objects/text/fonts/Poppins-Regular.ttf";
    // Colors
        // NORMALIZED
    const float RED_PINKY_NORMALIZED[4]     = {0.9882, 0, 0.3137, 1.0};
    const float MINT_GREEN_NORMALIZED[4]    = { 0.0039f, 0.9412f, 0.5686f, 1.0f };
    const float LIGHT_CYAN_NORMALIZED[4]    = { 0.0039f, 0.7922f, 0.8824f, 1.0f };
    const float GOLDEN_YELLOW_NORMALIZED[4] = { 0.9529f, 0.8980f, 0.3765f, 1.0f };
    const float WHITE_NORMALIZED[4]         = {1.0, 1.0, 1.0, 1.0};
        // RGBA
    const SDL_Color WHITE_SDL = {255,255,255,255};

}