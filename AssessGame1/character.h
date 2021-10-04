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

	void heal() {
		if (!hasHealed) {
			hasHealed = true;
			int healValue = energy / 2;
			if (health + healValue > maxHealth)
				health = maxHealth;
			else
				health += healValue;
		}
		else
			std::cout << "Invalid action, you have healed recently." << std::endl;
	}

	void damage(int damageValue) {
		health -= damageValue;
	}

	int getEnergy() {
		return energy;
	}

	void increaseEnergy() {
		if (isRecharging) {
			if (energy += energyRegen > maxEnergy){
				energy = maxEnergy;
				isRecharging = false;
			}
			else 
				energy += energyRegen;
		}
	}

	void reduceEnergy(int val) {
		energy -= val;
	}
};