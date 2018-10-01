/*
 * fpga_ports.c
 *
 *  Created on: Aug 18, 2016
 *      Author: Holguer
 */

#include "../fpga_ports/fpga_ports.h"

#include "hps.h"
#include "../hpss.h"


int physical_memory_fd = -1;
void *ports_base; //el axi
void *lw_ports_base;// el axi lw


void init_hw() {

	//se abren e inicializan los puertos axi
	open_ports(0xc0000000, 512*8);

	 //se abren los lw axi
	open_ports_lw();

	//inicializar uart



}

void uninit_hw() {

	close_ports();
}

void open_ports(unsigned int base_addr, unsigned int span) {
	if (physical_memory_fd < 0)
		physical_memory_fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (physical_memory_fd < 0) {
		printf(
				"Failed to open /dev/mem for read/write -- permissions perhaps?\n");
		exit(-__LINE__);
	}
	ports_base = mmap(NULL, span, PROT_READ | PROT_WRITE, MAP_SHARED,
			physical_memory_fd, base_addr);
	if (ports_base == MAP_FAILED) {
		printf("Failed to mmap physical memory page.\n");
		exit(-__LINE__);
	}
}

void open_ports_lw(){

	if (physical_memory_fd < 0)
		physical_memory_fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (physical_memory_fd < 0) {
		printf(
				"Failed to open /dev/mem for read/write -- permissions perhaps?\n");
		exit(-__LINE__);
	}


    //lw axi
    lw_ports_base= mmap( NULL, 0x04000000, ( PROT_READ | PROT_WRITE ), MAP_SHARED, physical_memory_fd, ALT_STM_OFST);

    if (lw_ports_base == MAP_FAILED) {
        printf("Failed to mmap physical memory page.\n");
        exit(-__LINE__);
    }

}

unsigned long * open_lw(unsigned int base_addr) {
	unsigned long *temporal=NULL;

    //divisor de frecuencia
    temporal= lw_ports_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST+ base_addr ) & ( unsigned long)( 0x04000000-1 ) );

    return temporal;
}


void close_ports() {
	if (physical_memory_fd >= 0)
		close(physical_memory_fd);
}

