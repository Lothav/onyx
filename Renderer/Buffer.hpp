#ifndef ONYX_BUFFER_HPP
#define ONYX_BUFFER_HPP

#include <GLES3/gl3.h>

namespace Renderer {

    class Buffer
    {
    private:
        GLuint buffer_object;
        GLenum target;
    public:

        Buffer(GLenum target) : buffer_object(), target(target) {
            glGenBuffers(1, &this->buffer_object);
        }

        void bindBuffer()
        {
            glBindBuffer(target, this->buffer_object);
        }

        void copyDataToBuffer(GLfloat* data, unsigned long size)
        {
            glBufferData(target, size, data, GL_STATIC_DRAW);
        }
    };
}
#endif //ONYX_BUFFER_HPP
