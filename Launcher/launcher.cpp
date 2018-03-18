#include <iostream>

#include "../vendor/include/SDL2/SDL.h"
#include "../vendor/include/SDL2/SDL_image.h"
#include "../Renderer/Window.hpp"
#include "../Renderer/Shader.hpp"
#include "../Renderer/Buffer.hpp"
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

SDL_Texture* LoadImage(SDL_Renderer* renderer, std::string file)
{
	SDL_Surface *loadedImage = nullptr;
	SDL_Texture *texture = nullptr;
	loadedImage = IMG_Load(file.c_str());

	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
	} else {
		std::cout << SDL_GetError() << std::endl;
	}
		
	return texture;
}

const GLchar* vertexSource =
        "attribute vec4 position;                  \n"
        "void main()                               \n"
        "{                                         \n"
        "   gl_Position = vec4(position.xyz, 1.0); \n"
        "}                                         \n";
const GLchar* fragmentSource =
        "precision mediump float;                     \n"
        "void main()                                  \n"
        "{                                            \n"
        "  gl_FragColor = vec4 (1.0, 1.0, 1.0, 1.0 ); \n"
        "}                                            \n";

std::function<void()> loop;
void main_loop() { loop(); }

int main(int argc, char* args[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}

	auto windowObj = new Renderer::Window(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Window* window = windowObj->getWindow();


    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLfloat vertices[] = {0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f};
    auto vbo = new Renderer::Buffer(GL_ARRAY_BUFFER);
    vbo->bindBuffer();
    vbo->copyDataToBuffer(vertices, sizeof(vertices));

    auto shader = new Renderer::Shader();
    shader->createGraphicShader(GL_VERTEX_SHADER, vertexSource);
    shader->createGraphicShader(GL_FRAGMENT_SHADER, fragmentSource);
    shader->begin();

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

        // Draw a triangle from the 3 vertices
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    };

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, true);
#else
    while(true) main_loop();
#endif
    
	return EXIT_SUCCESS;
}