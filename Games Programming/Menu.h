#pragma once
#include "Includes.h"



class Menu{

public:
	// Pop up menu identifiers
	int gameMenu, mainMenu;

	// Config variables
	
	bool gameRestart;


	void init_menus(void);
	bool get_gameRestart(void);
	void set_gameRestart(bool status);
};

	

