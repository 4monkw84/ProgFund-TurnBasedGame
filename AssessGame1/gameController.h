#pragma once
#include "menuSystem.h"

class game {
	character player, enemy;

	//used to handle resetting the game
	bool gameStarted = false;
	//used to track wins/losses
	int wins = 0;
	int losses = 0;

	void coreLoop() {
		gameStarted = true;

		while (!player.checkIfDead() && !enemy.checkIfDead()) {
			if (!player.checkIfDead()) {
				player.upkeep();
				playerAction();
			}
			if (!enemy.checkIfDead()) {
				enemy.upkeep();
				enemyAction();
				Sleep(1500);
			}
		}

		if (player.checkIfDead()) {
			std::cout << "You lose." << std::endl;
			losses++;
			Sleep(1500);
			mainMenu();
		}
		else {
			std::cout << "You win!" << std::endl;
			wins++;
			Sleep(1500);
			mainMenu();
		}

		//reset game after it finishes
		player.initCharacter();
		enemy.initCharacter();
	}

	void mainMenu() {
		system("CLS");
		menu mainMenuObj;

		mainMenuObj.setOutputText({ "Turn based battle game\n" });
		mainMenuObj.setInputOptions({ "Play", "Rules", "Score", "Reset Game", "Quit" });
		mainMenuObj.printMenu(0);

		enum menuCase { playGame, showRules, score, resetGame, exitGame };
		switch (mainMenuObj.getInput()) {
		case playGame:
			coreLoop();
			break;

		case showRules:
			rulesMenu();
			break;

		case score:
			scoreMenu();
			break;

		case resetGame:
			if (gameStarted) {
				gameStarted = false;
				player.initCharacter();
				enemy.initCharacter();
				std::cout << "\nGame reset!" << std::endl;
				Sleep(1500);
				mainMenu();
			}
			else {
				std::cout << "\nGame hasn't begun, there's nothing to reset!" << std::endl;
				Sleep(1500);
				mainMenu();
			}

		case exitGame:
			exit(0);
		}
	}

	void rulesMenu() {
		system("CLS");
		menu rulesMenu;

		rulesMenu.setOutputText({
			"The aim of the game is to defeat your opponent before they defeat you!\n",
			"You may use the following actions:\n\n",
			"Attack: Deal 1-10 points of damage. 80% chance to hit.\n",
			"Special Attack: Deal 5-20 points of damage. 50% chance to hit. Expends 50 energy\n",
			"Recharge: Skip attack, quadruple energy regeneration on next turn, enemy gains 10% hit chance.\n",
			"Dodge: Decreases enemy accuracy by 30%, halves energy regeneration on next turn.\n",
			"Heal: Convert half of stored energy to health. May perform a second non-heal action this turn.\n" });
		rulesMenu.setInputOptions({ "Return" });
		rulesMenu.printMenu(0);

		enum menuCase { menu };
		switch (rulesMenu.getInput()) {
		case menu:
			mainMenu();
			break;
		}
	}

	void scoreMenu() {
		system("CLS");
		menu scoreMenu;

		//conversion of win/loss count for displaying
		std::string winCount = std::to_string(wins);
		std::string lossCount = std::to_string(losses);

		scoreMenu.setOutputText({ "Score Menu\n", "Wins: ", winCount, "\n", "Losses: ", lossCount, "\n" });
		scoreMenu.setInputOptions({ "Return" });
		scoreMenu.printMenu(0);

		enum menuCase { menu };
		switch (scoreMenu.getInput()) {
		case menu:
			mainMenu();
			break;
		}
	}

	void playerAction() {
		system("CLS");
		menu getPlayerAction;

		//converting attributes to string format to display
		std::string plrHealth = std::to_string(player.getHealth());
		std::string plrEnergy = std::to_string(player.getEnergy());
		std::string enmyHealth = std::to_string(enemy.getHealth());
		std::string enmyEnergy = std::to_string(enemy.getEnergy());

		//valid action check
		bool hasUsedValidAction = false;

		getPlayerAction.setOutputText({ "Player Health: ", plrHealth, "\n Player Energy: ", plrEnergy, "\n\n Enemy Health: ", enmyHealth, "\n Enemy Energy: ", enmyEnergy, "\n" });
		getPlayerAction.setInputOptions({ "Attack", "Special Attack", "Recharge", "Dodge", "Heal", "Pause Menu" });
		getPlayerAction.printMenu(0);

		while (!hasUsedValidAction) {
			enum actionCase { attack, spAttack, recharge, dodge, heal, menu };
			switch (getPlayerAction.getInput()) {
			case attack:
				hasUsedValidAction = player.attack(&enemy);
				break;

			case spAttack:
				hasUsedValidAction = player.specialAttack(&enemy);
				break;

			case recharge:
				hasUsedValidAction = player.rechargeAction();
				break;

			case dodge:
				hasUsedValidAction = player.dodgeAction();
				break;

			case heal:
				hasUsedValidAction = player.heal();
				break;

			case menu:
				hasUsedValidAction = true;
				mainMenu();
				break;
			}
		}
	}

	void enemyAction() {
		//if the player is or will be at max energy and is not dodging, assume incoming special attack and dodge
		if (((player.getEnergy() == player.getMaxEnergy()) || (player.getEnergy() + player.getEnergyRegenValue() >= player.getMaxEnergy())) && (player.getDodgeChance() <= player.getBaseDodgeChance()))
		{
			std::cout << "\nEnemy is dodging!" << std::endl;
			enemy.dodgeAction();
		}

		//if the enemy is low on energy, regen
		else if (enemy.getEnergy() <= 10)
		{
			std::cout << "\nEnemy is regenerating!" << std::endl;
			enemy.rechargeAction();
		}

		//if the enemy is under half health and hasn't already healed, heal
		else if (enemy.getHealth() <= (enemy.getMaxHealth() / 2) && !enemy.getHasHealed())
		{
			std::cout << "\nEnemy has healed!" << std::endl << std::endl;
			enemy.heal();
		}

		//if the enemy is at max energy and isn't actively dodging, special attack
		else if (enemy.getEnergy() == enemy.getMaxEnergy() && player.getDodgeChance() <= player.getBaseDodgeChance())
		{
			std::cout << "\nEnemy is using Special Attack!" << std::endl;
			enemy.attack(&player);
		}

		//if the enemy is close to max energy, regen in preperation for special attack
		else if (enemy.getEnergy() + (enemy.getEnergyRegenValue() * 4) >= enemy.getMaxEnergy())
		{
			std::cout << "\nEnemy is recharing energy!" << std::endl;
			enemy.rechargeAction();
		}

		//if there's nothing else better to do, a default attack will suffice
		else
		{
			std::cout << "\nEnemy is using Attack!" << std::endl;
			enemy.attack(&player);
		}
	}

public:
	game() {
		mainMenu();
	}
};