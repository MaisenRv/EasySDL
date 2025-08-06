#pragma once

#include "../../interface/IDrawable.hpp"
#include <vector>
#include <GL/glew.h>

namespace EasySDL{
    class Shape : public EasySDL::IDrawable{
        protected:

            float _color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

            //  Vertex info
            std::vector<float> _vertexList;

            // Shader info
            GLuint _vertexSrc;
            GLuint _fragmentSrc;


            int vertexCount;
        public:
            GLuint program;
            
            void setColor(const float (&color)[4] ){
                for (size_t i = 0; i < 4; i++) this->_color[i] = color[i];
            }
    };
}