#include "Includes.h"
#include "Sprite.h"
#include "cTexture.h"
#include "Bullet.h"
#include "Invader.h"
#include "Popup.h"
#include "cFontMgr.h"
#include "cFont.h"
#include "cSoundMgr.h"
#include "cSound.h"




vector<Invader*> theInvaders;
vector<Bullet*> theBullets;
std::vector<Sprite*> sprites;

void resize(int width, int height);
void render();
void keyboard(unsigned char k, int x, int y);
void SetupInvaders();
void init_menus();
void Play(unsigned char k, int x, int y);




// load game fontss
// Load Fonts
LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };




//loads in game sounds
LPCSTR gameSounds[5] = { "Audio/Theme.wav", "Audio/FIRE.wav", "Audio/GRM_EXP.wav", "Audio/GUN_HIT.wav", "Audio/INVADERS.wav"  };


static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();


int main(int argc, char **argv)
{
	//Start OpenGL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);


	//Create Window
	glutInitWindowSize(800, 600);
	glutCreateWindow("Invaders From Space");

	theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("FIRE", gameSounds[1]);
	theSoundMgr->add("GRM_EXP", gameSounds[2]);
	theSoundMgr->add("INVADERS", gameSounds[4]);

	//Game Code
	cTexture t = cTexture("Images/Ship.png");
	Sprite* s = new Sprite();
	s->position = glm::vec2(400, 500);
	s->size = glm::vec2(50, 50);
	s->SetTexture(t.getTexture());
	s->renderCollisionBox();
	
	
	sprites.push_back(s);


	

	//calls the method
	SetupInvaders();


	//calls the method
	init_menus();

	for (vector<Bullet*>::iterator b = theBullets.begin(); b != theBullets.end(); ++b)
	{
		(*b)->update();
		for (vector<Invader*>::iterator i = theInvaders.begin(); i != theInvaders.end(); ++i)
		{
			if ((*i)->collidedWith((*b)->getBoundingRect(), (*i)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				(*i)->setActive(false);
				(*b)->setActive(false);
			}
		}
	}

	vector<Bullet*>::iterator b = theBullets.begin();
	while (b != theBullets.end())
	{
		if ((*b)->isActive() == false)
		{
			b = theBullets.erase(b);
			// play the explosion sound.
			theSoundMgr->getSnd("GRM_EXP")->playAudio(AL_TRUE);
		}
		else
		{
		
			(*b)->render();
			++b;
		}
	}


	

	//Open GL Functions
	glutReshapeFunc(resize);
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);

	//if there is an error with glew this returns it
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW error");
		return 1;
	}

	glutMainLoop();
	return 0;
}

//This creates the invaders
void SetupInvaders()
{
	cTexture tI = cTexture("Images/alien1.png");
	//creates the invaders to have five on the y
	for (int y = 0; y < 5; y++)
	{
		//8 on the x for every y
		for (int x = 0; x < 8; x++)
		{
			//loads the invader texture and sets size
			Invader* i = new Invader();
			i->position = glm::vec2(10 + (40 * x), 10 + (40 * y));
			i->size = glm::vec2(25, 25);
			i->leftLimit = 0;
			i->rightLimit = 800;
			i->SetTexture(tI.getTexture());	
			i->renderCollisionBox();
			i->isActive() == true;
			
			sprites.push_back(i);
			

		}
		
	}
}

//Allows the resizing of the window
void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}


//renders Sprites
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (Sprite* s : sprites)
	{
		s->render();

	}

	glutSwapBuffers();
	glutPostRedisplay();

	
}

//input control
void keyboard(unsigned char k, int x, int y)
{
	//Makes the ship move left
	if (k == GLUT_KEY_LEFT)
	{
		sprites[0]->position.x -= 5;
	}
	//Makes the ship move right
	else if (k == GLUT_KEY_RIGHT)
	{
		sprites[0]->position.x += 5;
	}

	//if space is pressed create bullet 
	if (k == ' ')
	{
		cTexture t = cTexture("Images/Bullet.png");
		Bullet* b = new Bullet();
		b->position = sprites[0]->position + glm::vec2(20, 0);
		b->size = glm::vec2(10, 10);
		b->SetTexture(t.getTexture());
		b->renderCollisionBox();
		sprites.push_back(b);
	
		theSoundMgr->getSnd("FIRE")->playAudio(AL_TRUE);
	}

}


