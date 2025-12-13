#pragma once
#ifdef __EMSCRIPTEN__

#include <emscripten.h>
#include <emscripten/html5.h>

#endif

// Includes EasySDL objects 
#include "../../include/EasySDL/Window.hpp"
    // Lines
    // Circles

// static elemensts
static EasySDL::Window* windowWeb = nullptr;
    // Example:
    // static EasySDL::Line * webLine = nullptr;

extern "C"{
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE
    void registerWindow(EasySDL::Window* w){
        windowWeb = w;
    }

    EMSCRIPTEN_KEEPALIVE
    int getWindowWidth(){
        if(windowWeb){
            return windowWeb->getWidth();
        }
        printf("Window es nullptr");
        return 0;
    }

    EMSCRIPTEN_KEEPALIVE
    int getWindowHeight(){
        if(windowWeb){
            return windowWeb->getHeight();
        }
        printf("Window es nullptr");
        return 0;
    }
    // Methods
#endif
}