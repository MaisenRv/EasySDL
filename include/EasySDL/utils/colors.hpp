#pragma once
#include <SDL2/SDL.h>

namespace EasySDL{
    // NORMALIZED
    const float RED_PINKY_NORMALIZED[4]     = {0.9882, 0, 0.3137, 1.0};
    const float MINT_GREEN_NORMALIZED[4]    = { 0.0039f, 0.9412f, 0.5686f, 1.0f };
    const float LIGHT_CYAN_NORMALIZED[4]    = { 0.0039f, 0.7922f, 0.8824f, 1.0f };
    const float GOLDEN_YELLOW_NORMALIZED[4] = { 0.9529f, 0.8980f, 0.3765f, 1.0f };
    const float WHITE_NORMALIZED[4]         = {1.0, 1.0, 1.0, 1.0};
    // RGBA
    const SDL_Color WHITE_SDL = {255,255,255,255};
}