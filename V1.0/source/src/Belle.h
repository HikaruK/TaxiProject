#ifndef READER_H_INCLUDED_
#define READER_H_INCLUDED_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*Desmond Chan
 * #include "Guber.h"
 * #include "Reader.h"
 * #include "Taxi.h"*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

int searchword(char *text, char *word);

char *Belle(char *string);

char* FullStreetName( char* a);
#endif
