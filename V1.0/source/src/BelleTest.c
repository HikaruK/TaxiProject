#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include "Route.h"
#include "Reader.h"
#include "Taxi.h"

int main() {
	Map map;
	TaxiStandList *list = MakeTaxiStandList();
	map = Reader(map, list);
	int i, j, src_index, dest_index;;
	char *finder = NULL, *line = NULL, *line2 = NULL, *dest = NULL;
	char client_input[100];
	char client_temp[100];
	char src[100];
	char *x_temp = (char *)malloc(sizeof(char)*map.x*80);
	char *x_temp2 = (char *)malloc(sizeof(char)*map.x*80);
	char *y_temp = (char *)malloc(sizeof(char)*map.y*80);
	char *y_temp2 = (char *)malloc(sizeof(char)*map.y*80);
	
	memcpy(x_temp, map.x_names, strlen(map.x_names)+1);
	memcpy(x_temp2, map.x_names, strlen(map.x_names)+1);
	memcpy(y_temp, map.y_names, strlen(map.y_names)+1);
	memcpy(y_temp2, map.y_names, strlen(map.y_names)+1);
	
	printf("\nEnter Command : ");
	fgets(client_input, 100, stdin);	
	memcpy(client_temp, client_input, 100);
	line = strtok(client_temp, " ");
	printf("line: %s\n", line);
	int max = 0;
	while (strcmp(line, "TO")) {
		max += strlen(line) + 1;
		line = strtok(NULL, " ");
	}
	
	memcpy(src, client_input, max);
	finder = strstr(client_input, "REQUEST_TAXI");
	if(finder){
		finder = strstr(client_input, "CORNER");
		if(finder){
			line = strtok(x_temp, ",");
			for(i = 0; i < map.x; i++){
				line2 = strstr(src, line);
				if(line2) {
					line = strtok(y_temp, ",");
					for(j = 0; j < map.y; j++){
						line2 = strstr(src, line);
						if(line2) {
							printf("\nfirst set found\n");
							src_index = map.x*j + i;
							i = map.x;
							break;
						}
						line = strtok(NULL, ",");
					}
				}
				if (i < map.x) {
					line = strtok(NULL, ",");
				}
			}
			dest = strstr(client_input, "TO");
			line = strtok(x_temp2, ",");
			for(i = 0; i < map.x; i++){
				line2 = strstr(dest, line);
				if(line2) {
					line = strtok(y_temp2, ",");
					for(j = 0; j < map.y; j++){
						line2 = strstr(dest, line);
						if(line2) {
							printf("\n2nd set found\n");
							dest_index = map.x*j + i;
							i = map.x;
							break;
						}
						line = strtok(NULL, ",");
					}
				}
				if (i < map.x) {
					line = strtok(NULL, ",");
				}
			}
		}
	}
	printf("src index: %d dest index: %d\n", src_index, dest_index);
	return 0;
}



