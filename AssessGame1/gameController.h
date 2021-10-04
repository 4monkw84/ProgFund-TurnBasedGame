#pragma once
#include "menuSystem.h"

class game {
	character player, enemy;

	void mainLoop() {

		std::cout << "main loop running";
		while (!player.checkIfDead() && !enemy.checkIfDead()) {
			player.upkeep();
			playerAction();
			player.damage(5);
			enemy.checkIfDead();
			enemy.upkeep();		
		}

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

		mainMenu->setOutputText({ "Turn based battle game\n" });
		mainMenu->setInputOptions({ "Play", "Rules", "Quit" });
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

		rulesMenu->setOutputText({ 
			"The aim of the game is to defeat your opponent before they defeat you!\n", 
			"You may use the following actions:\n\n", 
			"Attack: Deal 1-10 points of damage. 80% chance to hit.\n", 
			"Special Attack: Deal 5-20 points of damage. 50% chance to hit. Expends 50 energy\n",
			"Recharge: Skip attack, quadruple energy regeneration on next turn, enemy gains 10% hit chance.\n",
			"Dodge: Decreases enemy accuracy by 30%, halves energy regeneration on next turn.\n",
			"Heal: Convert half of stored energy to health. May perform a second non-heal action this turn.\n"});
		rulesMenu->setInputOptions({ "Return" });
		rulesMenu->printMenu();

		switch (rulesMenu->getInput()) {
		case 1:
			mainMenu();
			rulesMenu.release();
			break;
		}
	}

	void playerAction() {
		system("CLS");
		std::auto_ptr<menu> getPlayerAction(new menu());

		//converting attributes to string format to display
		std::string plrHealth = std::to_string(player.getHealth());
		std::string plrEnergy = std::to_string(player.getEnergy());
		std::string enmyHealth = std::to_string(enemy.getHealth());
		std::string enmyEnergy = std::to_string(enemy.getEnergy());

		getPlayerAction->setOutputText({ "Player Health: ", plrHealth, "\nPlayer Energy: ", plrEnergy, "\n\nEnemy Health: ", enmyHealth, "\nEnemy Energy: ", enmyEnergy, "\n" });
		getPlayerAction->setInputOptions({ "Attack", "Special Attack", "Recharge", "Dodge", "Heal", "Exit to menu" });
		getPlayerAction->printMenu();

		switch (getPlayerAction->getInput()) {
		case 1:
			player.attack(&enemy);
			break;
		
		case 2:
			player.specialAttack(&enemy);
			break;
		
		case 3:
			player.rechargeAction();
			break;
			
		case 4:
			player.dodgeAction();
			break;

		case 5:
			player.heal();
			playerAction();
			break;

		case 6:
			mainMenu();
			break;
		}
	}

public:
	game() {
		mainMenu();
	}
};