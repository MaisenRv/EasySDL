#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

namespace EasySDL
{
    inline std::string readShader(const std::string &path)
    {
        std::ifstream f(path);
        std::stringstream buf;
        buf << f.rdbuf();
        return buf.str();
    }

    auto compileShader = [](GLenum type, const std::string &path)
    {
        std::string shadersSrc = EasySDL::readShader(path);
        GLuint shader = glCreateShader(type);
        const char *cstr = shadersSrc.c_str();
        glShaderSource(shader, 1, &cstr, nullptr);
        glCompileShader(shader);

        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            char buf[512];
            glGetShaderInfoLog(shader, 512, nullptr, buf);
            std::cerr << "Shader compile error: " << buf << "\n";
        }
        return shader;
    };

}