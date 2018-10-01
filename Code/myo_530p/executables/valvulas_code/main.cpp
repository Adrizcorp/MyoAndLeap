/*
 * main.cpp/
 *
 *  Created on: Aug 11, 2016
 *      Author: Holguer
 */

extern "C" {
#include "hpss.h"
#include "./fpga_ports/fpga_ports.h"

}

#include "Valves/valves.h"

valves * Valvulas;

void init_system() {

	//inicializa el hw
	fflush(stdout);
	init_hw();
	fflush(stdout);

	//Valves
	Valvulas = new valves(VALVES_CONTROL_BASE, 3);

}

int main(int argc, char *argv[]) {

	//inicializa el hw y lso perifericos
	init_system();

	int i;
	int number = 0;
	if (argc > 1) {

		sscanf(argv[1], "%d", &number);
		int anterior= Valvulas->get(number);
		printf("Prediendo valvula %d\n", number);
		for (i = 0; i < 500; i++) {
			Valvulas->turn_on(number);
			usleep(10000);
		}
//		if(anterior==1){
//			Valvulas->turn_on(number);
//		}
//		else{
			Valvulas->turn_off(number);
//		}
	} else {
		printf("error\n");
	}
	//close ports
	uninit_hw();

	return 0;
}

