#ifndef ONYX_UNIFORM_HPP
#define ONYX_UNIFORM_HPP

#include <GLES3/gl3.h>
#include "../vendor/include/SDL2/SDL_surface.h"
#include "../vendor/include/SDL2/SDL_image.h"
#include <string>
namespace Renderer
{
    class Uniform
    {
    private:
        GLuint texture_id;

    public:
        Uniform() {}

        void loadTexture(std::string path)
        {
            SDL_Surface* surf = IMG_Load(path.c_str());

            glGenTextures(1, &this->texture_id);
            glBindTexture(GL_TEXTURE_2D, this->texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels);
            glGetError();

            /* Linear Filtering */
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }

        void setUniform(GLuint shader_program, bool clear=false)
        {
            if (clear) {
                glBindTexture(GL_TEXTURE_2D, 0);
                return;
            }
            GLint uniformAtt = glGetUniformLocation(shader_program, "tex");
            glActiveTexture(GL_TEXTURE0 + 0);
            glBindTexture(GL_TEXTURE_2D, this->texture_id);
            glUniform1i(uniformAtt, 0);
        }

    };

}
#endif //ONYX_UNIFORM_HPP
