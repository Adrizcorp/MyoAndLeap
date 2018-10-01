/*
 * valves.cpp
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#include "valves.h"


extern "C" {
#include "../fpga_ports/fpga_ports.h"
}

valves::valves() {
	// TODO Auto-generated constructor stub
	this->baseport = NULL;
	this->number_valves=0;
}


valves::valves(unsigned int address,unsigned char numer_of_valves){
	this->baseport = open_lw(address);

	*(unsigned int *) this->baseport = 0;

	this->number_valves=numer_of_valves;
}

void valves::turn_on(unsigned char channel){
	channel=channel%this->number_valves;

	unsigned int data=*(unsigned int *) this->baseport;
	unsigned int valve_d= 1<<channel;
	*(unsigned int *) this->baseport = data | valve_d;


}

void valves::turn_off(unsigned char channel){

	channel=channel%this->number_valves;

	unsigned int data=*(unsigned int *) this->baseport;
	unsigned int valve_d= 1<<channel;
	valve_d= ~valve_d;
	*(unsigned int *) this->baseport = data & valve_d;

}

void valves::turn_valve(unsigned char channel,unsigned char value){

	if(value==1){
		this->turn_on(channel);
	}
	else{
		this->turn_off(channel);
	}


}


void valves::off_all(){
	this->turn_DESCARGA_CAMARA_VAL(0);
	this->turn_LLENADO_VAL(0);
	this->turn_AUXILIAR_CONTROL_DESCARGA_VAL(0);
}

void valves::turn_DESCARGA_CAMARA_VAL(unsigned char value){
	this->turn_valve(DESCARGA_CAMARA_VAL,value);
}
void valves::turn_LLENADO_VAL(unsigned char value){
	this->turn_valve(LLENADO_VAL,value);
}
void valves::turn_AUXILIAR_CONTROL_DESCARGA_VAL(unsigned char value){
	this->turn_valve(AUXILIAR_CONTROL_DESCARGA_VAL,value);
}

void valves::turn_AUXILIAR_CONTROL_DESCARGA_VAL_toggle(){
	this->toggle(AUXILIAR_CONTROL_DESCARGA_VAL);
}


void valves::toggle(unsigned char channel){

	channel=channel%this->number_valves;
	unsigned int data=*(unsigned int *) this->baseport;
	unsigned int valve_d= 1<<channel;
	*(unsigned int *) this->baseport = data ^ valve_d;

}

unsigned char valves::get(unsigned char channel){

	channel=channel%this->number_valves;
	unsigned int data=*(unsigned int *) this->baseport;

	data=(data >>channel) & 1;

	return (unsigned char)data;


}

valves::~valves() {
	// TODO Auto-generated destructor stub
}

