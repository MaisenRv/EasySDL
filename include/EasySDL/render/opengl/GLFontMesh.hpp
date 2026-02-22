#pragma once

#include "./../geometry/Mesh2D.hpp"
#include <GL/glew.h>

namespace EasySDL
{
    template <typename T = float>
    struct GLFontMesh{
        GLuint VBO = 0;
        GLuint VAO = 0;
        GLuint EBO = 0;
        unsigned int indices[6] = {0, 1, 2, 2, 3, 0};

        void create(){
            glGenVertexArrays(1,&VAO);
            glGenBuffers(1,&VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
            glBindVertexArray(0);
        }

        void upload(const Mesh2D<T> &mesh){
            if(!mesh.geometryDirty) return;
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(
                GL_ARRAY_BUFFER,
                mesh.vertices.size() * sizeof(T),
                mesh.vertices.data(),
                (mesh.usage == MeshUsage::DYNAMIC) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW
            );
            glBindVertexArray(0);
        }

        void del(){
            glDeleteBuffers(1,&VBO);
            glDeleteVertexArrays(1,&VAO);
            glDeleteBuffers(1,&EBO);
        }

    };
}