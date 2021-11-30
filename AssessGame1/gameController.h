#pragma once
#include "menuSystem.h"

class game {
	character player, enemy;

	void coreLoop() {
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
		}
		else {
			std::cout << "You win!" << std::endl;
		}
	}

	void mainMenu() {
		system("CLS");
		std::auto_ptr<menu> mainMenu(new menu());

		mainMenu->setOutputText({ "Turn based battle game\n" });
		mainMenu->setInputOptions({ "Play", "Rules", "Reset Game", "Quit" });
		mainMenu->printMenu(0);

		enum menuCase { beginGame, showRules, resetGame, exitGame };
		switch (mainMenu->getInput()) {
		case beginGame:
			coreLoop();
			break;

		case showRules:
			rulesMenu();
			break;

		case resetGame:
			//TODO: breaks game when used before starting
			player.initCharacter();
			enemy.initCharacter();
			std::cout << "Game reset!" << std::endl;
			Sleep(1500);
			playerAction();
			break;

		case exitGame:
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
			"Heal: Convert half of stored energy to health. May perform a second non-heal action this turn.\n" });
		rulesMenu->setInputOptions({ "Return" });
		rulesMenu->printMenu(0);

		enum menuCase { menu };
		switch (rulesMenu->getInput()) {
		case menu:
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

		//valid action check
		bool hasUsedValidAction = false;

		getPlayerAction->setOutputText({ "Player Health: ", plrHealth, "\nPlayer Energy: ", plrEnergy, "\n\nEnemy Health: ", enmyHealth, "\nEnemy Energy: ", enmyEnergy, "\n" });
		getPlayerAction->setInputOptions({ "Attack", "Special Attack", "Recharge", "Dodge", "Heal", "Pause Menu" });
		getPlayerAction->printMenu(0);

		while (!hasUsedValidAction) {
			enum actionCase { attack, spAttack, recharge, dodge, heal, menu };
			switch (getPlayerAction->getInput()) {
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
			std::cout << "Enemy is dodging!" << std::endl;
			enemy.dodgeAction();
		}

		//if the enemy is low on energy, regen
		else if (enemy.getEnergy() <= 10)
		{
			std::cout << "Enemy is regenerating!" << std::endl;
			enemy.rechargeAction();
		}

		//if the enemy is under half health and hasn't already healed, heal
		else if (enemy.getHealth() <= (enemy.getMaxHealth() / 2) && !enemy.getHasHealed())
		{
			std::cout << "Enemy has healed!" << std::endl << std::endl;
			enemy.heal();
		}

		//if the enemy is at max energy and isn't actively dodging, special attack
		else if (enemy.getEnergy() == enemy.getMaxEnergy() && player.getDodgeChance() <= player.getBaseDodgeChance())
		{
			std::cout << "Enemy is using Special Attack!" << std::endl;
			enemy.attack(&player);
		}

		//if the enemy is close to max energy, regen in preperation for special attack
		else if (enemy.getEnergy() + (enemy.getEnergyRegenValue() * 4) >= enemy.getMaxEnergy())
		{
			std::cout << "Enemy is recharing energy!" << std::endl;
			enemy.rechargeAction();
		}

		//if there's nothing else better to do, a default attack will suffice
		else
		{
			std::cout << "Enemy is using Attack!" << std::endl;
			enemy.attack(&player);
		}
	}

public:
	game() {
		mainMenu();
	}
};