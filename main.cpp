#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include <string>

const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Window* gWindow = NULL;

SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gPNGSurface = NULL;

bool init()
{
	bool success = true;

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL initialization failed. SDL_ERROR: %s\n", SDL_GetError());
		success = false;
	}

	else
	{
		gWindow = SDL_CreateWindow("SDL Window", WIDTH, HEIGHT, 0);

		if (gWindow == NULL)
		{
			SDL_Log("Window creation failed. SDL_ERROR: %s\n", SDL_GetError());
			success = false;
		}

		else gScreenSurface = SDL_GetWindowSurface(gWindow);
	}

	return success;
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) SDL_Log("Image loading is failed %s! SDL_ERROR: %s\n", path.c_str(), SDL_GetError());

	else
	{
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format);
		if (optimizedSurface == NULL) SDL_Log("Image optimize is failed %s! SDL_ERROR: %s\n", path.c_str(), SDL_GetError());

		SDL_DestroySurface(loadedSurface);
	}

	return optimizedSurface;
}

bool loadMedia()
{
	bool success = true;

	gPNGSurface = loadSurface("test_png.png");
	if (gPNGSurface == NULL)
	{
		SDL_Log("PNG loading is failed.\n");
		success = false;
	}

	return success;
}

void close()
{
	SDL_DestroySurface(gPNGSurface);
	gPNGSurface = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!init())
	{
		SDL_Log("Initialization failed.\n");
	}
	else
	{
		if (!loadMedia())
		{
			SDL_Log("Media load is failed.\n");
		}
		else
		{
			bool quit = false;  //main loop flag
			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_EVENT_QUIT) quit = true;
				}

				SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}

		}
	}

	close();

	return 0;
}