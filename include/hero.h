#ifndef HERO_H
#define HERO_H

#include "stats.h"
#include "items.h"

struct HeroItems{
	struct Item *headgear;
	struct Item *faceAccessory;
	struct Item *armor;
	struct Item *gloves;
	struct Item *greaves;
	struct Item *footwear;

	struct Item *decoration;
	struct Item *amulet;
	struct Item *rings;
	struct Item *totem;
	struct Item *artifact;
	struct Item *mount;
	
	struct Item *shield;

	struct Item *weapon;
};

struct Hero{
	struct HeroItems *items;
	struct HeroStats *stats;
};

void recalculateStats(struct HeroStats *stats, struct HeroItems *itmes);

#endif
