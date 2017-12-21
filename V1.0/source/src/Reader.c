#include "Reader.h"

Map Reader(Map map, TaxiStandList *list){
	FILE *stream = fopen("NewIrvine.map", "r");
	if(stream == NULL){
		exit(EXIT_FAILURE);
	}
	size_t len = 0;
	ssize_t read;
	int x = 0, y = 0;
	char *finder = NULL, *line = NULL, *line2 = NULL;
	int i, j, xstart, xend, ystart, yend, sum, str_len;
	int l_num = 0;
	map.l_names = (char *)malloc(sizeof(char)*5*80);
	map.l_index = (int *)malloc(sizeof(int)*5);
	map.top_left = (int *)malloc(sizeof(int)*5);
	map.bot_right = (int *)malloc(sizeof(int)*5);
	strcpy(map.l_names, "");
 while((read = getline(&line, &len, stream)) != -1){
	xstart = xend = ystart = yend = sum = 0;
	finder = strstr(line, "GRID");
	if(finder)
	{
		line2 = strtok(line, " ");
		line2 = strtok(NULL, " ");
		str_len = strlen(line2);
		for(i=0; i<str_len; i++){
			y = y * 10 + ( line2[i] - '0' );
		}
		map.y = y;
		line2 = strtok(NULL, " ");
		str_len = strlen(line2);
		for(i=0; i<str_len-1; i++){
			x = x * 10 + ( line2[i] - '0' );
		}
		map.x = x;
		map.x_names = (char *)malloc(sizeof(char)*map.x*80);
		map.y_names = (char *)malloc(sizeof(char)*map.y*80);
		map.arr = (char *)malloc(sizeof(char)*map.x*map.y);
		for(i = 0; i < map.y; i++){
			for(j = 0; j < map.x; j++){
				map.arr[i*x + j] = 'X';
			}
		}
	}
 
 	finder = strstr(line, "STREET_NAMES_EAST_WEST");
	if(finder){
		line2 = strtok(line, " ");
		line2 = strtok(NULL, ",");
		strcpy(map.y_names, line2);
		strcat(map.y_names, ",");
		int i = map.y;
		while(i > 1) {
			line2 = strtok(NULL, ",\n");
			strcat(map.y_names, line2);
			strcat(map.y_names, ",");
			i--;	
		}
	}

	finder = strstr(line, "STREET_NAMES_NORTH_SOUTH");
	if(finder){
		line2 = strtok(line, " ");
		line2 = strtok(NULL, ",");
		strcpy(map.x_names, line2);
		strcat(map.x_names, ",");
		int i = map.x;
		while(i > 1) {
			line2 = strtok(NULL, ",\n");
			strcat(map.x_names, line2);
			strcat(map.x_names, ",");
			i--;	
		}
	}
	
	finder = strstr(line, "LANDMARK");
	if(finder){
		finder = strstr(line, "(");
		if(finder){
			line2 = strtok(line, " ");
			
			
			line2 = strtok(NULL, "(");
			i = 0;
			ystart = line2[i++] - 'A';
			while(line2[i] >= '0' && line2[i] <= '9'){
				xstart = xstart * 10 + ( line2[i] - '0' );
				i++;
			}
			map.l_index[l_num++] = map.x*ystart + xstart - 1;
			ystart = yend = xstart = xend = 0;
			line2 = strtok(NULL, " ");
			i = 0;
			ystart = line2[i++] - 'A';
			while(line2[i] >= '0' && line2[i] <= '9'){
				xstart = xstart * 10 + ( line2[i] - '0' );
				i++;
			}
			yend = line2[++i] - 'A';
			i++;
			while(line2[i] >= '0' && line2[i] <= '9'){
				xend = xend * 10 + ( line2[i] - '0' );
				i++;
			}
			for(j = ystart; j < yend + 1; j++){
				for(i = xstart - 1; i < xend; i++){
					map.arr[j*map.x + i] = 'L';
				}
			}
			map.top_left[l_num-1] = map.x*ystart + xstart -1;
			map.bot_right[l_num-1] = map.x*yend + xend - 1;
			line2 = strtok(NULL, "\n");
			strcat(map.l_names, line2);
			strcat(map.l_names, ", ");
		}
		else {
			line2 = strtok(line, " ");
			line2 = strtok(NULL, " ");
			i = 0;
			ystart = line2[i++] - 'A';
			while(line2[i] >= '0' && line2[i] <= '9'){
				xstart = xstart * 10 + ( line2[i] - '0' );
				i++;
			}
			map.l_index[l_num++] = map.x*ystart + xstart - 1;
			line2 = strtok(NULL, "\n");
			strcat(map.l_names, line2);
			strcat(map.l_names, ",");
		}
	}
	finder = strstr(line, "TAXI_STAND");
	if(finder){
		line2 = strtok(line, " ");
		line2 = strtok(NULL, " ");
		ystart = line2[0] - 'A';
		i = 1;
		while(line2[i] >= '0' && line2[i] <= '9'){
				xstart = xstart * 10 + ( line2[i] - '0' );
				i++;
		}
		i++;
		while(line2[i] >= '0' && line2[i] <= '9'){
				sum = sum * 10 + ( line2[i] - '0' );
				i++;
		}
		AddTaxiStandEntry(list, sum, map.x*ystart + xstart-1);
		map.arr[ystart*map.x + xstart-1] = sum + 48;
	}
	
  finder = NULL;
	}
 fclose(stream);
 map.list = list;
 return map;
}
