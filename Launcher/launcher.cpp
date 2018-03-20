#include <iostream>

#include "../Renderer/Window.hpp"
#include "../Renderer/Shader.hpp"
#include "../Renderer/Vertex.hpp"
#include "../Renderer/Uniform.hpp"
#include "../Renderer/Player.h"
#include "../Renderer/Meshes.h"
#include <functional>
#include <memory>

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

std::function<bool()> loop;
bool main_loop() { return loop(); }

int main(int argc, char* args[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
		std::cerr << "Could not initialize sdl2: " << SDL_GetError() << std::endl;
		return 1;
	}

	auto windowObj = std::make_unique<Renderer::Window>(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Window* window = windowObj->getWindow();

    auto shader = std::make_unique<Renderer::Shader>();
    shader->createGraphicShader(GL_VERTEX_SHADER, "default.vert");
    shader->createGraphicShader(GL_FRAGMENT_SHADER, "default.frag");
    shader->beginProgram();

    auto texture = std::make_unique<Renderer::Uniform>();
    texture->loadTexture("./data/launcher.png");
    texture->setUniform(shader->getShaderProgram());

    auto vertex = std::make_unique<Renderer::Vertex>(shader->getShaderProgram());
    auto meshes = std::make_unique<Renderer::Meshes>();

    auto player1 = std::make_unique<Renderer::Player>(0.5f, 0.0f, 1.0f, 0.5f);
    auto player2 = std::make_unique<Renderer::Player>(-0.5f, 0.0f, 1.0f, 0.5f);

    loop =  [&] () -> bool
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) return false;
            if(e.type == SDL_KEYDOWN) return false;
        }
        meshes->clear();
        meshes->insert(player1->getVertices(), player1->getVerticesSize());
        meshes->insert(player2->getVertices(), player2->getVerticesSize());

        vertex->setBufferData(meshes->getSize(), meshes->get());
        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(meshes->getSize()));

        SDL_GL_SwapWindow(window);

        return true;
    };

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, true);
#else
    while(main_loop());
#endif
	return EXIT_SUCCESS;
}