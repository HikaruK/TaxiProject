#include "Reader.h"
#include "Taxi.h"


int main() {
	
	Map map;
	TaxiStandList *list = MakeTaxiStandList();
	map = Reader(map, list);
	
	int totalTaxis = list->totalTaxis; 
	Taxi *taxis = malloc(totalTaxis*sizeof(Taxi));
	Taxi *fleet = MakeTaxiFleet(map.list, taxis);

	printf("TEST %d\n", fleet[11].location);
	int i, j, cmp;; 
	for(i = 0; i < list->totalTaxis;i++)
	{
	printf("%d, %d\n", fleet[i].location, fleet[i].taxiID);
	}
	printf("   ");
	for(i = 0; i < map.x; i++){
		printf("%d ", i % 10);
	}
	printf("\n");
	for(i = 0; i < map.y; i++){
		if (i < 10) {
			printf(" %d ", i);
		}
		else {
			printf("%d ", i);
		}
		for(j = 0; j < map.x; j++){
			printf("%c ",map.arr[i*map.x + j]);
		}
		printf("\n");
	}
	printf("\nX names:\n%s\n\n", map.x_names);
	printf("Y names:\n%s\n\n", map.y_names);
	printf("Landmarks: \n%s\n\n", map.l_names);
	printf("Landmark indexes:");
	for (i = 0; i < 5; i++) {
		printf("%d ", map.l_index[i]);
	}
	printf("\n\n");
	
	for (i = 0; i < 5; i++) {
		printf("top left: %d ", map.top_left[i]);
		printf("bot right: %d ", map.bot_right[i]);
		printf("\n");
	}
	printf("\n\n");
	
	if(map.x == 42)
		printf("X axis length loaded successfully\n");
	else 
		printf("X axis length is not correct\n");
	
	if(map.y == 26)
		printf("Y axis length loaded successfully\n");
	else 
		printf("Y axis length is not correct\n");
	
	cmp = strcmp(map.x_names, "1st Street, 2nd Street, 3rd Street, 4th Street, 5th Street, 6th Street, 7th Street, 8th Street, 9th Street, 10th Street, 11th Street, 12th Street, 13th Street, 14th Street, 15th Street, 16th Street, 17th Street, 18th Street, 19th Street, 20th Street, 21st Street, 22nd Street, 23rd Street, 24th Street, 25th Street, 26th Street, 27th Street, 28th Street, 29th Street, 30th Street, 31st Street, 32nd Street, 33rd Street, 34th Street, 35th Street, 36th Street, 37th Street, 38th Street, 39th Street, 40th Street, 41st Street, 42nd Street,");
	if(cmp == 0)
		printf("X names loaded successfully\n");
	else 
		printf("X names are not correct\n");	
	
	cmp = strcmp(map.y_names, "Antbeater Road, Barracuda Pkwy, Cauliflower Ave, Doc Arthur Blvd, East Main Street, Four Or Five Hours Freeway, Gymboree Road, Hazard Ave, Irvine Classic Drive, Jerkly Ave, Karmans Van Ave, Lawnut Ave, Michelangelo Drive, New Irvine Blvd, Orange Hill Road, Pale Loop, Quail Mill Pkwy, Rectangular Adobe Road, Stand Fourth, Talton Pkwy, University Circle, Verde Palo Road, West Campus Drive, X Roads, Yoming Ave, Z End,");
	if(cmp == 0)
		printf("Y names loaded successfully\n");
	else 
		printf("Y names are not correct\n");

	cmp = strcmp(map.arr, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX<XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXLLLLLLLLLLLXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXLLLLLLLLLLLXXXXLLLLLLLXXXXXXXXXXXXXXXXXXXXLLLLLLLLLLLXXXXLLLLLLLXXXXXXXXXXXXXXXXXXXXLLLLLLLLLLLXXXXLLLLLLLXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXLLLLLLLXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXLLLLLLLXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXLLLLLLLXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXLLLLLLLXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXLLLLLLLXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXLLLLLLLXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXLLLLLLLXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXLLLLLLLXXXXXXXXXXXXXXXXLLLLLLLLLLXXXXXXXXXLLLLLLLXXXXXXXXXXXXXXXXLLLLLLLLLLXXXXXXXXXLLLLLLLXXXXXXXXXXXXXXX<LLLLLLLLLLXXXXXXXXXLLLLLLLXXXXXXXXXXXXXXXXLLLLLLLLLLXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXLLLLLLLLLLXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXLLLLLLLLLLXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX<XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	if(cmp == 0)
		printf("Array loaded successfully\n");
	else 
		printf("Array loaded unsuccessfully\n");

	return 0;
}