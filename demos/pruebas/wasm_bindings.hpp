#pragma once
#ifdef __EMSCRIPTEN__

#include <emscripten.h>
#include <emscripten/html5.h>

#endif
#include "../../include/EasySDL/objects/shape/line/Line.hpp"

static EasySDL::Line * webLine = nullptr;


extern "C" {
#ifdef __EMSCRIPTEN__
    // registrar desde C++ cuál es la línea que queremos controlar
    EMSCRIPTEN_KEEPALIVE
    void registerLine(EasySDL::Line* linePtr) {
        webLine = linePtr;
    }

    // función que llamará JS para cambiar el grosor
    EMSCRIPTEN_KEEPALIVE
    void setLineWidth(float w) {
        if (webLine) {
            printf("Cambiando grosor a: %f\n", w);
            webLine->setWidth(w);
        }else {
            printf("webLine es nullptr\n");
        }
    }
#endif
}