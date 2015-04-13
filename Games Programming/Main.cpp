#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cSprite.h"
#include "invadersGame.h"




int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR cmdLine,
	int cmdShow)
{

	//Set our window settings
	const int windowWidth = 800;
	const int windowHeight = 600;
	const int windowBPP = 16;

	

	//This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	//The example OpenGL code
	windowOGL theOGLWnd;

	//Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

	//Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
	{
		//If it fails

		MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
	{
		MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// Create vector array of textures
	LPCSTR texturesToUse[] = { "Images\\alien1.png", "Images\\alien2.png", "Images\\alien3.png", "Images\\alien4.png", "Images\\bullet.png" };
	for (int tCount = 0; tCount < 5; tCount++)
	{
		theGameTextures.push_back(new cTexture());
		theGameTextures[tCount]->createTexture(texturesToUse[tCount]);
	}

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Audio/FIRE.wav", "Audio/Theme.wav", "Audio/GRM_EXP.wav" };

	//theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("FIRE", gameSounds[0]);
	theSoundMgr->add("Theme", gameSounds[1]);
	theSoundMgr->add("BOOM", gameSounds[2]);

	// load game fontss
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);


	
	
		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 25; x++)
			{
				theInvaders.push_back(new cInvader);
				theInvaders[y, x]->spritePos2D = glm::vec2(10 + (30 * x), 10 + (30 * y));
				theInvaders[y, x]->setSpriteTranslation(glm::vec2((rand() % 4 + 1), (rand() % 4 + 1)));
				theInvaders[y, x]->setTexture(theGameTextures[0]->getTexture());
				theInvaders[y, x]->setTextureDimensions(theGameTextures[0]->getTWidth(), theGameTextures[0]->getTHeight());
				theInvaders[y, x]->setSpriteCentre();
				theInvaders[y, x]->setActive(true);
				theInvaders[y, x]->setMdlRadius();

			}
		}

		

	
		cTexture textureBkgd;
		textureBkgd.createTexture("Images\\Background.png");
		cBkGround spriteBkgd;
		spriteBkgd.setSpritePos(glm::vec2(0, 0));
		spriteBkgd.setTexture(textureBkgd.getTexture());
		spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());

		cTexture rocketTxt;
		rocketTxt.createTexture("Images\\Ship.png");
		cRocket rocketSprite;
		rocketSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
		rocketSprite.setSpritePos(glm::vec2(400, 500));
		rocketSprite.setTexture(rocketTxt.getTexture());
		rocketSprite.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
		rocketSprite.setSpriteCentre();
		rocketSprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));
		rocketSprite.renderCollisionBox();

		// Attach sound manager to rocket sprite
		rocketSprite.attachSoundMgr(theSoundMgr);


		theSoundMgr->getSnd("Theme")->playAudio(AL_TRUE);

		//This is the mainloop, we render frames until isRunning returns false
		while (pgmWNDMgr->isWNDRunning())
		{
			pgmWNDMgr->processWNDEvents(); //Process any window events



			//We get the time that passed since the last frame
			float elapsedTime = pgmWNDMgr->getElapsedSeconds();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			spriteBkgd.render();

			rocketSprite.update(elapsedTime);



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

			rocketSprite.render();


			pgmWNDMgr->swapBuffers();
			theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
		}

		theOGLWnd.shutdown(); //Free any resources
		pgmWNDMgr->destroyWND(); //Destroy the program window

		return 0; //Return success
	}
