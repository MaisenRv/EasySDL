#pragma once
#include "../../../Window.hpp"
#include "../../../utils/shadersUtils.hpp"
#include "../../../utils/pathList.hpp"
#include "../../../../Math/types/Vec2.hpp"
#include "../shape.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <functional>

namespace EasySDL
{
    class LineStrip : public EasySDL::Shape
    {
    protected:
        // Line info
        GLfloat _lineWidth;

        // Shift shader
        GLuint _shiftVBO;
        GLuint _shiftProgram;


        void _onSetup() override
        {
            this->_vertexSrc = EasySDL::compileShader(GL_VERTEX_SHADER, EasySDL::BASIC_VERTEX_SHADER_PATH);
            this->_fragmentSrc = EasySDL::compileShader(GL_FRAGMENT_SHADER, EasySDL::BASIC_FRAGMENT_SHADER_PATH);
            this->program = glCreateProgram();
            glAttachShader(program, this->_vertexSrc);
            glAttachShader(program, this->_fragmentSrc);
            glLinkProgram(program);

            // SHIFT PROGRAM

            glGenBuffers(1,&this->_shiftVBO);
            glBindBuffer(GL_ARRAY_BUFFER, this->_shiftVBO);
            glBufferData(
                GL_ARRAY_BUFFER,
                this->_vertexList.size()* sizeof(float),
                nullptr,
                GL_DYNAMIC_COPY
            );

            GLuint shiftVertex = EasySDL::compileShader(GL_VERTEX_SHADER,EasySDL::SHIFT_VERTEX_SHADER_PATH);
            this->_shiftProgram = glCreateProgram();
            glAttachShader(this->_shiftProgram,shiftVertex);

            const GLchar* varyings[] = { "vPos" };
            glTransformFeedbackVaryings(this->_shiftProgram, 1,
                            varyings, GL_INTERLEAVED_ATTRIBS
                        );
            glLinkProgram(this->_shiftProgram);
            glDeleteShader(shiftVertex);
        }

    public:
        LineStrip(GLfloat lineWidth) : _lineWidth(lineWidth) {}

        void draw(EasySDL::Window *w) override
        {
            this->vertexCount = (int)(this->_vertexList.size() / 2);
            if (this->vertexCount == 0) return;

            glBindBuffer(GL_ARRAY_BUFFER, w->VBO);
            glBufferData(
                GL_ARRAY_BUFFER,
                this->_vertexList.size() * sizeof(float),
                this->_vertexList.data(),
                GL_DYNAMIC_DRAW);

            GLint loc = glGetUniformLocation(this->program, "u_WindowSize");
            GLint colorLoc = glGetUniformLocation(this->program, "u_Color"); // Color
            glUseProgram(this->program);
            glUniform2f(loc, (float)w->getWidth(), (float)w->getHeight());
            glUniform4f(colorLoc, this->_color[0], this->_color[1], this->_color[2], this->_color[3]);
            glBindVertexArray(w->VAO);
            glLineWidth(this->_lineWidth);
            glDrawArrays(GL_LINE_STRIP, 0, this->vertexCount);
        }


        void addPoint(Vec2 point)
        {
            this->_vertexList.push_back(point.x);
            this->_vertexList.push_back(point.y);
        }

        ~LineStrip()
        {
            glDeleteShader(this->_vertexSrc);
            glDeleteShader(this->_fragmentSrc);
        }

        void removeFirstPoint()
        {
            if (!this->_vertexList.empty())
            {
                this->_vertexList.erase(this->_vertexList.begin());
                this->_vertexList.erase(this->_vertexList.begin());
            }
        }

        void shiftX(float delta,EasySDL::Window *w){
            // // 1) Recalcula cuántos vértices tenemos
            // vertexCount = static_cast<int>(_vertexList.size() / 2);
            // if (vertexCount == 0) return;

            // // 2) Acumula el shift y pásalo al shader
            // //    (si quieres acumulativo, sustituye delta por _shiftXAmount += delta)
            // glUseProgram(_shiftProgram);
            // GLint loc = glGetUniformLocation(_shiftProgram, "u_ShiftX");
            // glUniform1f(loc, delta);

            // // 3) Asegura espacio en el buffer de feedback
            // glBindBuffer(GL_ARRAY_BUFFER, _shiftVBO);
            // glBufferData(GL_ARRAY_BUFFER,
            //             _vertexList.size() * sizeof(float),
            //             nullptr,
            //             GL_DYNAMIC_COPY);

            // // 4) Sube los datos fuente al VBO de la ventana
            // glBindBuffer(GL_ARRAY_BUFFER, w->VBO);
            // glBufferData(GL_ARRAY_BUFFER,
            //             _vertexList.size() * sizeof(float),
            //             _vertexList.data(),
            //             GL_DYNAMIC_DRAW);

            // // 5) Configura VAO para leer de w->VBO
            // glBindVertexArray(w->VAO);
            // glEnableVertexAttribArray(0);
            // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

            // // 6) Enlaza buffer de salida para Feedback
            // glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, _shiftVBO);

            // // 7) Ejecuta Transform Feedback (sin rasterizar)
            // glEnable(GL_RASTERIZER_DISCARD);
            // glBeginTransformFeedback(GL_POINTS);
            // glDrawArrays(GL_POINTS, 0, vertexCount);
            // glEndTransformFeedback();
            // glDisable(GL_RASTERIZER_DISCARD);

            // // 8) Leer de vuelta al vector CPU
            // _vertexList.resize(vertexCount * 2);
            // glBindBuffer(GL_ARRAY_BUFFER, _shiftVBO);
            // glGetBufferSubData(GL_ARRAY_BUFFER,
            //                 0,
            //                 _vertexList.size() * sizeof(float),
            //                 _vertexList.data());

            // // 9) Restablece el VAO de la ventana (por si acaso)
            // glBindVertexArray(w->VAO);

            for (size_t i = 0; i < this->_vertexList.size(); i += 2){
                this->_vertexList[i] -= delta;
            }
        }

        void updateAllPoint(std::function<Vec2(float x,float y)> updateFunction){
            std::vector<float> copyPoints(this->_vertexList);
            this->_vertexList.clear();
            for (size_t i = 0; i < copyPoints.size(); i += 2)
            {
                Vec2 newPoints = updateFunction(copyPoints[i], copyPoints[i+1]);
                this->_vertexList.push_back(newPoints.x);
                this->_vertexList.push_back(newPoints.y);
            }
        }

        //-------------------- Getters and setters

        int getVertexSize()
        {
            return this->_vertexList.size() / 2;
        }

        std::vector<float> &getVertexList()
        {
            return this->_vertexList;
        }
    };

}