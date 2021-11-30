#pragma once

class character {
	//attribute default valus:
	const int maxHealth = 100;
	const int maxEnergy = 50;
	const int defaultRegen = 5;
	const int defaultDodge = 2;
	const int dodgeActionGain = 3;
	const int rechargingMultiplier = 4;

	//attack specific:
	const int basicAttackCost = 10;
	const int specialAttackCost = 50;
	const int attackMinDamage = 1;
	const int attackMaxDamage = 10;
	const int attackHitChance = 8;
	const int spAttackMinDmg = 5;
	const int spAttackMaxDmg = 20;
	const int spAttackHitChance = 5;

	//attributes
	int health = maxHealth;
	int energy = maxEnergy;
	int energyRegen = defaultRegen;
	int dodge = defaultDodge;
	bool isDead = false;
	bool hasHealed = false;
	bool isRecharging = false;

public:

	void initCharacter() {
		health = maxHealth;
		energy = maxEnergy;
		energyRegen = defaultRegen;
		dodge = defaultDodge;
		isDead = false;
		hasHealed = false;
		isRecharging = false;
	}

	bool checkIfDead() {
		if (health <= 0)
			return true;
		else
			return false;
	}

	void upkeep() {
		//energy regen
		if (energy != maxEnergy && energy <= (maxEnergy - energyRegen))
			energy += energyRegen;
		else
			energy += (maxEnergy - energy);

		//reset stats for turn
		hasHealed = false;
		dodge = defaultDodge;
		energyRegen = defaultRegen;
	}

	int getHealth() {
		return health;
	}

	int getMaxHealth() {
		return maxHealth;
	}

	bool heal() {
		if (getHealth() != maxHealth) {
			if (!hasHealed) {
				hasHealed = true;
				int healValue = energy / 2;
				energy /= 2;

				if (health + healValue > maxHealth) {
					int overhealValue = health + healValue - maxHealth;
					health = maxHealth;
					std::cout << "\nHealed for " << healValue << " points of health! " << overhealValue << "HP over-healed." << std::endl;
					Sleep(1500);
					return true;
				}
				else {
					health += healValue;
					std::cout << "\nHealed for " << healValue << " points of health!" << std::endl;
					Sleep(1500);
					return true;
				}
			}
			else {
				std::cout << "\nInvalid action, you have healed recently." << std::endl;
				Sleep(1500);
				return false;
			}
		}
		else {
			std::cout << "\nAre you sure you want to do that? You're already max HP!" << std::endl;
			Sleep(1500);
			return false;
		}
	}

	bool getHasHealed() {
		return hasHealed;
	}

	void damage(int damageValue) {
		health -= damageValue;
	}

	int getEnergy() {
		return energy;
	}

	int getEnergyRegenValue() {
		return energyRegen;
	}

	int getMaxEnergy() {
		return maxEnergy;
	}

	bool increaseEnergy() {
		if (isRecharging) {
			if (energy += energyRegen > maxEnergy) {
				energy = maxEnergy;
				isRecharging = false;
			}
			else
				energy += energyRegen;
		}
		return true;
	}

	void reduceEnergy(int val) {
		energy -= val;
	}


	bool attack(character* target) {
		int damageValue = (rand() % (attackMaxDamage - attackMinDamage)) + attackMinDamage;
		int hitRoll = (rand() % attackHitChance);
		if (hitRoll > target->getDodgeChance()) {
			target->damage(damageValue);
			std::cout << "\nThe attack landed and dealt " << damageValue << " points of damage!" << std::endl;
		}
		else
			std::cout << "\nThe attack missed!" << std::endl;
		Sleep(1500);
		return true;
	}

	bool specialAttack(character* target) {
		if (getEnergy() >= specialAttackCost) {
			energy -= specialAttackCost;
			int damageValue = (rand() % (spAttackMinDmg - spAttackMaxDmg)) + spAttackMinDmg;
			int hitRoll = (rand() % spAttackHitChance);
			if (hitRoll > target->getDodgeChance()) {
				target->damage(damageValue);
				std::cout << "\nThe attack landed and dealt " << damageValue << " points of damage!" << std::endl;
				Sleep(1500);
				return true;
			}
			else {
				std::cout << "\nThe attack missed!" << std::endl;
				Sleep(1500);
				return true;
			}
		}
		else {
			std::cout << "\nInvalid action, not enough energy." << std::endl;
			Sleep(1500);
			return false;
		}
	}

	bool rechargeAction() {
		isRecharging = true;
		return true;
	}

	bool dodgeAction() {
		dodge += dodgeActionGain;
		energyRegen /= 2;
		return true;
	}

	int getDodgeChance() {
		return dodge;
	}

	int getBaseDodgeChance() {
		return defaultDodge;
	}
};