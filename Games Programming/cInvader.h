/*
=================
cAsteroid.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CINVADER_H
#define _CINVADER_H
#include "cSprite.h"

class cInvader : public cSprite
{
private:
	glm::vec2 invaderVelocity = glm::vec2(0.0f, 0.0f);

	float speed;
	bool moveRight;


public:
	float leftLimit;
	float rightLimit;
	float xPosition, yPosition, zPosition; //Invaders position

	cInvader();
	~cInvader();

	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void setinvaderVelocity(glm::vec2 asteroidVel);   // Sets the velocity for the rocket
	glm::vec2 getinvaderVelocity();				 // Gets the rocket velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif