#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <string>

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL,
};

const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Window* gWindow = NULL;

SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

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
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL) SDL_Log("Image loading is failed %s! SDL_ERROR: %s\n", path.c_str(), SDL_GetError());

	return loadedSurface;
}

bool loadMedia()
{
	bool success = true;

	//default
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("test_media.bmp");  //PATH/TO/BMP.bmp
	if (gKeyPressSurfaces == NULL)
	{
		SDL_Log("Image loading is failed %s. SDL_ERROR: %s\n", "test_media.bmp", SDL_GetError());
		success = false;
	}

	//up
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");  //PATH/TO/BMP.bmp
	if (gKeyPressSurfaces == NULL)
	{
		SDL_Log("Image loading is failed %s. SDL_ERROR: %s\n", "up.bmp", SDL_GetError());
		success = false;
	}

	//down
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");  //PATH/TO/BMP.bmp
	if (gKeyPressSurfaces == NULL)
	{
		SDL_Log("Image loading is failed %s. SDL_ERROR: %s\n", "down.bmp", SDL_GetError());
		success = false;
	}

	//left
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");  //PATH/TO/BMP.bmp
	if (gKeyPressSurfaces == NULL)
	{
		SDL_Log("Image loading is failed %s. SDL_ERROR: %s\n", "left.bmp", SDL_GetError());
		success = false;
	}

	//right
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");  //PATH/TO/BMP.bmp
	if (gKeyPressSurfaces == NULL)
	{
		SDL_Log("Image loading is failed %s. SDL_ERROR: %s\n", "right.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void close()
{
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++)
	{
		SDL_DestroySurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] == NULL;
	}

	//SDL_DestroySurface(gImageMedia);
	//gImageMedia = NULL;

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

			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_EVENT_QUIT) quit = true;

					else if (e.type == SDL_EVENT_KEY_DOWN)  //key press events
					{
						switch (e.key.key)
						{
						case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
							break;
						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
							break;
						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
							break;
						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
							break;
						default:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}

				SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}

		}
	}

	close();

	return 0;
}