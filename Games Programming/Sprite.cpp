#include "Sprite.h"


Sprite::Sprite()
{
	position = glm::vec2(0, 0);
	size = glm::vec2(1, 1);
}


Sprite::~Sprite()
{
}

void Sprite::update(){ }

void Sprite::render()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTranslatef(position.x, position.y, 0);
	glScalef(size.x, size.y, 0);

	glBegin(GL_QUADS);

	glColor3f(255, 255, 255);

	glTexCoord2i(0, 0);
	glVertex2i(0, 0);

	glTexCoord2i(1, 0);
	glVertex2i(1, 0);

	glTexCoord2i(1, 1);
	glVertex2i(1, 1);

	glTexCoord2i(0, 1);
	glVertex2i(0, 1);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glPopMatrix();

	update();
}

void Sprite::SetTexture(GLuint t)
{
	textureID = t;
}

void Sprite::setBoundingRect(RECT* pRect)
{
	glm::vec2 sPos = getSpritePos();
	RECT theBoundingRect;
	theBoundingRect.left = sPos.x;
	theBoundingRect.top = sPos.y;
	theBoundingRect.right = textureWidth + sPos.x;
	theBoundingRect.bottom = textureHeight + sPos.y;

	SetRect(pRect, (int)theBoundingRect.left, (int)theBoundingRect.top, (int)theBoundingRect.right, (int)theBoundingRect.bottom);
}

RECT Sprite::getBoundingRect()		// Return the bounding rectangle for the sprite
{
	return Sprite::boundingRect;
}

void Sprite::renderCollisionBox()
{
	glPushMatrix();

	glTranslatef(boundingRect.left, boundingRect.top, 0.0f);


	glColor3f(255.0f, 0.0f, 0.0f);
	//glBegin(GL_LINE_LOOP);
	//glVertex2f(0, 0);
	//glVertex2f(0, boundingRect.bottom);
	//glVertex2f(boundingRect.right, boundingRect.bottom);
	//glVertex2f(boundingRect.right, 0);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(textureWidth, 0);
	glVertex2f(textureWidth, textureHeight);
	glVertex2f(0, textureHeight);


	glEnd();

	glPopMatrix();
}

glm::vec2 Sprite::getSpritePos()  // Return the sprites current position
{
	return Sprite::position;
}