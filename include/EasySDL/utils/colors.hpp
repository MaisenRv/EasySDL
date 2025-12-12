#pragma once
#include <SDL2/SDL.h>

namespace EasySDL
{
    // NORMALIZED
    const float DARK_BLUE_NORMALIZED[4] = {0.0431f, 0.0667f, 0.1020f, 1.0f};
    const float RED_PINKY_NORMALIZED[4] = {0.9882f, 0, 0.3137f, 1.0f};
    const float MINT_GREEN_NORMALIZED[4] = {0.0039f, 0.9412f, 0.5686f, 1.0f};
    const float LIGHT_CYAN_NORMALIZED[4] = {0.0039f, 0.7922f, 0.8824f, 1.0f};
    const float GOLDEN_YELLOW_NORMALIZED[4] = {0.9529f, 0.8980f, 0.3765f, 1.0f};
    const float WHITE_NORMALIZED[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    // RGBA
    const SDL_Color WHITE_SDL = {255, 255, 255, 255};
}