#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Window* gWindow = NULL;

SDL_Surface* gScreenSurface = NULL;

SDL_Surface* gImageMedia = NULL;  //image to load

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
		gWindow = SDL_CreateWindow("SDL Tutorial", WIDTH, HEIGHT, 0);

		if (gWindow == NULL)
		{
			SDL_Log("Window creation failed. SDL_ERROR: %s\n", SDL_GetError());
			success = false;
		}

		else gScreenSurface = SDL_GetWindowSurface(gWindow);
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	gImageMedia = SDL_LoadBMP("PATH/TO/BMP.bmp");  //PATH/TO/BMP.bmp
	if (gImageMedia == NULL)
	{
		SDL_Log("Image loading is failed %s. SDL_ERROR: %s\n", "PATH/TO/BMP.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void close()
{
	SDL_DestroySurface(gImageMedia);
	gImageMedia = NULL;

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
			}

			SDL_BlitSurface(gImageMedia, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface(gWindow);
		}
	}

	close();

	return 0;
}