#include <iostream>
#include "Shader.hpp"

void Renderer::Shader::createGraphicShader(GLenum type, const std::string name)
{
    std::string shader_file_content = this->loadShaderFileContent(name);
    auto shader_script = std::move(shader_file_content.c_str());

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shader_script, nullptr);
    this->compileShader(shader);
    glAttachShader(this->shaderProgram, shader);

    this->shaders.push_back(shader);
}

GLuint Renderer::Shader::getShaderProgram()
{
    return this->shaderProgram;
}

void Renderer::Shader::beginProgram()
{
    glLinkProgram(this->shaderProgram);
    glUseProgram(this->shaderProgram);
}

void Renderer::Shader::compileShader(GLuint shader)
{
    // Try compile Shader
    glCompileShader(shader);

    // Check if success compiled
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg("Compile failure in shader:\n");

        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, nullptr, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;

        glDeleteShader(shader);
        std::cerr << msg << std::endl;
    }
}

std::string Renderer::Shader::loadShaderFileContent(std::string name)
{
    std::string filePath = "./data/shaders/" + name;

    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream.is_open()) {
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