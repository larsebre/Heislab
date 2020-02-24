/**
* @file
* @brief Implementation of Panel.h
*/

#include "Panel.h"

void cleanOrders(int* orders){

	for (int i=0; i<8; i++){
		orders[i] = -1;
	}
}

void panelDefault(Panel* p){

	cleanOrders(p->orders);
	p->stop = false;
	p->obstruction = false;
}

int checkOrders(int* orders, int floor){

	for(int i=0; i<=3; i++){
		if(orders[i] == floor){
		return i;
		}	
	}
	return -1;												//-1 shows that the order is executed
}

void left_shiftOrders(int* orders){		

	for (unsigned int i = 0; i <= 2; i++){
		if (orders[i] == -1){			
			for (unsigned int j = i; j <= 2; j++){
				orders[j] = orders[j+1];
				orders[j+4] = orders[j+1+4];
			
			}
			break;
		}
	}
}

void pushOrders(Panel* p){

	for(unsigned int i=0; i<=3; i++){
		bool check = (hardware_read_order(i, HARDWARE_ORDER_UP) || hardware_read_order(i, HARDWARE_ORDER_INSIDE) || hardware_read_order(i, HARDWARE_ORDER_DOWN));
		if (check){
			if (hardware_read_order(i, HARDWARE_ORDER_UP)){
				 if (checkOrders(p->orders, i)<0){
					hardware_command_order_light(i, HARDWARE_ORDER_UP, 1);
				 	left_shiftOrders(p->orders);
					p->orders[3] = i;
					if (i == 0){
						p->orders[3+4] = -1;	
					}else{
						p->orders[3+4] = 1;
					}
					
				 }
			}else if (hardware_read_order(i, HARDWARE_ORDER_INSIDE)){
				if (checkOrders(p->orders, i)<0){
					hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 1);
					left_shiftOrders(p->orders);
				 	p->orders[3] = i;
					if (i == 0){
						p->orders[3+4] = -1;
					}else if (i == 3){
						p->orders[3+4] = 1;
					}else{
						p->orders[3+4] = 0;
					}
					
				 }
			}else if (hardware_read_order(i, HARDWARE_ORDER_DOWN)){
				if (checkOrders(p->orders, i)<0){
					hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 1);
					left_shiftOrders(p->orders);
				 	p->orders[3] = i;
					if (i == 3){
						p->orders[3+4] = 1;	
					}else{
						p->orders[3+4] = -1;
					}
				}
			}
		}
	}
}

void delay(Panel* p, int number_of_seconds) { 
	
    int time = 1000000 * number_of_seconds;  
    clock_t start_time = clock(); 
    while (clock() < start_time + time){
		pushOrders(p);
	}
    	
} 

bool check_if_orders(Panel* p){
	
	for (unsigned int i = 0; i<=3; i++){
		if (p->orders[i] != -1) return true;
	}
	return false;
}


int maxValue(Panel* p, State* s){
	
	if (check_if_orders(p) == false){
		return s->betweenFloors[0];
	}
	int max = 0;
	for (int i = 0; i<=3; i++){
		if (p->orders[i] > max){
			max = p->orders[i];
		}
	}
	return max;	
}


int minValue(Panel* p, State* s){

	if (check_if_orders(p) == false){
		return s->betweenFloors[0];
	}	
	int min = 3;
	for (int i = 0; i<=3; i++){
		if ((p->orders[i] < min) && (p->orders[i] != -1)){
			min = p->orders[i];
		}
	}
	return min;	
}

bool series_of_downs(Panel* p){

	bool serie = false;
	for (unsigned int i = 0; i<=2; i++){
		if ((p->orders[i] != -1) && (p->orders[i+1] != -1) && (p->orders[i+4] == -1) && (p->orders[i+1+4] == -1)){
			serie = true;
		} 
	}
	return serie;
}

bool series_of_ups(Panel* p){

	bool serie = false;
	for (unsigned int i = 0; i<=2; i++){
		if ((p->orders[i] != -1) && (p->orders[i+1] != -1) && (p->orders[i+4] == 1) && (p->orders[i+1+4] == 1)){
			 serie = true;
		}
	}
	return serie;
}

int closestFloor(Panel* p, State* s){

	int direction = s->Direction;
	int currentFloor = s->betweenFloors[0];
	int destination = minValue(p,s);
	int distance;
	switch (direction){
		case -1:
			distance = currentFloor - minValue(p, s);
			for (int i = 3; i >= 0; i--){
				if (series_of_ups(p)){
					return minValue(p,s);
				}
					
				if(((currentFloor - p->orders[i]) <= distance) && (p->orders[i] != -1) && (p->orders[i+4] != 1) && (p->orders[i] <= currentFloor)){
					distance = currentFloor - p->orders[i];
					destination = p->orders[i];
				}
			}
			s->Direction = -1;
			return destination;
				
		case 1:
			distance = currentFloor - maxValue(p,s);
			for (int i = 3; i >= 0; i--){
				if (series_of_downs(p)){
					return maxValue(p,s);
				}

				if(((currentFloor - p->orders[i]) >= distance) && (p->orders[i] != -1) && (p->orders[i+4] != -1) && (p->orders[i] >= currentFloor)){
					distance = currentFloor - p->orders[i];
					destination = p->orders[i];
				}
			}
			s->Direction = 1;
			return destination;
	}

	return destination;
}

void clearExecuted(Panel* p, State* s){
	
	for (int i = 0; i<=3; i++){
		if (p->orders[i] == s->betweenFloors[0]){
			if (p->orders[i+4] == -1){
				hardware_command_order_light(p->orders[i], HARDWARE_ORDER_DOWN, 0);
			}else if (p->orders[i+4] == 0){
				hardware_command_order_light(p->orders[i], HARDWARE_ORDER_INSIDE, 0);
			}else if (p->orders[i+4] == 1){
				hardware_command_order_light(p->orders[i], HARDWARE_ORDER_UP, 0);
			}
			p->orders[i] = -1;
			p->orders[i+4] = -1;
		}
	}
}

void reached_Floor(Panel* p, State* s){
	
	int floor = closestFloor(p,s);
	
	if (check_if_orders(p) == true){
		if (floor == s->betweenFloors[0]){
        	s->reachedFloor = true;

    	}else{
        	s->reachedFloor = false;
    	}  
	}   
}
