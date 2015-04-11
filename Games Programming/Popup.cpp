
#include "Popup.h"

// Pop up menu identifiers
int gameMenu, mainMenu;

// Config variables


bool gameRestart = false;

bool get_gameRestart(void)
{
	return gameRestart;
}

void set_gameRestart(bool status)
{
	gameRestart = status;
}





void processGameMenuEvents(int option)
{
	if (option == 1)
	{
		gameRestart = true;
	}
}




// --------------------------------------------------------------------------------------------------
void processMainMenuEvents(int option)
{
	switch (option)
	{
	case 1: // Close the program
		exit(0);
		break;
	}
}

// --------------------------------------------------------------------------------------------------
/***** GLUT menus *****/

void init_menus(void)
{
	
	// Submenu Particle Color
	gameMenu = glutCreateMenu(processGameMenuEvents);
	glutAddMenuEntry("RESTART", 1);

	// Main Menu
	mainMenu = glutCreateMenu(processMainMenuEvents);


	
	glutAddSubMenu("Game Options", gameMenu);
	glutAddMenuEntry("Exit", 1);
	glutAddMenuEntry("D - Left, F - Right, Spacebar - shoot.", gameMenu);

	// Attach the menu to the right button
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
}
