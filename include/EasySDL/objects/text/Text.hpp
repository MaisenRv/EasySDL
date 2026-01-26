#pragma once
#include <SDL2/SDL.h>
#include "../../interface/IDrawable.hpp"
#include <GL/glew.h>
#include <vector>
#include "../../utils/pathList.hpp"
#include "../../../Math/types/Vec2.hpp"
#include "../../utils/shadersUtils.hpp"
#include "../../interface/IWindow.hpp"

#ifdef __EMSCRIPTEN__
#include <SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

namespace EasySDL
{
    class Text : public EasySDL::IDrawable
    {
    private:
        TTF_Font *font;
        SDL_Color color;
        int wText, hText;
        GLuint textTexture;
        GLuint VAO, VBO, EBO;
        GLuint vertShader, fragShader;
        GLuint program;

        
        std::vector<float> vertices;
        unsigned int indices[6] = {0, 1, 2, 2, 3, 0};
        float _scale = 1;
        Vec2 _pos = {0,0};
        std::string _message = "";

        // state
        bool isUpdatableTexture = false;
        bool geometryDirty = false;


        void generateTexture(const std::string &str)
        {
            // Render text to surface
            SDL_Surface *surf = TTF_RenderText_Blended(font, str.c_str(), color);
            if (!surf)
            {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Blended error: %s", TTF_GetError());
                return;
            }
            SDL_Surface *formatted = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_ABGR8888, 0);
            SDL_FreeSurface(surf);
            surf = formatted;

            wText = surf->w;
            hText = surf->h;

            // 3) Asegúrate de que OpenGL respete el alineamiento de 1 byte
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            // 4) Subes la textura a OpenGL
            glBindTexture(GL_TEXTURE_2D, textTexture);
            // Ahora que surf está en ABGR8888, usas GL_RGBA
            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         GL_RGBA,
                         wText,
                         hText,
                         0,
                         GL_RGBA,
                         GL_UNSIGNED_BYTE,
                         surf->pixels);
            glGenerateMipmap(GL_TEXTURE_2D);

            SDL_FreeSurface(surf);
        }

        void updateVertices()
        {
            float w = float(wText);
            float h = float(hText);
            // Centered at origin
            vertices = {
                -w, h, 0.0f, 0.0f,
                w, h, 1.0f, 0.0f,
                w, -h, 1.0f, 1.0f,
                -w, -h, 0.0f, 1.0f};
        }

    public:
        Text(const std::string &fontPath, int fontSize)
        {
            font = TTF_OpenFont(fontPath.c_str(), fontSize);
            color = {255, 255, 255, 255};
            glGenTextures(1, &textTexture);
            glBindTexture(GL_TEXTURE_2D, textTexture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Prepare shaders
            vertShader = EasySDL::compileShader(GL_VERTEX_SHADER, BASIC_VERTEX_TEXT_SHADER_PATH);
            fragShader = EasySDL::compileShader(GL_FRAGMENT_SHADER, BASIC_FRAGMENT_TEXT_SHADER_PATH);
            program = glCreateProgram();
            glAttachShader(program, vertShader);
            glAttachShader(program, fragShader);
            glLinkProgram(program);

            // Create buffers
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // reserve space
            glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            // Attributes
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
            glBindVertexArray(0);
        }

        ~Text()
        {
            glDeleteTextures(1, &textTexture);
            glDeleteProgram(program);
            glDeleteShader(vertShader);
            glDeleteShader(fragShader);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            glDeleteVertexArrays(1, &VAO);
            TTF_CloseFont(font);
        }

        void draw(EasySDL::IWindow *w) override
        {
            generateTexture(this->_message);
            updateVertices();
            // Update buffer data
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());

            // Use shader
            glUseProgram(program);
            glUniform2f(glGetUniformLocation(program, "u_WindowSize"), float(w->getWidth()), float(w->getHeight()));
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textTexture);
            glUniform1i(glGetUniformLocation(program, "text"), 0);

            // Position translation
            // In shader, position is in pixels relative to center; we need to shift by x,y
            GLint locOff = glGetUniformLocation(program, "u_Offset");
            if (locOff >= 0)
                glUniform2f(locOff, this->_pos.x, this->_pos.y);
            GLint locScale = glGetUniformLocation(program, "u_Scale");
            glUniform2f(locScale, this->_scale, this->_scale);
            // Draw
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        void shiftX(float delta)
        {
            this->_pos.x -= delta;
        }
        //-------------------- Getters and setters
        void setScale(float scale){
            this->_scale = scale;
        }

        void setPos(Vec2 newPos){
            this->_pos.x = newPos.x;
            this->_pos.y = newPos.y;
        }

        void setMessage(const std::string &message){
            this->_message = message;
        }
        
        int getwText(){
            return this->wText;
        }

        int gethText(){
            return this->hText;
        }

        void setTextColor(const SDL_Color color){
            this->color = color;
        }

        void setUpdatebleTexture(bool isUpdatableTexture){
            this->isUpdatableTexture = isUpdatableTexture;
        }
    };
}

