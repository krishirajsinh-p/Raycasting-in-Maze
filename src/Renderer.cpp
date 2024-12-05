#include "../include/Renderer.hpp"

Renderer::Renderer() : screenWidth(SCREEN_WIDTH), screenHeight(SCREEN_HEIGHT), anyError(false)
{
	initSDLComponents();
}

Renderer::Renderer(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight), anyError(false)
{
	initSDLComponents();
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Renderer::cleanUp(std::string errorMessage)
{
	std::cerr << errorMessage << SDL_GetError() << std::endl;
	SDL_Quit();
	anyError = true;
}

void Renderer::initSDLComponents()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cleanUp("SDL_Init Error: ");
		return;
	}

	window = SDL_CreateWindow("Raycasting in Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		cleanUp("SDL_CreateWindow Error: ");
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		SDL_DestroyWindow(window);
		cleanUp("SDL_CreateRenderer Error: ");
		return;
	}
}

void Renderer::render(const Player &player, const Maze &maze)
{
	if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255))
	{
		cleanUp("SDL_SetRenderDrawColor Error: ");
		return;
	}

	if (SDL_RenderClear(renderer))
	{
		cleanUp("SDL_RenderClear Error: ");
		return;
	}

	for (int x = 0; x < screenWidth; x++)
	{
		double cameraX = 2 * x / double(screenWidth) - 1;
		double rayDirX = player.getDirX() + player.getPlaneX() * cameraX;
		double rayDirY = player.getDirY() + player.getPlaneY() * cameraX;

		int mapX = int(player.getX());
		int mapY = int(player.getY());

		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

		double perpWallDist;

		int stepX;
		int stepY;

		bool hit = false;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player.getX() - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player.getX()) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player.getY() - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player.getY()) * deltaDistY;
		}

		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			if (mapX < 0 || mapX >= maze.getWidth() || mapY < 0 || mapY >= maze.getHeight())
			{
				hit = true;
				continue;
			}

			if (maze.at(mapX, mapY) > 0)
			{
				hit = true;
			}
		}

		if (side == 0)
			perpWallDist = (mapX - player.getX() + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - player.getY() + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(screenHeight / perpWallDist);

		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255))
		{
			cleanUp("SDL_SetRenderDrawColor Error: ");
			return;
		}

		if (side == 1)
		{
			if (SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255))
			{
				cleanUp("SDL_SetRenderDrawColor Error: ");
				return;
			}
		}

		if (SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd))
		{
			cleanUp("SDL_RenderDrawLine Error: ");
			return;
		}
	}

	SDL_RenderPresent(renderer);
}

int Renderer::getScreenWidth() const
{
	return screenWidth;
}

int Renderer::getScreenHeight() const
{
	return screenHeight;
}

bool Renderer::hasAnyError() const
{
	return anyError;
}