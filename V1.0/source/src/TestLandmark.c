#include <stdio.h>
#include <stdlib.h>
#include "Landmark.h"
#include "Reader.h"

int main()
{

 /*===========linked list test==========*/
 printf("\n=====Linked List Test=====\n");
 LandmarkList *list = MakeLandmarkList(); 
 AddLandmarkEntry(list, "library", 5, 4, 3);
 AddLandmarkEntry(list, "cafe", 4, 2, 1);
 
 printf("dropoff location:%d\n", list->first->next->landmark->dropoff);
 printf("topLeft location:%d\n", list->first->next->landmark->topLeft);
 printf("botRight location:%d\n", list->first->next->landmark->botRight);

 AddLandmarkEntry(list, "Hikaru", 4, 2, 1); 
 printf("last entry name: %s\n", list->last->landmark->name);


 DeleteLandmarkList(list); 
 return 0;  
/*==========linked list test==========*/

 }
