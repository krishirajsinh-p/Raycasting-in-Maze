#include "../include/Player.hpp"

Player::Player() : moveSpeed(MOVE_SPEED), rotSpeed(ROTATE_SPEED), fov(FOV)
{
	initPlayer();
}

Player::Player(double move_speed, double rotate_speed, double Fov) : moveSpeed(move_speed), rotSpeed(rotate_speed), fov(Fov)
{
	initPlayer();
}

void Player::initPlayer()
{
	x = 1.5;
	y = 1.5;
	dirX = -1.0;
	dirY = 0.0;
	planeX = 0.0;
	planeY = fov;
}

void Player::moveForward(Maze &maze)
{
	if (maze.at(x + dirX * moveSpeed, y) == 0)
	{
		x += dirX * moveSpeed;
	}
	if (maze.at(x, y + dirY * moveSpeed) == 0)
	{
		y += dirY * moveSpeed;
	}
}

void Player::moveBackward(Maze &maze)
{
	if (maze.at(x - dirX * moveSpeed, y) == 0)
	{
		x -= dirX * moveSpeed;
	}
	if (maze.at(x, y - dirY * moveSpeed) == 0)
	{
		y -= dirY * moveSpeed;
	}
}

void Player::moveLeft(Maze &maze)
{
	if (maze.at(x - dirY * moveSpeed, y) == 0)
	{
		x -= dirY * moveSpeed;
	}
	if (maze.at(x, y + dirX * moveSpeed) == 0)
	{
		y += dirX * moveSpeed;
	}
}

void Player::moveRight(Maze &maze)
{
	if (maze.at(x + dirY * moveSpeed, y) == 0)
	{
		x += dirY * moveSpeed;
	}
	if (maze.at(x, y - dirX * moveSpeed) == 0)
	{
		y -= dirX * moveSpeed;
	}
}

void Player::rotateLeft()
{
	double oldDirX = dirX;
	dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);

	double oldPlaneX = planeX;
	planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
}

void Player::rotateRight()
{
	double oldDirX = dirX;
	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);

	double oldPlaneX = planeX;
	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
}

double Player::getX() const
{
	return x;
}

double Player::getY() const
{
	return y;
}

double Player::getDirX() const
{
	return dirX;
}

double Player::getDirY() const
{
	return dirY;
}

double Player::getPlaneX() const
{
	return planeX;
}

double Player::getPlaneY() const
{
	return planeY;
}

double Player::getMoveSpeed() const
{
	return moveSpeed;
}

double Player::getRotSpeed() const
{
	return rotSpeed;
}

double Player::getFov() const
{
	return fov;
}
