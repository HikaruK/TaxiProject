#ifndef TAXI_H_INCLUDED_
#define TAXI_H_INCLUDED_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "GuberServer.h"


typedef struct TaxiStandList
{
 struct TaxiStandEntry *first;
 struct TaxiStandEntry *last;
 int totalTaxis;
 int totalStands;
}TaxiStandList;

typedef struct TaxiStandEntry
{
 struct TaxiStandList *list;
 struct TaxiStandEntry *next;
 struct TaxiStand *stand;
}TaxiStandEntry;

typedef struct Taxi
{
 int passenger;
 int rideLength;
 double fare;
 double expense; 
 int type; 
 int taxiID;
 int location; 
 int pickup; 
 int destination;
 int route_index;
 int *route; 
 double lastUpdate;
}Taxi;

typedef struct TaxiStand
{
 int location;
 int numTaxis;
}TaxiStand;

/*Linked List functions*/
TaxiStandList *MakeTaxiStandList();
void DeleteTaxiStandList(TaxiStandList *list);

void AddTaxiStandEntry(TaxiStandList *list, int location, int num);
TaxiStand *DeleteTaxiStandEntry(TaxiStandEntry *entry);

TaxiStand *MakeTaxiStand(int location, int num); 
void DeleteTaxiStand();

/*taxi fleet*/
Taxi *MakeTaxiFleet(TaxiStandList *list, Taxi *fleet);
void DeleteTaxiFleet(Taxi *taxiFleet);
void UpdateTaxi(Taxi *fleet, int totalTaxis);

/*Setter functions*/
void SetLocation(Taxi *fleet, int index, int location);
void SetPickup(Taxi *fleet, int index, int pickup);
void SetDestination(Taxi *fleet, int index, int destination); 

#endif /* TAXI_H_INCLUDED_ */
