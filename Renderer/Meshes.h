//
// Created by luiz0tavio on 3/20/18.
//

#ifndef ONYX_DRAW_H
#define ONYX_DRAW_H

#include <vector>
#include <GLES3/gl3.h>

namespace Renderer
{
    class Meshes
    {
    private:

        std::vector<GLfloat> meshes;

    public:

        Meshes(): meshes({}) {}

        void insert(GLfloat* mesh, unsigned int meshes_size)
        {
            for(unsigned int i = 0; i < meshes_size; i++) this->meshes.push_back(mesh[i]);
        }

        void clear()
        {
            this->meshes.clear();
        }

        GLfloat * get()
        {
            return this->meshes.data();
        }

        unsigned long getSize()
        {
            return this->meshes.size() * sizeof(GLfloat);
        }
    };

}

#endif //ONYX_DRAW_H