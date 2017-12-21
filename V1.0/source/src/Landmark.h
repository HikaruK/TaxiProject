#ifndef LANDMARK_H_INCLLUDED
#define LANDMARK_H_INCLUDED
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Reader.h"
	
typedef struct LandmarkList
{
 struct LandmarkEntry *first;
 struct LandmarkEntry *last;
 int totalLandmarks;
}LandmarkList;

typedef struct LandmarkEntry
{
 struct LandmarkList *list;
 struct LandmarkEntry *next;
 struct Landmark *landmark;
}LandmarkEntry;

typedef struct Landmark
{
 char *name;
 int dropoff;
 int topLeft;
 int botRight;
}Landmark;

/*Linked List functions*/
LandmarkList *MakeLandmarkList();
void DeleteLandmarkList(LandmarkList *list);

void AddLandmarkEntry(LandmarkList *list, char *name, int dropoff, int topLeft, int botRight);
Landmark *DeleteLandmarkEntry(LandmarkEntry *entry);

Landmark *MakeLandmark(char *name, int dropoff, int topLeft, int botRight);
void DeleteLandmark();
#endif
/*taxi fleet
Taxi *MakeTaxiFleet(TaxiStandList *list, Taxi *fleet);
void DeleteTaxiFleet(Taxi *taxiFleet);
void UpdateTaxi();
*/
