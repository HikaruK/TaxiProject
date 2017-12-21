#include "Taxi.h"
#include "GuberClient.h"
#include <assert.h>
#include "Reader.h"
#include "Landmark.h"

/*Linked List functions*/
LandmarkList *MakeLandmarkList();
void DeleteLandmarkList(LandmarkList *list);

void AddLandmarkEntry(LandmarkList *list, char *name, int dropoff, int topLeft, int botRight);
Landmark *DeleteLandmarkEntry(LandmarkEntry *entry);

Landmark *MakeLandmark(char *name, int dropoff, int topLeft, int botRight);
void DeleteLandmark();
#
/*=========Linked list==========*/
LandmarkList *MakeLandmarkList()
{
 LandmarkList *list = malloc(sizeof(LandmarkList));
 if(!list)
 {
  exit(12);
 }
 
 list->first = NULL; 
 list->last = NULL;
 list->totalLandmarks = 0;
 return list;
}

void DeleteLandmarkList(LandmarkList *list)
{
 LandmarkEntry *entry, *next;
 Landmark *landmark;
 assert(list);
 entry = list->first;
 while(entry)
 { 
  next = entry->next;
  landmark = DeleteLandmarkEntry(entry);
  DeleteLandmark(landmark);
  entry = next;  
 }
 free(list);
}



/*=====*/

void AddLandmarkEntry(LandmarkList *list, char *name, int dropoff, int topLeft, int botRight)
{
 Landmark *landmark = MakeLandmark(name,dropoff,topLeft,botRight);
 LandmarkEntry *entry = malloc(sizeof(LandmarkEntry));
 if(!entry)
 {
  perror("out of memory");
  exit(11);
 }
 entry->list = list;
 entry->next = NULL;
 entry->landmark = landmark;
 list->totalLandmarks++;
 if(list->first == NULL)
 {
  list->first = entry;
  list->last = entry;
 }
 else
 {
  list->last->next = entry;
  list->last = list->last->next;
 }
}

Landmark *DeleteLandmarkEntry(LandmarkEntry *entry)
{
 Landmark *landmark;
 assert(entry);
 landmark = entry->landmark;
 free(entry);
 return landmark;
}

/*=====*/
Landmark *MakeLandmark(char *name, int dropoff, int topLeft, int botRight)
{
 Landmark *landmark = malloc(sizeof(struct Landmark));
 if(!landmark)
 {
  perror("out of memory");
  exit(10);
 }
 landmark->name = name;
 landmark->dropoff = dropoff;
 landmark->topLeft = topLeft;
 landmark->botRight = botRight;
 return landmark;
}

void DeleteLandmark(Landmark *landmark)
{
 assert(landmark);
 free(landmark);
}



