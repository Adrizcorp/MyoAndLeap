/*
 * valves.h
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#ifndef VALVES_H_
#define VALVES_H_

#define DESCARGA_CAMARA_VAL 0
#define LLENADO_VAL 1
#define AUXILIAR_CONTROL_DESCARGA_VAL 2

class valves {
public:
	unsigned long * baseport;
	unsigned char number_valves=0;
	valves();
	valves(unsigned int address,unsigned char numer_of_valves);
	void turn_on(unsigned char channel);
	void turn_off(unsigned char channel);
	void off_all();
	void turn_valve(unsigned char channel,unsigned char value);
	void turn_DESCARGA_CAMARA_VAL(unsigned char value);
	void turn_LLENADO_VAL(unsigned char value);
	void turn_AUXILIAR_CONTROL_DESCARGA_VAL(unsigned char value);
	void turn_AUXILIAR_CONTROL_DESCARGA_VAL_toggle();
	void toggle(unsigned char channel);
	unsigned char get(unsigned char channel);
	virtual ~valves();
};

#endif /* VALVES_H_ */
