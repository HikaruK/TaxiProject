#ifndef ROUTE_H_INCLUDED_
#define ROUTE_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Reader.h"

int *CreateRoute(Map map, int src, int dest);

#endif /* ROUTE_H_INCLUDED_ */
