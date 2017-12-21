#include "Route.h"

int *CreateRoute(Map map, int src, int dest) {
	int x, y, i, bad, start_x, start_y, end_x, end_y, temp_length, last_pos, up, down, left, right;
	start_x = src % map.x;
	start_y = src / map.x;
	end_x = dest % map.x;
	end_y = dest / map.x;
	int *path = (int *)malloc(sizeof(int)*100);

	last_pos = -1;
	temp_length = 0;
 	x = start_x;
	y = start_y;
	
	while((x != end_x || y != end_y)){
		if(map.x*y + x == last_pos) {
			printf("\nit breaks here\n");
			break;
		}
		last_pos = map.x*y + x;
		if(x != end_x){
			bad = 0;
			if(x+1 <= end_x && map.arr[map.x*y + x + 1] != 'L') {
				if(y < end_y) {
					for (i = y; i < end_y; i++) {
						if(map.arr[map.x*i + end_x] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(y > end_y) {
					for (i = y; i > end_y; i--) {
						if(map.arr[map.x*i + end_x] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(!bad) {
					path[temp_length++] = map.x*y + ++x;
					printf("x: %d y: %d\n", x, y);
				}
			}
			if(x-1 >= end_x && map.arr[map.x*y + x -1] != 'L') {
				if(y < end_y) {
					for (i = y; i < end_y; i++) {
						if(map.arr[map.x*i + end_x] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(y > end_y) {
					for (i = y; i > end_y; i--) {
						if(map.arr[map.x*i + end_x] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(!bad) {
					path[temp_length++] = map.x*y + --x;
					printf("x: %d y: %d\n", x, y);
				}
			}
		}
		if(y != end_y){
			bad = 0;
			if(y+1 <= end_y && map.arr[map.x*(y+1) + x] != 'L') {
				if(x < end_x) {
					for (i = x; i < end_x; i++) {
						if(map.arr[map.x*(end_y) + i] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(x > end_x) {
					for (i = x; i > end_x; i--) {
						if(map.arr[map.x*(end_y) + i] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(!bad) {
					path[temp_length++] = map.x*++y + x;
					printf("x: %d y: %d\n", x, y);
				}
			}
			if(y-1 >= end_y && map.arr[map.x*(y-1) + x] != 'L') {
				if(x < end_x) {
					for (i = x; i < end_x; i++) {
						if(map.arr[map.x*(end_y) + i] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(x > end_x) {
					for (i = x; i > end_x; i--) {
						if(map.arr[map.x*(end_y) + i] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(!bad) {
					printf("x: %d y: %d\n", x, y);
					path[temp_length++] = map.x*--y + x;
				}
			}
		}
		if(map.x*y + x == last_pos) {
			printf("landmark blocking\n");
			up = down = left = right = 0;
			if(y == end_y && map.arr[map.x*y + (x-1)] == 'L') {
				printf("landmark to left\n");
				while(y < map.y && map.arr[map.x*(y+1) + (x-1)] == 'L') {
					y++;
					down++;
				}
				if (y + 1 == map.y && map.arr[map.x*y + (x-1)] == 'L') {
					down = 2 * map.y;
				}
				printf("down: %d\n", down);
				y = y - down;
				while(y > - 1 && map.arr[map.x*(y-1) + (x-1)] == 'L') {
					y--;
					up++;
				}
				if (y == 0 && map.arr[map.x*y + (x-1)] == 'L') {
					up = 2 * map.y;
				}
				printf("up: %d\n", up);
				y = y + up;
				if(up < down) {
					printf("going up\n");
					for (i = 0; i <= up; i++) {
						printf("x: %d y: %d\n", x, y);
						path[temp_length++] = map.x*--y + x;
					}
				}
				else {
					printf("going down\n");
					for (i = 0; i <= down; i++) {
						path[temp_length++] = map.x*++y + x;
						printf("x: %d y: %d\n", x, y);
					}
				}
			}
			if(y == end_y && x + 1 < map.x && map.arr[map.x*y + (x+1)] == 'L') {
				printf("landmark to right\n");
				while(y < map.y && map.arr[map.x*(y+1) + (x+1)] == 'L') {
					y++;
					down++;
				}
				if (y + 1 == map.y && map.arr[map.x*y + (x+1)] == 'L') {
					down = 2 * map.y;
				}
				printf("down: %d\n", down);
				y = y - down;
				while(y > - 1 && map.arr[map.x*(y-1) + (x+1)] == 'L') {
					y--;
					up++;
				}
				if (y == 0 && map.arr[map.x*y + (x+1)] == 'L') {
					up = 2 * map.y;
				}
				printf("up: %d\n", up);
				y = y + up;
				if(up < down) {
					printf("going up\n");
					for (i = 0; i <= up; i++) {
						printf("x: %d y: %d\n", x, y);
						path[temp_length++] = map.x*--y + x;
					}
				}
				else {
					printf("going down\n");
					for (i = 0; i <= down; i++) {
						path[temp_length++] = map.x*++y + x;
						printf("x: %d y: %d\n", x, y);
					}
				}
			}
			if(x == end_x && y > 0 && map.arr[map.x*(y-1) + x] == 'L') {
				printf("landmark above\n");
				while(x < map.x && map.arr[map.x*(y-1) + (x+1)] == 'L') {
					x++;
					right++;
				}
				if (x + 1 == map.x && map.arr[map.x*(y-1) + x] == 'L') {
					right = 2 * map.x;
				}
				printf("right: %d\n", right);
				x = x - right;
				while(x > - 1 && map.arr[map.x*(y-1) + (x-1)] == 'L') {
					x--;
					left++;
				}
				if (x == 0 && map.arr[map.x*(y-1) + x] == 'L') {
					left = 2 * map.x;
				}
				printf("left: %d\n", left);
				x = x + left;
				if(left < right) {
					printf("going left\n");
					for (i = 0; i <= left; i++) {
						path[temp_length++] = map.x*y + --x;
						printf("x: %d y: %d\n", x, y);
					}
				}
				else {
					printf("going right\n");
					for (i = 0; i <= right; i++) {
						path[temp_length++] = map.x*y + ++x;
						printf("x: %d y: %d\n", x, y);
					}
				}
			}
			if(x == end_x && y + 1 < map.y && map.arr[map.x*(y+1) + x] == 'L') {
				printf("landmark below\n");
				while(x < map.x && map.arr[map.x*(y+1) + (x+1)] == 'L') {
					x++;
					right++;
				}
				if (x + 1 == map.x && map.arr[map.x*(y+1) + x] == 'L') {
					right = 2 * map.x;
				}
				printf("right: %d\n", right);
				x = x - right;
				while(x > - 1 && map.arr[map.x*(y+1) + (x-1)] == 'L') {
					x--;
					left++;
				}
				if (x == 0 && map.arr[map.x*(y+1) + x] == 'L') {
					left = 2 * map.x;
				}
				printf("left: %d\n", left);
				x = x + left;
				if(left < right) {
					printf("going left\n");
					for (i = 0; i <= left; i++) {
						path[temp_length++] = map.x*y + --x;
						printf("x: %d y: %d\n", x, y);
					}
				}
				else {
					printf("going right\n");
					for (i = 0; i <= right; i++) {
						path[temp_length++] = map.x*y + ++x;
						printf("x: %d y: %d\n", x, y);
					}
				}
			}
		}
	}
	return path;
}









