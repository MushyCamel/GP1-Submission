#include "Invader.h"

#define INTERSECTION_DIST 2.5f
Invader::Invader()
{
	speed = 0;
	moveRight = true;

	leftLimit = 0;
	rightLimit = 400;
	invaderAlive = true;
	xPosition = 0.0f;
	yPosition = 0.0f;
	zPosition = -25.0f;
}


Invader::~Invader()
{
}

void Invader::update()
{
	position += glm::vec2(speed, 0);

	if (moveRight)
	{
		if (position.x >= rightLimit)
		{
			moveRight = false;
			position += glm::vec2(0, 50);
		}
		speed = 1;
	}
	else
	{
		if (position.x <= leftLimit)
		{
			moveRight = true;
			position += glm::vec2(0, 50);
		}

		speed = -1;
	}
}

bool Invader::collide(Bullet *bullet)
{
	if (invaderAlive && bullet[0].alive)
	{
		float distSquare = (xPosition - bullet[0].xPosition) * (xPosition - bullet[0].xPosition) + (yPosition - bullet[0].yPosition) * (yPosition - bullet[0].yPosition);

		if (distSquare <= INTERSECTION_DIST)
		{
			return true;
		}
	}
}

bool Invader::Destroy(void)
{
	invaderAlive = false;
	return false;
}

void Invader::renderCollisionBox()
{
	glPushMatrix();

	glTranslatef(boundingRect.left, boundingRect.top, 0.0f);
	//glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	//glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glColor3f(255.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	//glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	//glVertex2f((textureWidth / 2), -(textureHeight / 2));
	//glVertex2f((textureWidth / 2), (textureHeight / 2));
	//glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glVertex2f(-((boundingRect.right - boundingRect.left) / 2), -((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(((boundingRect.right - boundingRect.left) / 2), -((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(((boundingRect.right - boundingRect.left) / 2), ((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(-((boundingRect.right - boundingRect.left) / 2), ((boundingRect.bottom - boundingRect.top) / 2));
	glEnd();

	glPopMatrix();
	}
