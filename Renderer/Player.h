//
// Created by luiz0tavio on 3/20/18.
//

#ifndef ONYX_PLAYER_H
#define ONYX_PLAYER_H

#include <GLES3/gl3.h>
#include <algorithm>
#include <array>

#define SIZE_VERTICES 30 // 6 points, 5 coords each (x, y, z, u, v)

namespace Renderer
{
    class Player
    {
    private:

        float x;
        float y;
        float height;
        float width;

        std::array<GLfloat,SIZE_VERTICES>vertices;

    public:

        Player(float x, float y, float height, float width) : x(x), y(y), height(height), width(width)
        {
            vertices = {
                    // Triangles                                                c ___
                    x + (width/2), y + (height/2), 0.0f, 1.0f, 0.0f, // a        |  /a
                    x - (width/2), y - (height/2), 0.0f, 0.0f, 1.0f, // b        | /
                    x - (width/2), y + (height/2), 0.0f, 0.0f, 0.0f, // c       b|/

                    x + (width/2), y + (height/2), 0.0f, 1.0f, 0.0f, // d          /|d
                    x - (width/2), y - (height/2), 0.0f, 0.0f, 1.0f, // e         / |
                    x + (width/2), y - (height/2), 0.0f, 1.0f, 1.0f, // f       e/__|f
            };
        }

        GLfloat* getVertices()
        {
            return this->vertices.data();
        }

        unsigned int getVerticesSize()
        {
            return sizeof(GLfloat) * SIZE_VERTICES;
        }

    };
}

#endif //ONYX_PLAYER_H
