#include <stdlib.h>
#include <stats.h>
#include <string.h>

struct Stat *parse_stat(char *stat){
	if (stat[0] != '+') {
		return NULL;
	}

	int firstSpaceIndex = 0;

	while (stat[firstSpaceIndex] != ' '){
		firstSpaceIndex++;
	}

	struct Stat *result = (struct Stat *)malloc(sizeof(struct Stat));

	char *value =(char *)malloc(firstSpaceIndex * sizeof(char));
	if (!value) return NULL;

	memcpy(value, stat + 1, (firstSpaceIndex - 1) * sizeof(char));
	memcpy(result->name, stat + firstSpaceIndex + 1, (strlen(stat)) * sizeof(char));

	result->value = atof(value);

	free(value);

	return result;
}

