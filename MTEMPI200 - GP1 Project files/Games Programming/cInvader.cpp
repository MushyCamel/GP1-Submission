/*
=================
cInvader.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cInvader.h"

void cInvader::render()
{


	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);

	glScalef(size.x, size.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cInvader::update(float deltaTime)
{
	spritePos2D += glm::vec2(speed, 0);

	if (moveRight)
	{
		if (spritePos2D.x >= rightLimit)
		{
			moveRight = false;
			spritePos2D += glm::vec2(0, 50);
		}
		speed = 3;
		
	}
	else
	{
		if (spritePos2D.x <= leftLimit)
		{
			moveRight = true;
			spritePos2D += glm::vec2(0, 50);
		}

		speed = -3;
	}




	setBoundingRect(&boundingRect);
}
/*
=================================================================
  Sets the velocity for the Asteroid
=================================================================
*/
void cInvader::setinvaderVelocity(glm::vec2 AsteroidVel)
{
	invaderVelocity = AsteroidVel;
}
/*
=================================================================
  Gets the Asteroid velocity
=================================================================
*/
glm::vec2 cInvader::getinvaderVelocity()
{
	return invaderVelocity;
}
/*
==========================================================================
Use this method to show the collision box.
==========================================================================
*/
void cInvader::renderCollisionBox()
{
	glPushMatrix();

	glTranslatef(boundingRect.left, boundingRect.top, 0.0f);
	//glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	//glScalef(size.x, size.y, 1.0f);

	glColor3f(255.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	//glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	//glVertex2f((textureWidth / 2), -(textureHeight / 2));
	//glVertex2f((textureWidth / 2), (textureHeight / 2));
	//glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glVertex2f(-((boundingRect.right - boundingRect.left) / 2), -((boundingRect.bottom - boundingRect.top)/2));
	glVertex2f(((boundingRect.right - boundingRect.left) / 2), -((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(((boundingRect.right - boundingRect.left) / 2), ((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(-((boundingRect.right - boundingRect.left) / 2), ((boundingRect.bottom - boundingRect.top) / 2));
	glEnd();

	glPopMatrix();
}

cInvader::cInvader(){

	leftLimit = 10;
	rightLimit = 790;
	speed = 0;
	moveRight = true;

}



cInvader::~cInvader(){

}