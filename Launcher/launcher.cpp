#include "../Memory/Pool.hpp"

#include "../Renderer/Window.hpp"
#include "../Renderer/Shader.hpp"
#include "../Renderer/Vertex.hpp"
#include "../Renderer/Uniform.hpp"
#include "../Renderer/Player.hpp"
#include "../Renderer/Meshes.hpp"
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

    Memory::Provider::initPool();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialize sdl2: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        std::cerr << "Could not initialize IMG's flags" << std::endl;
        return EXIT_FAILURE;
    }

    auto windowObj = new Renderer::Window(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Window* window = windowObj->getWindow();

    auto shader = new Renderer::Shader();
    shader->createGraphicShader(GL_VERTEX_SHADER, "default.vert");
    shader->createGraphicShader(GL_FRAGMENT_SHADER, "default.frag");
    shader->beginProgram();

    auto texture = new Renderer::Uniform();
    texture->loadTexture("./data/launcher.png");
    texture->setUniform(shader->getShaderProgram(), UNIFORM_TYPE_TEXTURE);
    texture->setUniform(shader->getShaderProgram(), UNIFORM_TYPE_MAT4);

    auto vertex = new Renderer::Vertex(shader->getShaderProgram());
    auto meshes = new Renderer::Meshes();

    auto player1 = new Renderer::Player(0.5f, 0.0f, 1.0f, 0.5f);
    auto player2 = new Renderer::Player(-0.5f, 0.0f, 1.0f, 0.5f);

    loop =  [&] () -> bool
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) return false;
            if(e.type == SDL_KEYDOWN)
            {
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP:
                        player1->move(.0f, .10f);
                        std::cout << "Key Up pressed" << std::endl;
                        break;
                    case SDLK_DOWN:
                        player1->move(.0f, -.10f);
                        std::cout << "Key Down pressed" << std::endl;
                        break;
                    case SDLK_LEFT:
                        player1->move(-.10f, .0f);
                        std::cout << "Key Left pressed" << std::endl;
                        break;
                    case SDLK_RIGHT:
                        player1->move(.10f, .0f);
                        std::cout << "Key Right pressed" << std::endl;
                        break;

                    case SDLK_w:
                        texture->translateCamera(shader->getShaderProgram(), glm::vec3(0.0f, 0.1f, 0.0f));
                        break;
                    case SDLK_a:
                        texture->translateCamera(shader->getShaderProgram(), glm::vec3(-0.1f, 0.0f, 0.0f));
                        break;
                    case SDLK_s:
                        texture->translateCamera(shader->getShaderProgram(), glm::vec3(0.0f, -0.1f, 0.0f));
                        break;
                    case SDLK_d:
                        texture->translateCamera(shader->getShaderProgram(), glm::vec3(0.1f, 0.0f, 0.0f));
                        break;

                    default:
                        std::cout << "Non-arrow Key pressed" << std::endl;
                }
            }
        }
        meshes->clear();
        meshes->insert(player1->getVertices(), player1->getTotalVertices());
        meshes->insert(player2->getVertices(), player2->getTotalVertices());

        vertex->setBufferData(meshes->getByteSize(), meshes->get());
        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(meshes->getSize()) );

        SDL_GL_SwapWindow(window);

        return true;
    };

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, true);
#else
    while(main_loop());
#endif
    Memory::Provider::destroyPool();
    return EXIT_SUCCESS;
}