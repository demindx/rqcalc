#ifndef UTILS_H
#define UTILS_H

#include "external/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/*#define UTILS_IMPLEMENTATION*/

cJSON *get_json_from_file(char *file);

char *get_file_buffer(char *file);


#if defined (UTILS_IMPLEMENTATION)

char *get_file_buffer(char *file){
		FILE *json_file = fopen(file, "r");

		if (!json_file) {
				return NULL;
		}

		int fd = fileno(json_file);
		struct stat file_stat;
		fstat(fd, &file_stat);

		char *buffer = (char *)malloc(file_stat.st_size*sizeof(char));
		fread(buffer, 1, file_stat.st_size * sizeof(char), json_file);

		return buffer;
}

cJSON *get_json_from_file(char *file){
		char *buffer = get_file_buffer(file);

		if (!buffer) {
				fprintf(stderr, "Something went wrong while opening the file.");
				return NULL;
		}

		cJSON *json = cJSON_Parse(buffer);

		if (!json){
				const char *error_ptr = cJSON_GetErrorPtr();
				if (error_ptr != NULL){
						printf("Error: %s\n", error_ptr);
				}
				cJSON_Delete(json);
				free(buffer);
				return NULL;
		}

		free(buffer);

		return json;
}

#endif
#endif
