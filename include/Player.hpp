#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Config.hpp"
#include "Maze.hpp"
#include <vector>
#include <cmath>

class Player
{
private:
	double x;
	double y;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double moveSpeed;
	double rotSpeed;
	double fov;

	void initPlayer();

public:
	Player();
	Player(double moveSpeed, double rotSpeed, double fov);
	~Player() = default;

	void moveForward(Maze &maze);
	void moveBackward(Maze &maze);
	void moveLeft(Maze &maze);
	void moveRight(Maze &maze);
	void rotateLeft();
	void rotateRight();

	double getX() const;
	double getY() const;
	double getDirX() const;
	double getDirY() const;
	double getPlaneX() const;
	double getPlaneY() const;
	double getMoveSpeed() const;
	double getRotSpeed() const;
	double getFov() const;
};

#endif
