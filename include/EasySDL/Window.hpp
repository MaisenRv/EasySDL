#pragma once

#include <SDL2/SDL.h>
#include <functional>
#include <iostream>

#include "./interface/IWindow.hpp"
#include "./utils/colors.hpp"

#ifdef __EMSCRIPTEN__

#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL_ttf.h>
#include <GLES3/gl3.h>

#else

#include <GL/glew.h>

#endif

namespace EasySDL
{
    class Window : public EasySDL::IWindow
    {
    private:
        // Window properties
        const char *_title;
        float _fps = 0;
        SDL_Window *_win;
        SDL_GLContext _context;

        const char *_canvasName;

        std::function<void()> _setup;

        std::function<void()> _drawFn; // WASM
        bool _quit = false;            // WASM

        int prepareWindow() override
        {
            if (SDL_Init(SDL_INIT_VIDEO) != 0)
            {
                std::cerr << "Error al iniciar SDL: " << SDL_GetError() << std::endl;
                return 1;
            }
            TTF_Init();
            // Settings OpenGL
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // 4× MSAA (puedes probar 8, 16, según GPU)

            this->_win = SDL_CreateWindow(
                this->_title,
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                this->_width,
                this->_height,
                SDL_WINDOW_OPENGL);

            if (!this->_win)
            {
                std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
                return 1;
            }

            this->_context = SDL_GL_CreateContext(this->_win);
            if (!this->_context)
            {
                std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << std::endl;
                return 1;
            }

            if (SDL_GL_MakeCurrent(this->_win, this->_context) != 0)
            {
                std::cerr << "SDL_GL_MakeCurrent failed: " << SDL_GetError() << std::endl;
                return 1;
            }

            SDL_GL_SetSwapInterval(1); // V‑Sync

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glViewport(0, 0, this->_width, this->_height);
            return 0;
        }

        void prepareGL() override
        {
            // Le dice como pintar los datos
            glGenVertexArrays(1, &(this->VAO));
            glBindVertexArray(this->VAO);

            // Almacena datos
            glGenBuffers(1, &(this->VBO));            // crea un buffer
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO); // lo activa

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, /*stride*/ 0, /*offset*/ 0);
            glBindVertexArray(0);
        }

    public:
        Window(int width, int height, const char *title, const char *canvasName) : _title(title), _canvasName(canvasName)
        {
            this->_width = width;
            this->_height = height;

            this->prepareWindow();
            this->prepareGL();
            glClearColor(
                DARK_BLUE_NORMALIZED[0],
                DARK_BLUE_NORMALIZED[1],
                DARK_BLUE_NORMALIZED[2],
                DARK_BLUE_NORMALIZED[3]);
        }

        void start(std::function<void()> drawFn, std::function<void()> setup) override
        {
            this->_setup = setup;
            this->_setup();
            this->_drawFn = drawFn;
            // OPENGL SETUP

#ifdef __EMSCRIPTEN__
            // _instance = this; // WASM
            emscripten_set_main_loop_arg(Window::mainLoopProxy, this, 0, 1);
#endif
        }

        void loopFrame()
        {
            SDL_Event e;
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    this->_quit = true;
#ifdef __EMSCRIPTEN__
                    // no cancelar aquí; usar stop_loop desde JS si quieres un control explícito
                    emscripten_cancel_main_loop();
#endif
                }
                
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (this->_drawFn)
                this->_drawFn();

            SDL_GL_SwapWindow(this->_win);
        }

        static void mainLoopProxy(void *arg)
        {
            Window *self = static_cast<Window *>(arg);
            if (!self->_quit)
            {
                self->loopFrame();
            }
        }
        ~Window()
        {
            glDeleteVertexArrays(1, &(this->VAO));
            glDeleteBuffers(1, &(this->VBO));
            SDL_GL_DeleteContext(this->_context);
            SDL_DestroyWindow(this->_win);
            TTF_Quit();
            SDL_Quit();
        }
    };
}
