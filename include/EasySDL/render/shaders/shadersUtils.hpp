#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

namespace EasySDL::render::shaders{
    [[nodiscard]] inline std::string readShader(const std::string &path) {

        std::ifstream file(path, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "ERROR: Cannot open shader file: " << path << "\n";
            return "";
        }

        std::string source(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());

        if (source.size() >= 3 &&
            (unsigned char)source[0] == 0xEF &&
            (unsigned char)source[1] == 0xBB &&
            (unsigned char)source[2] == 0xBF)
        {
            source.erase(0, 3);
        }

        while (!source.empty() &&
               (source[0] == '\n' || source[0] == '\r' || source[0] == ' '))
        {
            source.erase(0, 1);
        }

        return source;
    }

    auto compileShader = [](GLenum type, const std::string &path) {
        std::string shadersSrc = readShader(path);
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