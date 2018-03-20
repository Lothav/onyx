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
            std::string shader_file_content = this->loadFileContent(name);
            auto shader_script = std::move(shader_file_content.c_str());

            GLuint shader = glCreateShader(type);
            glShaderSource(shader, 1, &shader_script, nullptr);
            this->compileShader(shader);
            glAttachShader(this->shaderProgram, shader);
        }

        GLuint getShaderProgram()
        {
            return this->shaderProgram;
        }

        void beginProgram()
        {
            glLinkProgram(this->shaderProgram);
            glUseProgram(this->shaderProgram);
        }

    private:

        void compileShader(GLuint shader) {
            // Try compile Shader
            glCompileShader(shader);

            // Check if success compiled
            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (status == GL_FALSE) {
                std::string msg("Compile failure in shader:\n");

                GLint infoLogLength;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
                char* strInfoLog = new char[infoLogLength + 1];
                glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
                msg += strInfoLog;
                delete[] strInfoLog;

                glDeleteShader(shader);
                std::cerr << msg << std::endl;
            }
        }

        std::string loadFileContent(std::string name){
            std::string filePath = "./Renderer/shaders/" + name;

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
