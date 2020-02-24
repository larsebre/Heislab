/**
* @file
* @brief Functionality in conjunction with elevator panels
*/

#ifndef PANEL_H
#define PANEL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "hardware.h"
#include "State.h"


/**
* @brief Panel struct to contain information about buttons pushed on elevator panels
* @param[out] orders Two-dimensional array containing information about incoming orders
* @param[out] stop Boolean variable to indicate whether stop-button is pushed or not
* @param[out] obstruction Boolean variable to indicate whether obstruction-switch is active or not
*/
typedef struct{
	int orders[8];
	bool stop;
	bool obstruction;
}Panel;

/**
* @brief cleanOrders function to clear all orders
*/
void cleanOrders(int* orders);

/**
* @brief checkOrders function to check if order is already in array
*/
int checkOrders(int* orders, int floor);

/**
* @brief panelDefault function to initialize panel
*/
void panelDefault(Panel* p);

/**
* @brief left_shiftOrders function to shift orders to the left side
*/
void left_shiftOrders(int* orders);

/**
* @brief pushOrders function to push orders into orders array
*/
void pushOrders(Panel* p);

/**
* @brief delay function to add time-delay
*/
void delay(int number_of_seconds);

/**
* @brief maxValue function to return highest value in orders array
*/
int maxValue(Panel* p, State* s);

/**
* @brief minValue function to return lowest value in orders array
*/
int minValue(Panel* p, State* s);

/**
* @brief series_of_downs function to check if orders include a series of downward-orders
*/
bool series_of_downs(Panel* p);

/**
* @brief series_of_ups function to check if orders include a series of upward-orders
*/
bool series_of_ups(Panel* p);

/**
* @brief closest function to return next floor to go to
*/
int closestFloor(Panel* p, State* s);

/**
* @brief clearExecuted function to clear executed orders
*/
void clearExecuted(Panel* p, State* s);

/**
* @brief reached_Floor function to check if elevator has reached the correct floor
*/
void reached_Floor(Panel* p, State* s);

/**
* @brief check_if_orders function to check if there are orders in the orders array
*/
bool check_if_orders(Panel* p);

#endif
