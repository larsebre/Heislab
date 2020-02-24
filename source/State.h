/**
* @file
* @brief Struct and functionality to handle state of elevator
*/

#ifndef STATE_H
#define STATE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "hardware.h"



/**
* @brief cleanOrders function to clear all orders
*/
typedef struct{
	int prevFloor;
    int currentFloor;                               // -1 if between floors
    int betweenFloors[2];
    int Direction;
    int prevDirection;
    int reachedFloor;
}State;

/**
* @brief cleanOrders function to clear all orders
*/
//Only use for configuration outside the while-loop
void stateDefault(State* Elevator);

/**
* @brief cleanOrders function to clear all orders
*/
int checkState();

/**
* @brief cleanOrders function to clear all orders
*/
int getFloor(int check);

/**
* @brief cleanOrders function to clear all orders
*/
void stateControl(State* Elevator);


#endif
