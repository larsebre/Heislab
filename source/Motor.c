/**
* @file
* @brief Struct and functionality to handle state of elevator
*/

#include "Motor.h"

void elevatorDrive(Panel* p, State* s){

	while (hardware_read_stop_signal()){
		hardware_command_movement(HARDWARE_MOVEMENT_STOP);
		hardware_command_stop_light(1);
		cleanOrders(p->orders);
		s->justPressedStop = true;
	}
	hardware_command_stop_light(0);
    
    if (check_if_orders(p) == true){
    	
    	int nextFloor = closestFloor(p, s);

		/*if (s->justPressedStop){
			if ((double)nextFloor > ((s->betweenFloors[0] + s->betweenFloors[1])/2)){
				s->betweenFloors[0] = s->betweenFloors[1];
				s->Direction = 1;
				hardware_command_movement(HARDWARE_MOVEMENT_UP);
			}
			if ((double)nextFloor < ((s->betweenFloors[0] + s->betweenFloors[1])/2)){
				s->betweenFloors[1] = s->betweenFloors[0];
				s->Direction = -1;
				hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
				
			}
			s->justPressedStop = false;
		}*/
    	
    	if (s->reachedFloor == true){
    		clearExecuted(p, s);
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
           	s->reachedFloor = false;
           	hardware_command_door_open(1);
           	delay(p,3);
           	hardware_command_door_open(0);
    	}
    	
    	if(s->reachedFloor == false){

            if((nextFloor - s->betweenFloors[0]) >= 0){
            	hardware_command_movement(HARDWARE_MOVEMENT_UP);
            	s->Direction = 1;
            }
            if((nextFloor - s->betweenFloors[0]) <= 0){
            	hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            	s->Direction = -1;
            }
			
   		}
    }else{
    	hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    }  
}
