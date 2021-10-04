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

		mainMenu->setOutputText({ "Turn based battle game" });
		mainMenu->setInputOptions({ "Play", "Rules", "Quit" });
		mainMenu->printMenu();

		enum inputChoice {play = 1, rules, quit};

		switch (mainMenu->getInput()) {
		case play:
			mainLoop();
			break;

		case rules:
			rulesMenu();
			break;

		case quit:
			exit(0);
		}
	}

	void rulesMenu() {
		system("CLS");
		std::auto_ptr<menu> rulesMenu(new menu());

		rulesMenu->setOutputText({ 
			"The aim of the game is to defeat your opponent before they defeat you!", 
			"You may use the following actions:\n", 
			"Attack: Deal 1-10 points of damage. 80% chance to hit.", 
			"Special Attack: Deal 5-20 points of damage. 50% chance to hit. Expends 50 energy",
			"Recharge: Skip attack, quadruple energy regeneration on next turn, enemy gains 10% hit chance.",
			"Dodge: Decreases enemy accuracy by 30%, halves energy regeneration on next turn.",
			"Heal: Convert half of stored energy to health. May perform a second non-heal action this turn."});
		rulesMenu->setInputOptions({ "Return" });
		rulesMenu->printMenu();

		switch (rulesMenu->getInput()) {
		case 1:
			mainMenu();
			~std::auto_ptr<menu>;
			break;
		}
	}

	void playerAction() {

	}

public:
	game() {
		mainMenu();
	}
};