#pragma once
#include "Includes.h"
#include "cSoundMgr.h"

class Sprite
{
private:
	GLuint textureID;



public:
	glm::vec2 position;
	glm::vec2 size;
	//glm::vec2 spritePos2D;
	cSoundMgr* m_SoundMgr;

	int textureWidth;
	int textureHeight;
	RECT boundingRect;

	glm::vec2 getSpritePos();  // Return the sprites current position

	virtual void update();
	void render();
	void SetTexture(GLuint t);
	void setBoundingRect(RECT* pRect);		// Determine the bounding rectangle for the sprite
	RECT getBoundingRect();		// Determine the bounding rectangle for the sprite
	void renderCollisionBox();
	void attachSoundMgr(cSoundMgr* soundMgr);  // Attach the Sound Manager

	Sprite();
	~Sprite();
};

