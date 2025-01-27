#ifndef ITEMS_H
#define ITEMS_H
#define MAX_ITEM_NAME_LENGTH 255

#include "enums.h"
#include "stats.h"

struct Card{
	char name[MAX_ITEM_NAME_LENGTH];
	char *icon;

	void (*proccesStats)(struct HeroStats);
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

	void (*proccesStats)(struct HeroStats);
};
#endif
