#pragma once
#include "Sprite.h"
#include "Bullet.h"


class Invader: public Sprite
{
private:
	float speed;
	bool moveRight;

public:
	float leftLimit;
	float rightLimit;
	float xPosition, yPosition, zPosition; //Invaders position
	bool invaderAlive;


	void renderCollisionBox();
	void update();


	Invader();
	~Invader();
};