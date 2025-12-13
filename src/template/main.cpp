// Template for Web Assembly

// EasySDL objects 
#include "../../include/EasySDL/Window.hpp"

// Includes

// Bindings
#include "wasm_bindings.hpp" 


extern "C" {
    void registerWindow(EasySDL::Window*);
    // Extern methods
        // register methods
}


int main(){
    // Change "WindowName" and "#canvasName"
    static EasySDL::Window *w = new EasySDL::Window(600, 600, "WindowName","#canvasName");

    // Create shapes
        // circles
        // Lines

    // Call extern methods
    registerWindow(w);
        // bindings for web
    

    // Setop method
    auto setup = [&](){

    };
    // draw method
    auto draw = [&](){
        // Update 
        // Draw 
    };

    w->start(draw, setup);
}