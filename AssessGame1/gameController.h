#pragma once
#include "menuSystem.h"

class game {
	character player, enemy;

	void mainLoop() {

		std::cout << "main loop running";
		/*while (!player.checkIfDead() && !enemy.checkIfDead()) {
			player.upkeep();
			//playerAction();
			enemy.checkIfDead();
			enemy.upkeep();		
		}*/

		if (player.checkIfDead()) {
			std::cout << "You lose." << std::endl;
		}
		else {
			std::cout << "You win!" << std::endl;
		}
	}

	void mainMenu() {
		system("CLS");
		std::auto_ptr<menu> mainMenu(new menu());
		mainMenu->printMenu();
		switch (mainMenu->getInput()) {
		case 1:
			mainLoop();
			break;

		case 2:
			rulesMenu();
			break;

		case 3:
			exit(0);
		}
	}

	void rulesMenu() {
		system("CLS");
		std::auto_ptr<menu> rulesMenu(new menu());
		rulesMenu->printMenu();
		switch (rulesMenu->getInput()) {
		case 1:
			mainMenu();
			break;
		}
	}

public:
	game() {
		mainMenu();
	}
};