#include "Route.h"

int main() {
	Map map;
	map = Reader(map);
	/* (0, 0), (10, 0), (10, 0), (20, 0), (20, 0), (35, 14), (26, 14), (28, 20), (28, 3) */
	int src_arr[9] = {0, 10, 10, 20, 20, 623, 614, 868, 154};
	/* (2, 19), (13, 14), (24, 16), (2, 19), (23, 21), (26, 14), (35, 14), (28, 3), (28, 20) */
	int dest_arr[9] = {800, 601, 696, 800, 905, 614, 623, 154, 868};
	int optimal_length[9] = { 21, 17, 30, 37, 24, 19, 19, 21, 21};
	int i, j, k, a, b, start_x, start_y, end_x, end_y;
	double fare;
	
	int *path;
	for(i = 0; i < 9; i++) {
		start_x = src_arr[i] % map.x;
		start_y = src_arr[i] / map.x;
		end_x = dest_arr[i] % map.x;
		end_y = dest_arr[i] / map.x;
		path = CreateRoute(map, src_arr[i], dest_arr[i]);
		for ( j = 0; j < 100; j++) {
			printf( "%d ", path[j]);
			if(path[j] == dest_arr[i]) {
				fare = 4.25 + .5 * j;
				printf("\nfare is: %.2f", fare);
				printf("\nl expect: %d l actual: %d\n", optimal_length[i], j+1);
				printf("x expect: %d x actual: %d\n", end_x, path[j] % map.x);
				printf("y expect: %d y actual: %d\n\n", end_y, path[j] / map.x);
				for(k = 0; k <= j; k++) {
					map.arr[path[k]] = '.';
				}
				for(a = 0; a < map.y; a++){
					for(b = 0; b < map.x; b++){
						printf("%c", map.arr[a*map.x + b]);
					}
					printf("\n");
				}
				map = Reader(map);
				break;
			}
		}
	}
	
	return 0;
}