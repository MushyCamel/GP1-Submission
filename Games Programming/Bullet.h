#pragma once
#include "Sprite.h"

class Bullet: public Sprite
{
public:
	bool alive;
	float xPosition, yPosition, zPosition;

	void update();
	void renderCollisionBox();
	

	Bullet();
	~Bullet();
};