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
		if (getHealth() != maxHealth) {
			if (!hasHealed) {
				hasHealed = true;
				int healValue = energy / 2;
				energy /= 2;

				if (health + healValue > maxHealth) {
					int overhealValue = health + healValue - maxHealth;
					health = maxHealth;
					std::cout << "You healed for " << healValue << " points of health! " << overhealValue << "HP over-healed." << std::endl;
				}
				else{
					health += healValue;
					std::cout << "You healed for " << healValue << " points of health!" << std::endl;
				}
			}
			else
				std::cout << "Invalid action, you have healed recently." << std::endl;			
		}
		else
			std::cout << "Are you sure you want to do that? You're already max HP!" << std::endl;
		Sleep(1500);
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

	int getDodgeChance() {
		return dodge;
	}

	void attack(character* target) {
		int damageValue = (rand() % (attackMaxDamage - attackMinDamage)) + attackMinDamage;
		int hitRoll = (rand() % attackHitChance);
		if (hitRoll > target->getDodgeChance()) {
			target->damage(damageValue);
			std::cout << "The attack landed and dealt " << damageValue << " points of damage!" << std::endl;
		}
		else
			std::cout << "The attack missed!" << std::endl;
		Sleep(1500);
	}

	void specialAttack(character* target) {
		if (getEnergy() >= specialAttackCost) {
			energy -= specialAttackCost;
			int damageValue = (rand() % (spAttackMinDmg - spAttackMaxDmg)) + spAttackMinDmg;
			int hitRoll = (rand() % spAttackHitChance);
			if (hitRoll > target->getDodgeChance()) {
				target->damage(damageValue);
				std::cout << "The attack landed and dealt " << damageValue << " points of damage!" << std::endl;
			}
			else
				std::cout << "The attack missed!" << std::endl;
		}
		else
			std::cout << "Invalid action, not enough energy." << std::endl;
		Sleep(1500);
	}

	void rechargeAction() {
		isRecharging = true;
	}

	void dodgeAction() {
		dodge += dodgeActionGain;
		energyRegen /= 2;
	}
};