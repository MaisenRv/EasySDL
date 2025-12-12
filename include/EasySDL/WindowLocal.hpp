#pragma once

#include <SDL2/SDL.h>
#include <functional>
#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL_ttf.h>

#include "./interface/IWindow.hpp"
#include "./utils/colors.hpp"

namespace EasySDL
{
    class WindowLocal : public EasySDL::IWindow
    {
    private:
        // Window properties
        const char *_title;
        SDL_Window *_win;
        SDL_GLContext _context;

        std::function<void()> _setup;

        std::function<void()> _drawFn;

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
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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

            this->_context = SDL_GL_CreateContext(this->_win);
            SDL_GL_MakeCurrent(this->_win, this->_context);
            SDL_GL_SetSwapInterval(1); // V‑Sync
            glEnable(GL_LINE_SMOOTH);
            glEnable(GL_MULTISAMPLE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glewExperimental = GL_TRUE;
            if (glewInit() != GLEW_OK)
            {
                std::cerr << "Error inicializando GLEW\n";
                return 1;
            }
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
        WindowLocal(int width, int height, const char *title) : _title(title)
        {
            this->_width = width;
            this->_height = height;
            this->prepareWindow();
            glClearColor(
                DARK_BLUE_NORMALIZED[0],
                DARK_BLUE_NORMALIZED[1],
                DARK_BLUE_NORMALIZED[2],
                DARK_BLUE_NORMALIZED[3]
            );          
            this->prepareGL();
        }

        void start(std::function<void()> drawFn, std::function<void()> setup) override
        {

            this->_setup = setup;
            this->_setup();

            this->_drawFn = drawFn;
            // OPENGL SETUP

            bool running = true;
            SDL_Event e;
            while (running)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                        running = false;
                    // Other events
                }

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // DRAW
                this->_drawFn();
                this->calFPS();
                SDL_GL_SwapWindow(this->_win);
            }
        }

        ~WindowLocal()
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