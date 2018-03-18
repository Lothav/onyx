#ifndef ONYX_SHADER_HPP
#define ONYX_SHADER_HPP

#include <GLES3/gl3.h>
#include <fstream>

namespace Renderer {

    class Shader
    {
    private:
        GLuint shaderProgram;

    public:

        Shader() : shaderProgram(glCreateProgram()) {}

        void createGraphicShader(GLenum type, const std::string name)
        {
            std::string filePath = "../Renderer/shaders/" + name;

            std::string content;
            std::ifstream fileStream(filePath, std::ios::in);
            if(!fileStream.is_open()) {
                std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
                return;
            }
            std::string line = "";
            while(!fileStream.eof()) {
                std::getline(fileStream, line);
                content.append(line + "\n");
            }
            fileStream.close();

            auto shader_script = std::move(content.c_str());

            GLuint shader = glCreateShader(type);
            glShaderSource(shader, 1, &shader_script, nullptr);
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
