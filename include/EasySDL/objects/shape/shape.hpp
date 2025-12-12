#pragma once

#include "../../interface/IDrawable.hpp"
#include "../../interface/IInitializable.hpp"
#include "../../interface/IWindow.hpp"
#include <vector>
#include <GL/glew.h>

namespace EasySDL{
    class Shape : public EasySDL::IDrawable, public EasySDL::IInitializable {
        protected:

            float _color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

            //  Vertex info
            std::vector<float> _vertexList;
            bool isCreatedVertex = false;

            // Shader info
            GLuint _vertexSrc = 0;
            GLuint _fragmentSrc = 0;


            int vertexCount;

            bool _restriction() override {
                return this->_vertexSrc && this->_fragmentSrc;
            }

        public:
            GLuint program;
            virtual ~Shape() = default;  
            // virtual void draw(EasySDL::IWindow *w);

            void setColor(const float (&color)[4] ){
                for (size_t i = 0; i < 4; i++) this->_color[i] = color[i];
            }
    };
}