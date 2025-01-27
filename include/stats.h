#ifndef STATS_H
#define STATS_H

#include "enums.h"

struct HeroStats{
	enum HeroClass class;

	// BASE stats
	
	int health;
	int classEnergy;

	int mainClassStat;
	int dexterity;
	int stamina;
	int luck;

	int attack;
	int attackSpeed;
	int defense;
	int hit;
	int dodge;
	float criticalHitChance;
	int criticalHit;

	// EXTRA stats
	// GENERAL
	int experienceObtained;
	int goldObtained;
	int chanceOfLootDrops;
	int movementSpeed;
	int attackRange;

	// HIT ?
	
	// SURVIVAL
	float healthRestoration;
	float energyRestoration;

	// PvP
	int damage;
	int damageResistance;
	int controlResistance;

	// ELEMENTAL DAMAGE
	int fire;
	int water;
	int earth;
	int air;
	int chaos;
	int poison;

	// ELEMENTAL RESISTANCE
	int fireResistance;
	int waterResistance;
	int earthResistance;
	int airResistance;
	int chaosResistance;
	int poisonResistance;


	// RACE DAMAGE RESISTANCE
	int humanoidsResistance;
	int animalsResistance;
	int plantsResistance;
	int undeadResistance;
	int orcsResistance;
	int amphibiansResistance;
	int magicalResistance;
	int shapelessResistance;
	int monstrositiesResistance;
	int insectsResistance;
	int mechanismsResistance;
};

#endif
