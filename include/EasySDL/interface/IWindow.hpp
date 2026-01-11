#pragma once
#include <SDL2/SDL.h>
#include <functional>
#include <GL/glew.h>
#include "../utils/mouseState.hpp"

namespace EasySDL
{
    class IWindow
    {
    protected:
        int _width;
        int _height;
        MouseState _mouseState;
    private:
        float _fps = 0;
        virtual int prepareWindow() = 0;
        virtual void prepareGL() = 0;

    public:
        GLuint VBO;
        GLuint VAO;
        virtual ~IWindow() = default;
        virtual void start(std::function<void()> drawFn, std::function<void()> setup) = 0;

        void calFPS()
        {
            static Uint32 lastTime = SDL_GetTicks();
            static int frames = 0;
            static float fps = 0.0f;

            Uint32 currentTime = SDL_GetTicks();
            frames++;

            if (currentTime - lastTime >= 1000)
            {
                fps = frames * 1000.0f / (currentTime - lastTime);
                this->_fps = fps;
                frames = 0;
                lastTime = currentTime;
            }
        };

        float getFPS()
        {
            return this->_fps;
        };

        int getWidth() 
        {
            return this->_width;
        }

        int getHeight()
        {
            return this->_height;
        }

        MouseState getMouseState(){
            return this->_mouseState;
        }
        
        void setPositionMouse(float x, float y){
            this->_mouseState.x = x;
            this->_mouseState.y = y;
        }

        void setLeftClick(bool click){
            this->_mouseState.leftDown = click;
        }

        void setRightClick(bool click){
            this->_mouseState.rightDown = click;
        }
    };
}