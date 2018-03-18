#ifndef ONYX_SHADER_HPP
#define ONYX_SHADER_HPP

#include <GLES3/gl3.h>
#include <fstream>
#include <cassert>

namespace Renderer {

    class Shader
    {
    private:
        GLuint shaderProgram;

    public:

        Shader() : shaderProgram(glCreateProgram()) {}

        void createGraphicShader(GLenum type, const std::string name)
        {
            auto shader_script = std::move(this->loadFileContent(name).c_str());

            GLuint shader = glCreateShader(type);
            glShaderSource(shader, 1, &shader_script, nullptr);
            glCompileShader(shader);

            glAttachShader(this->shaderProgram, shader);
        }

        GLuint getShaderProgram() {
            return this->shaderProgram;
        }

        void begin()
        {
            glLinkProgram(this->shaderProgram);
        }

        void useProgram(bool clear=false) {
            if (clear && this->isProgramInUse()) {
                glUseProgram(0);
            } else {
                glUseProgram(this->shaderProgram);
            }
        }

        bool isProgramInUse() const {
            GLint currentProgram = 0;
            glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
            return (currentProgram == (GLint)shaderProgram);
        }

    private:

        std::string loadFileContent(std::string name){
            std::string filePath = "../Renderer/shaders/" + name;

            std::string content;
            std::ifstream fileStream(filePath, std::ios::in);
            if(!fileStream.is_open()) {
                std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
                return "";
            }
            std::string line = "";
            while(!fileStream.eof()) {
                std::getline(fileStream, line);
                content.append(line + "\n");
            }
            fileStream.close();

            return content;
        }

    };

}

#endif //ONYX_SHADER_HPP
