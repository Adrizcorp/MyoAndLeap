/*
 * main.cpp/
 *
 *  Created on: Aug 11, 2016
 *      Author: Holguer
 */

extern "C" {
#include "hpss.h"
#include <stdio.h>
}

#include "DataLog/DataLogger.h"
#include "Printer/printer.h"

DataLogger * grabador;

printer * impresora;

void init_system() {

	//datalogger
	grabador = new DataLogger();

	//Printer
	impresora = new printer();
}

int main(int argc, char *argv[]) {

	//inicializa el hw y lso perifericos
	init_system();

	// test json para configuraciones iniciales
	//grabador->testJson2();

	//test para ciclo
	if (grabador->load_a_cycle(9999) == 0) {

		return 0;
	}
	grabador->current_cycle_2_save["cycle"]["type"] = 134;
	grabador->current_cycle_2_save["Temp1"]["esteri"]["time"][0] = "17:00";
	grabador->current_cycle_2_save["Temp1"]["esteri"]["time"][1] = "18:00";
	grabador->current_cycle_2_save["Temp1"]["esteri"]["time"][2] = "19:00";
	grabador->current_cycle_2_save["Temp1"]["esteri"]["data"][2] = 120;

	grabador->save_cycle();

	grabador->create_a_cycle(2);
	grabador->current_cycle_2_save["cycle"]["type"] = 137;
	grabador->current_cycle_2_save["Temp1"]["esteri"]["data"][1] = 137 * 2;
	grabador->save_cycle();
	grabador->cycle2Printfile(1);
//	grabador->delete_cycle();

	printf("Testing-----Printer---------\n\n");
	if (impresora->getStatus()) {
		puts("Imprimiendo...\n");

		impresora->print((char*)grabador->current_cycle_file2print.c_str());
	} else {
		puts("impresora no conectada\n");

	}

	return 0;
}

