/**
* @file
* @brief Struct and functionality to handle state of elevator
*/

#ifndef MOTOR_H
#define MOTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "hardware.h"
#include "State.h"
#include "Panel.h"

/**
* @brief elevatorDrive main function for driving the elevator
*/
void elevatorDrive(Panel* p, State* s);

#endif
