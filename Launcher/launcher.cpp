#include <iostream>

#include "../vendor/include/SDL2/SDL.h"
#include "../Renderer/Window.hpp"
#include "../Renderer/Shader.hpp"
#include "../Renderer/Vertex.hpp"
#include "../Renderer/Uniform.hpp"
#include <functional>

/* This binary should check for updates and update the data files, the client and itself for non-console platforms (If internet connection)
 * Update server should be just an SFTP or something, can have the key inside the source code.
 * 1. Check for updates
 * 2. Check datafiles integrity against downloaded md5 references
 * References
 *   SelfUpdate (Windows): https://stackoverflow.com/questions/7483230/how-can-i-run-an-app-automatic-after-restart
 *	            (Linux  ): https://google.com
 */

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

std::function<void()> loop;
void main_loop() { loop(); }

int main(int argc, char* args[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}

	auto windowObj = new Renderer::Window(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Window* window = windowObj->getWindow();

    auto shader = new Renderer::Shader();
    shader->createGraphicShader(GL_VERTEX_SHADER, "default.vert");
    shader->createGraphicShader(GL_FRAGMENT_SHADER, "default.frag");
    shader->begin();

    auto texture = new Renderer::Uniform();
    texture->loadTexture("../bin/data/launcher.png");
    texture->setUniform(shader->getShaderProgram());

    GLfloat vertices[] = {
         0.0f, 0.8f, 0.0f,  0.5f, 1.0f,
        -0.8f,-0.8f, 0.0f,  0.0f, 0.0f,
         0.8f,-0.8f, 0.0f,  1.0f, 0.0f,
    };
    auto triangle = new Renderer::Vertex(sizeof(vertices), vertices, shader->getShaderProgram());

    loop =  [&]
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) std::terminate();
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->useProgram();
        texture->setUniform(shader->getShaderProgram());
        triangle->bindVAO();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        triangle->bindVAO(true);
        texture->setUniform(shader->getShaderProgram(), true);
        shader->useProgram(false);

        SDL_GL_SwapWindow(window);
    };

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, true);
#else
    while(true) main_loop();
#endif
	return EXIT_SUCCESS;
}