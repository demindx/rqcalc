/*#include <gtk/gtk.h>*/
#include "stats.h"
/*#include "external/uthash.h"*/
#include "external/cJSON.h"

#define UTILS_IMPLEMENTATION
#include "utils.h"


int main(int argc, char *argv[]){
    cJSON *weapons = get_json_from_file("data/weapons.json");
    cJSON *item = cJSON_GetObjectItemCaseSensitive(weapons,"Абордажная сабля");
    cJSON *stats = cJSON_GetObjectItemCaseSensitive(item, "stats");
    cJSON *stat = cJSON_GetArrayItem(stats, 1);

    struct Stat *item_stat = parse_stat(stat->valuestring);

    cJSON_Delete(weapons);
    free(item_stat);
}
