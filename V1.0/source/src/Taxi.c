#include "Taxi.h"
#include "GuberClient.h"
#include <assert.h>

/*Linked List functions*/
TaxiStandList *MakeTaxiStandList();
void DeleteTaxiStandList(TaxiStandList *list);

void AddTaxiStandEntry(TaxiStandList *list, int num, int location);
TaxiStand *DeleteTaxiStandEntry(TaxiStandEntry *entry);

TaxiStand *MakeTaxiStand(int location, int num); 
void DeleteTaxiStand();

/*taxi fleet*/
Taxi *MakeTaxiFleet(TaxiStandList *list, Taxi *fleet);
void DeleteTaxiFleet(Taxi *taxiFleet);
void UpdateTaxi(Taxi *taxi,int totalTaxis;);

/*Setter functions*/
void SetLocation(Taxi *fleet, int index, int location);
void SetPickup(Taxi *fleet, int index, int pickup);
void SetDestination(Taxi *fleet, int index, int destination); 


/*=========Linked list==========*/
TaxiStandList *MakeTaxiStandList()
{
 TaxiStandList *list = malloc(sizeof(TaxiStandList));
 if(!list)
 {
  exit(12);
 }
 
 list->first = NULL; 
 list->last = NULL;
 list->totalTaxis = 0;
 list->totalStands = 0; 
 return list;
}
void DeleteTaxiStandList(TaxiStandList *list)
{
 TaxiStandEntry *entry, *next;
 TaxiStand *stand;
 assert(list);
 entry = list->first;
 while(entry)
 { 
  next = entry->next;
  stand = DeleteTaxiStandEntry(entry);
  DeleteTaxiStand(stand);
  entry = next;  
 }
 free(list);
}

/*=====*/

void AddTaxiStandEntry(TaxiStandList *list, int num, int location)
{
 TaxiStand *stand = MakeTaxiStand(location, num);
 TaxiStandEntry *entry = malloc(sizeof(TaxiStandEntry));
 if(!entry)
 {
  perror("out of memory");
  exit(11);
 }
 entry->list = list;
 entry->next = NULL;
 entry->stand = stand;
 list->totalStands++;
 if(list->first == NULL)
 {
  list->first = entry;
  list->last = entry; 
  list->totalTaxis = list->totalTaxis + num; 
 }
 else
 {
  list->last->next = entry;
  list->last = list->last->next;
  list->totalTaxis += num;
 }
}

TaxiStand *DeleteTaxiStandEntry(TaxiStandEntry *entry)
{
 TaxiStand *stand;
 assert(entry);
 stand = entry->stand;
 free(entry);
 return stand;
}

/*=====*/

TaxiStand *MakeTaxiStand(int location, int num)
{
 TaxiStand *stand = malloc(sizeof(struct TaxiStand));
 if(!stand)
 {
  perror("out of memory");
  exit(10);
 }
 stand->location = location;
 stand->numTaxis = num;	
 return stand;
}

void DeleteTaxiStand(TaxiStand *stand)
{
 assert(stand);
 free(stand);
}

/*=====*/

Taxi *MakeTaxiFleet(TaxiStandList *list, Taxi *fleet)
{
int i;
int taxiID = 1; 
int numTaxis = list->totalTaxis; 
TaxiStandEntry *temp = list->first;
int counter = 0; 
for(i = 0; i < numTaxis; i++)
{
 if((counter >= temp -> stand->numTaxis) && (temp->next != NULL))
 {
  counter = 0; 
  temp = temp->next;
 }
 fleet[i].location = temp->stand->location;
 printf("make taxi location: %d\n", fleet[i].location);
 fleet[i].passenger = 0; 
 fleet[i].taxiID = taxiID;
 taxiID++; 
 counter++;
}
return fleet;
}

void DeleteTaxiFleet(Taxi *taxiFleet)
{
 free(taxiFleet);
}

/*=====Setter functions=====*/

void SetLocation(Taxi *fleet, int index, int location)
{
 fleet[index].location = location;
}
void SetPickup(Taxi *fleet, int index, int pickup)
{
 fleet[index].pickup = pickup;
}
void SetDestination(Taxi *fleet, int index, int destination) 
{
 fleet[index].destination = destination;
}
/*=====Routing functions=====*/

void UpdateTaxi(Taxi *fleet, int totalTaxis)
{
 int i;
 printf("\n updatetaxi \n ");
 for(i = 0; i < totalTaxis; i++)
 {
	if(fleet[i].location == fleet[i].destination) {
		/* go back to taxi stand or if at taxi stand chill set route/route_index to 0 etc */
	}
	else {
		fleet[i].location == fleet[i].route[fleet[i].route_index++];
	}
  printf("%d", fleet[i].taxiID);
 }
 printf("\n updatetaxi");

} 
