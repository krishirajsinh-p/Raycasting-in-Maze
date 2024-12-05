#include "../include/Game.hpp"

Game::Game() : maze(), player(), renderer(), running(true) {}

void Game::handleInput()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[FORWARD])
	{
		player.moveForward(maze);
	}
	if (state[BACKWARD])
	{
		player.moveBackward(maze);
	}
	if (state[LEFT])
	{
		player.moveLeft(maze);
	}
	if (state[RIGHT])
	{
		player.moveRight(maze);
	}
	if (state[ROTATE_LEFT])
	{
		player.rotateLeft();
	}
	if (state[ROTATE_RIGHT])
	{
		player.rotateRight();
	}
	if (state[EXIT])
	{
		running = false;
	}
}

void Game::run()
{
	SDL_Event event;
	while (running && !renderer.hasAnyError())
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}
		renderer.render(player, maze);
		handleInput();
	}
}
