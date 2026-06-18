#pragma once

#include <GL/glew.h>

#include <EasySDL/render/geometry/Mesh2D.hpp>

namespace EasySDL::render::gl{
    template <typename T>
    struct GLMesh2D {
        GLuint VBO = 0;
        GLuint VAO = 0;

        GLMesh2D() = default;

        GLMesh2D(const GLMesh2D&) = delete;
        GLMesh2D& operator=( const GLMesh2D&) = delete;

        GLMesh2D( GLMesh2D&& meshgl) noexcept: VBO(meshgl.VBO), VAO(meshgl.VAO){
            meshgl.VAO = 0;
            meshgl.VBO = 0;
        };
        
        GLMesh2D& operator=( GLMesh2D&& meshgl) noexcept{
            if (this != &meshgl) {
                release(); 
                VBO = meshgl.VBO;
                VAO = meshgl.VAO;
                meshgl.VBO = 0;
                meshgl.VAO = 0;
            }
            return *this;
        };
        ~GLMesh2D(){ release(); }

        void release() noexcept {
            if (VBO != 0) {
                glDeleteBuffers(1, &VBO);
                VBO = 0;
            }
            if (VAO != 0) {
                glDeleteVertexArrays(1, &VAO);
                VAO = 0;
            }
        }

        void create(){
            glGenVertexArrays(1,&VAO);
            glGenBuffers(1,&VBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

            glBindVertexArray(0);
        }

        void upload(const render::Mesh2D<T> &mesh){
            if(!mesh.geometryDirty) return;
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(
                GL_ARRAY_BUFFER,
                mesh.vertices.size() * sizeof(mesh.vertices[0]),
                mesh.vertices.data(),
                (mesh.usage == types::MeshUsage::DYNAMIC) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW
            );
            glBindVertexArray(0);
        }
    };
    
}