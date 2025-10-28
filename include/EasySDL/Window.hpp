#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <functional>
#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

namespace EasySDL
{
    class Window
    {
    private:
        int _width;
        int _height;
        const char *_title;
        SDL_Window *_win;
        SDL_GLContext _context;
        float _fps = 0;

        std::function<void()> _setup;

        std::function<void()> _drawFn; // WASM
        bool _quit = false;            // WASM
        int prepareWindow()
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
#ifdef __EMSCRIPTEN__
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

            // Crear contexto WebGL2 antes de SDL
            EmscriptenWebGLContextAttributes attrs;
            emscripten_webgl_init_context_attributes(&attrs);
            attrs.majorVersion = 2;
            attrs.minorVersion = 0;
            attrs.antialias = true;
            EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx =
                emscripten_webgl_create_context("#canvas", &attrs);
            emscripten_webgl_make_context_current(ctx);
#else
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

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

        void prepareGL()
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
        GLuint VBO;
        GLuint VAO;

        static Window *_instance; // WASM;
        Window(int width, int height, const char *title) : _width(width), _height(height), _title(title)
        {
            this->prepareWindow();
            glClearColor(
                11.0f / 255.0f, // R
                17.0f / 255.0f, // G
                26.0f / 255.0f, // B
                1.0f);          // A
            this->prepareGL();
        }

        void start(std::function<void()> drawFn, std::function<void()> setup)
        {

            this->_setup = setup;
            this->_setup();

            this->_drawFn = drawFn;
            // OPENGL SETUP

#ifdef __EMSCRIPTEN__
            _instance = this; // WASM
            emscripten_set_main_loop(mainLoopWrapper, 0, 1);
#else

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
                this->showFPS(); 
                SDL_GL_SwapWindow(this->_win);
            }
#endif
        }

        static void mainLoopWrapper()
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    _instance->_quit = true;
#ifdef __EMSCRIPTEN__
                    emscripten_cancel_main_loop();
#endif
                }
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // DRAW
            _instance->_drawFn();

            SDL_GL_SwapWindow(_instance->_win);
        }
        int getWidth()
        {
            return this->_width;
        }
        int getHeight()
        {
            return this->_height;
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

        void showFPS(){
            static Uint32 lastTime = SDL_GetTicks();
            static int frames = 0;
            static float fps = 0.0f;

            Uint32 currentTime = SDL_GetTicks();
            frames++;

            if (currentTime - lastTime >= 1000) {
                fps = frames * 1000.0f / (currentTime - lastTime);
                this->_fps = fps;
                frames = 0;
                lastTime = currentTime;
            }
        }
        float getFPS(){
            return this->_fps;
        }
    };
    Window *Window::_instance = nullptr;
}
