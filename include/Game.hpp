#ifndef GAME_HPP
#define GAME_HPP

#include "Config.hpp"
#include "Player.hpp"
#include "Maze.hpp"
#include "Renderer.hpp"

class Game
{
private:
	Maze maze;
	Player player;
	Renderer renderer;
	bool running;

	void handleInput();

public:
	Game();
	~Game() = default;
	void run();
};

#endif
