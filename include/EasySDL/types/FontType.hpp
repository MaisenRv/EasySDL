
#include <string>
#ifdef __EMSCRIPTEN__
#include <SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

namespace EasySDL{
    struct FontType
    {
        TTF_Font *font;

        FontType(const std::string &fontPath,int fontSize){
          font = TTF_OpenFont(fontPath.c_str(), fontSize);  
        }

        void close(){
            TTF_CloseFont(font);
        }
    };
}