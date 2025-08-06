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
}