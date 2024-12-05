#ifndef MAZE_HPP
#define MAZE_HPP

#include "Config.hpp"
#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

const std::vector<std::pair<int, int>> DIRECTIONS = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};

class Maze
{
private:
	int width;
	int height;
	std::vector<int> maze;

	bool isValidMove(int x, int y) const;
	int index(int x, int y) const;
	void generate();
	std::vector<std::tuple<int, int, int, int>> getValidFrontiers(int x, int y) const;

public:
	Maze();
	Maze(int width, int height);
	~Maze() = default;

	int getWidth() const;
	int getHeight() const;
	const std::vector<int> &getMaze() const;
	int at(int x, int y) const;

	friend std::ostream &operator<<(std::ostream &os, const Maze &maze);
};

#endif
