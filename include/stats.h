#ifndef STATS_H
#define STATS_H

#define MAX_NAME_LENGTH 255

#include "enums.h"

struct HeroStats{
	enum HeroClass class;

	// BASE stats
	int level;
	int points;

	float health;
	float classEnergy;

	float mainClassStat;
	float dexterity;
	float stamina;
	float luck;

	float attack;
	float attackSpeed;
	float defense;
	float hit;
	float dodge;
	float criticalHitChance;
	float criticalHit;

	// EXTRA stats
	// GENERAL
	float experienceObtained;
	float goldObtained;
	float chanceOfLootDrops;
	float movementSpeed;
	float attackRange;

	// HIT ?
	
	// SURVIVAL
	float healthRestoration;
	float energyRestoration;

	// PvP
	float damage;
	float damageResistance;
	float controlResistance;

	// ELEMENTAL DAMAGE
	float fire;
	float water;
	float earth;
	float air;
	float chaos;
	float poison;

	// ELEMENTAL RESISTANCE
	float fireResistance;
	float waterResistance;
	float earthResistance;
	float airResistance;
	float chaosResistance;
	float poisonResistance;


	// RACE DAMAGE RESISTANCE
	float humanoidsResistance;
	float animalsResistance;
	float plantsResistance;
	float undeadResistance; 
	float orcsResistance;
	float amphibiansResistance;
	float magicalResistance;
	float shapelessResistance;
	float monstrositiesResistance;
	float insectsResistance;
	float mechanismsResistance;
};


struct Stat{
	char name[MAX_NAME_LENGTH];
	float value;
};


struct Stat *parse_stat(char *stat);

#endif
