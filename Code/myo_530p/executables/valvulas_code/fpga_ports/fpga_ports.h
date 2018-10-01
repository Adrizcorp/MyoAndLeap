/*
 * fpga_ports.h
 *
 *  Created on: Aug 18, 2016
 *      Author: Holguer
 */

#ifndef FPGA_PORTS_H_
#define FPGA_PORTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

void open_ports_lw();
unsigned long * open_lw(unsigned int base_addr);
void open_ports(unsigned int base_addr, unsigned int span);


void close_ports();
void init_hw();
void uninit_hw();

#endif /* FPGA_PORTS_H_ */
