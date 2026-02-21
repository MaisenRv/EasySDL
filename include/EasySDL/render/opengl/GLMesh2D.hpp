#pragma once
#include "./../geometry/Mesh2D.hpp"
#include <GL/glew.h>

namespace EasySDL
{
    template <typename T = float>
    struct GLMesh2D
    {
        GLuint VBO = 0;
        GLuint VAO = 0;

        void create(){
            glGenVertexArrays(1,&VAO);
            glGenBuffers(1,&VBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

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
        }
    };
    
}