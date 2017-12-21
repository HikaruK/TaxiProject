#ifndef READER_H_INCLUDED_
#define READER_H_INCLUDED_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Taxi.h"

typedef struct map_obj
{  
char *x_names, *y_names, *l_names, *arr;
int x, y;
struct TaxiStandList *list;
int *l_index, *top_left, *bot_right;
} Map;

Map Reader(Map map, struct TaxiStandList *list);

#endif /* READER_H_INCLUDED_ */
