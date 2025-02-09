#ifndef ITEMS_H
#define ITEMS_H

#define MAX_ITEM_NAME_LENGTH 255

#include "enums.h"
#include "stats.h"


struct Seal {
	char name[MAX_ITEM_NAME_LENGTH];
	struct Stat *greenStats;
	struct Stat *blueStats;
	struct Stat *violetStats;
	struct Stat *orangeStats;
};


struct Card{
	char name[MAX_ITEM_NAME_LENGTH];
	char *icon;

	int statsLength;
	struct Stat *stats;
};


struct Item {
	char name[MAX_ITEM_NAME_LENGTH];
	char *icon;

	enum itemClass class;
	enum itemType type;

	int upgradeLevel;
	int mainStat;

	int cardSlotsLenght;
	struct Card *cards;

	int statsLength;
	struct Stat *stats;

	struct Seal *seal;
};

#endif
