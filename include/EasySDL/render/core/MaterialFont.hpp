#pragma once
#include "../../utils/colors.hpp"
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace EasySDL{
    struct MaterialFont{
        SDL_Color color = WHITE_SDL;
        GLuint textTexture;
        bool textureDirty = true;

        void del(){
            glDeleteTextures(1, &textTexture);
        }
    };
}