#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Config.hpp"
#include "Player.hpp"
#include "Maze.hpp"

class Renderer
{
private:
	int screenWidth;
	int screenHeight;
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool anyError;

	void cleanUp(std::string errorMessage);
	void initSDLComponents();

public:
	Renderer();
	Renderer(int screenWidth, int screenHeight);
	~Renderer();

	void render(const Player &player, const Maze &maze);

	int getScreenWidth() const;
	int getScreenHeight() const;
	bool hasAnyError() const;
};

#endif
