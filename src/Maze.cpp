#include "../include/Maze.hpp"

Maze::Maze() : width(MAZE_WIDTH), height(MAZE_HEIGHT) 
{
	maze.assign(width * height, 1);
	generate();
}

Maze::Maze(int width, int height) : width(width), height(height)
{
	maze.assign(width * height, 1);
	generate();
}

bool Maze::isValidMove(int x, int y) const
{
	return x > 0 && x < height && y > 0 && y < width && maze[index(x, y)] == 1;
}

int Maze::index(int x, int y) const
{
	return x * width + y;
}

std::vector<std::tuple<int, int, int, int>> Maze::getValidFrontiers(int x, int y) const
{
	std::vector<std::tuple<int, int, int, int>> frontiers;
	for (const auto &[dx, dy] : DIRECTIONS)
	{
		int nx = x + dx;
		int ny = y + dy;
		if (isValidMove(nx, ny))
		{
			frontiers.emplace_back(nx, ny, x, y);
		}
	}
	return frontiers;
}

void Maze::generate()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int start_x = (gen() % (height / 2)) * 2 + 1;
	int start_y = (gen() % (width / 2)) * 2 + 1;
	maze[index(start_x, start_y)] = 0;

	std::vector<std::tuple<int, int, int, int>> frontiers = getValidFrontiers(start_x, start_y);
	while (!frontiers.empty())
	{
		std::shuffle(frontiers.begin(), frontiers.end(), gen);
		auto [x, y, px, py] = frontiers.back();
		frontiers.pop_back();

		if (isValidMove(x, y))
		{
			maze[index(x, y)] = 0;
			maze[index((x + px) / 2, (y + py) / 2)] = 0;

			auto new_frontiers = getValidFrontiers(x, y);
			frontiers.insert(frontiers.end(), new_frontiers.begin(), new_frontiers.end());
		}
	}
}

int Maze::getWidth() const
{
	return width;
}

int Maze::getHeight() const
{
	return height;
}

const std::vector<int> &Maze::getMaze() const
{
	return maze;
}

int Maze::at(int x, int y) const
{
	if (x < 0 || x >= height || y < 0 || y >= width)
	{
		return 0;
	}
	return maze[index(x, y)];
}

std::ostream &operator<<(std::ostream &os, const Maze &maze)
{
	for (int i = 0; i < maze.getHeight(); ++i)
	{
		for (int j = 0; j < maze.getWidth(); ++j)
		{
			os << (maze.at(i, j) ? "██" : "  ");
		}
		os << std::endl;
	}
	return os;
}
