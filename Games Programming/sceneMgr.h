#pragma once

#ifndef SCENEMGR_H
#define SCENEMGR_H


#include "GameConstants.h"
#include "cInputMgr.h"
#include "cSprite.h"
#include "cBkGround.h"
#include "cRocket.h"
#include "cInvader.h"
#include "cSoundMgr.h"
#include "cBullet.h"
#include "cFontMgr.h"


enum SCENES_ENUM
{
	intro = 0,
	game,
	endScreen,
};

class sceneMgr
{

private:	
	SCENES_ENUM scenes;
	int windowWidth;
	int windowHeight;
	bool sceneActive;
	cInputMgr* theInputMgr;
	cSoundMgr* theSoundMgr;
	cFontMgr* theFontMgr;

	int score;
	int scoreAdd;
	int total;

	cTexture rocketTxt;
	cRocket rocketSprite;
	cTexture gameUItexture;
	cTexture textureBkgd;

	cBkGround spriteBkgd;
	cTexture invaderTexture;
	cInvader invader;
	
	cTexture introScreenTexture;
	cTexture endScreenTextureWin;
	cTexture endScreenTextureLose;
	cBkGround introScreen;
	cBkGround EndScreenWin;
	cBkGround EndScreenLose;


public:
	sceneMgr(int windowWidthValue, int windowHeightValue, cInputMgr* theInputMgrValue, cSoundMgr* theSoundMgrValue, cFontMgr* theFontMgrValue);
	~sceneMgr();
	 //default constructor
	void update(double elapsedTime); //Update function

};

#endif