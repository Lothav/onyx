#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "..\vendor\include\SDL2\SDL.h"
#include "..\vendor\include\SDL2\SDL_image.h"
#else
#include "../vendor/include/SDL2/SDL.h"
#include "../vendor/include/SDL2/SDL_image.h"
#endif

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

int main(int argc, char* args[]) {
	SDL_Window* window = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow(
		"Onyx Launcher",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS
	);
	if (window == nullptr) {
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_Texture* launcherBackground = LoadImage(renderer, "data/launcher.png");
	if (launcherBackground == nullptr) {
		fprintf(stderr, "%s", SDL_GetError());
		//return 1;
	}

	bool quit = false;
	SDL_Event event = nullptr;
	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		SDL_RenderCopy(renderer, launcherBackground, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(launcherBackground);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}