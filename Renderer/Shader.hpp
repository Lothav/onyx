#ifndef ONYX_SHADER_HPP
#define ONYX_SHADER_HPP

#include <GLES3/gl3.h>

namespace Renderer {

    class Shader
    {
    private:
        GLuint shaderProgram;

    public:

        Shader() : shaderProgram(glCreateProgram()) {}

        void createGraphicShader(GLenum type, const GLchar* const source)
        {
            GLuint shader = glCreateShader(type);
            glShaderSource(shader, 1, &source, nullptr);
            glCompileShader(shader);

            glAttachShader(this->shaderProgram, shader);
        }

        void begin()
        {
            glLinkProgram(this->shaderProgram);
            glUseProgram(this->shaderProgram);

            // Specify the layout of the vertex data
            GLint posAttrib = glGetAttribLocation(this->shaderProgram, "position");
            auto uPosAttrib = static_cast<GLuint>(posAttrib);
            glEnableVertexAttribArray(uPosAttrib);
            glVertexAttribPointer(uPosAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
        }

    };

}

#endif //ONYX_SHADER_HPP
