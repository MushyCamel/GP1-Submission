#include "sceneMgr.h"


sceneMgr::sceneMgr(int windowWidthValue, int windowHeightValue, cInputMgr* theInputMgrValue, cSoundMgr* theSoundMgrValue, cFontMgr* theFontMgrValue)
{
	scenes = intro;
	windowHeight = windowHeightValue;
	windowWidth = windowWidthValue;
	theInputMgr = theInputMgrValue;
	theSoundMgr = theSoundMgrValue;
	theFontMgr = theFontMgrValue;

	sceneActive = false;

	//------------------------------------------------------------------------------------------
	//Load in resorces
	//------------------------------------------------------------------------------------------

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Audio/FIRE.wav", "Audio/Theme.wav", "Audio/GRM_EXP.wav" };

	//theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("FIRE", gameSounds[0]);
	theSoundMgr->add("Theme", gameSounds[1]);
	theSoundMgr->add("BOOM", gameSounds[2]);

	// Create vector array of textures
	LPCSTR texturesToUse[] = { "Images\\alien1.png",  "Images\\bullet.png" };
	for (int tCount = 0; tCount < 2; tCount++)
	{
		theGameTextures.push_back(new cTexture());
		theGameTextures[tCount]->createTexture(texturesToUse[tCount]);
	}

	textureBkgd.createTexture("Images\\Background.png");

	rocketTxt.createTexture("Images\\Ship.png");

	introScreenTexture.createTexture("Images\\IntroScreen.png");
	endScreenTextureWin.createTexture("Images\\EndScreenWin.png");
	endScreenTextureLose.createTexture("Images\\EndScreenLose.png");


	spriteBkgd.setSpritePos(glm::vec2(0, 0));
	spriteBkgd.setTexture(textureBkgd.getTexture());
	spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());

	introScreen.setSpritePos(glm::vec2(0, 0));
	introScreen.setTexture(introScreenTexture.getTexture());
	introScreen.setTextureDimensions(introScreenTexture.getTWidth(), introScreenTexture.getTHeight());

	EndScreenWin.setSpritePos(glm::vec2(0, 0));
	EndScreenWin.setTexture(endScreenTextureWin.getTexture());
	EndScreenWin.setTextureDimensions(endScreenTextureWin.getTWidth(), endScreenTextureWin.getTHeight());

	EndScreenLose.setSpritePos(glm::vec2(0, 0));
	EndScreenLose.setTexture(endScreenTextureLose.getTexture());
	EndScreenLose.setTextureDimensions(endScreenTextureLose.getTWidth(), endScreenTextureLose.getTHeight());

	rocketSprite.attachInputMgr(theInputMgr);
	rocketSprite.attachSoundMgr(theSoundMgr);

	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/Space.ttf" };

	
	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);


	//sets up the invaders
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 25; x++)
		{
			theInvaders.push_back(new cInvader);
			theInvaders[y, x]->spritePos2D = glm::vec2(10 + (30 * x), 10 + (30 * y));
			theInvaders[y, x]->setTexture(theGameTextures[0]->getTexture());
			theInvaders[y, x]->setTextureDimensions(theGameTextures[0]->getTWidth(), theGameTextures[0]->getTHeight());
			theInvaders[y, x]->setSpriteCentre();
			theInvaders[y, x]->setActive(true);
			theInvaders[y, x]->setMdlRadius();

		}
	}


	score = 0;
	scoreAdd = 10;

}


sceneMgr::~sceneMgr()
{
}


void sceneMgr::update(double elapsedTime)
{
	//Intro Screen menu -------------------------------
	if (scenes == intro)
	{

		if (!sceneActive)
		{
			sceneActive = true;
		}

		if (sceneActive)
		{

			introScreen.render();

			if (theInputMgr->isKeyDown(VK_RETURN))
			{
				sceneActive = false;
				scenes = game;
			}

		}

	}

	//Main game scene ---------------------------
	if (scenes == game)
	{
		if (!sceneActive)
		{
	
			rocketSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
			rocketSprite.setSpritePos(glm::vec2(400, 500));
			rocketSprite.setTexture(rocketTxt.getTexture());
			rocketSprite.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
			rocketSprite.setSpriteCentre();
			rocketSprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));
			rocketSprite.renderCollisionBox();
			rocketSprite.attachSoundMgr(theSoundMgr);
			sceneActive = true;
		}

		if (sceneActive)
		{

	

			spriteBkgd.render();

			vector<cInvader*>::iterator invaderIterator = theInvaders.begin();
			while (invaderIterator != theInvaders.end())
			{
				if ((*invaderIterator)->isActive() == false)
				{
					invaderIterator = theInvaders.erase(invaderIterator);


				}
				else
				{
					(*invaderIterator)->update(elapsedTime);
					(*invaderIterator)->render();
					++invaderIterator;
				}
			}

			/*
			==============================================================
			| Check for collisions
			==============================================================
			*/
			for (vector<cBullet*>::iterator bulletIterartor = theBullets.begin(); bulletIterartor != theBullets.end(); ++bulletIterartor)
			{
				(*bulletIterartor)->update(elapsedTime);
				for (vector<cInvader*>::iterator invaderIterator = theInvaders.begin(); invaderIterator != theInvaders.end(); ++invaderIterator)
				{
					if ((*invaderIterator)->collidedWith((*invaderIterator)->getBoundingRect(), (*bulletIterartor)->getBoundingRect()))
					{
						// if a collision set the bullet and asteroid to false
						(*invaderIterator)->setActive(false);
						(*bulletIterartor)->setActive(false);
						score += 10;
					
					}
				}
			}

			vector<cBullet*>::iterator bulletIterartor = theBullets.begin();
			while (bulletIterartor != theBullets.end())
			{
				if ((*bulletIterartor)->isActive() == false)
				{
					bulletIterartor = theBullets.erase(bulletIterartor);
					// play the explosion sound.
					theSoundMgr->getSnd("BOOM")->playAudio(AL_TRUE);
				}
				else
				{
					//(*bulletIterartor)->update(deltaTime);
					(*bulletIterartor)->render();
					++bulletIterartor;
				}
			}
			rocketSprite.update(elapsedTime);
			rocketSprite.render();

			if (score >= 250)
			{
				sceneActive = false;
				scenes = endScreen;
		
			}
			string s = to_string(score);
			LPCSTR convert = s.c_str();
			theFontMgr->getFont("Space")->printText("Score: ", FTPoint(0.0f, -50.0f, 0.0f));
			theFontMgr->getFont("Space")->printText(convert, FTPoint(100.0f, -50.0f, 0.0f));
		}
	}



	//end screen menu ---------------------------------------
		if (scenes == endScreen)
		{
			if (!sceneActive)
			{
				sceneActive = true;
			}

			if (sceneActive)
			{
				EndScreenWin.render();
				string s = to_string(score);
				LPCSTR convert = s.c_str();
				theFontMgr->getFont("Space")->printText("Your score was: ", FTPoint(240.f, -270.f, 0.0f));
				theFontMgr->getFont("Space")->printText(convert, FTPoint(440.f, -270.0f, 0.0f));

			

			}

			if (theInputMgr->isKeyDown(VK_ESCAPE))
			{
				sceneActive = false;
				exit(0);
			}
		}
}
	

