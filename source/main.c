#include <stdio.h>
#include <stdlib.h>
#include "Panel.h"
#include "State.h"
#include "Motor.h"


int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    
	Panel p;
	Panel* p_panel = &p;
	panelDefault(p_panel);
	
	State s;
	State* p_state = &s;
	stateDefault(p_state);
	
	while(1){
	
  		int nextFloor = closestFloor(p_panel, p_state);
  		
  		for (unsigned int i = 0; i<=7; i++){
  			printf("%d", p_panel->orders[i]);
  		}
  		printf("\t");
  		printf("%d", p_state->Direction);
		
		printf("\t");
  		printf("%d", p_state->betweenFloors[0]);
		
  		printf("\t");
  		printf("%d", nextFloor);
		printf("\n");
		
		floorReached(p_panel, p_state);
		pushOrders(p_panel);
		setOrderLights(p_panel);
		stateControl(p_state);
		elevatorDrive(p_panel, p_state);
       	
		if(hardware_read_stop_signal()&&hardware_read_obstruction_signal()){
       		hardware_command_movement(HARDWARE_MOVEMENT_STOP);
       		break;
       	}
       	
       	p_state->prevFloor = p_state->betweenFloors[0];
    }

    return 0;
}
