/**
* @file
* @brief Struct and functionality to handle state of elevator
*/

#include "Motor.h"

void elevatorDrive(Panel* p, State* s){
    
    if (check_if_orders(p) == true){
    	
    	int nextFloor = closestFloor(p, s);
    	
    	if (s->reachedFloor == 1){
    		clearExecuted(p, s);
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
           	s->reachedFloor = 0;
           	hardware_command_door_open(1);
           	delay(3);
           	hardware_command_door_open(0);
    	}
    	
    	if(s->reachedFloor == 0){
            if((nextFloor - s->betweenFloors[0]) > 0){
            	hardware_command_movement(HARDWARE_MOVEMENT_UP);
            	s->Direction = 1;
            }
            if((nextFloor - s->betweenFloors[0]) < 0){
            	hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            	s->Direction = -1;
            }
   		}
    }else{
    	hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    }  
}
