/*
 * printer.cpp
 *
 *  Created on: Aug 31, 2016
 *      Author: Holguer
 */

#include "printer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer_print[200];
printer::printer() {
	// TODO Auto-generated constructor stub
	this->port="/dev/ttyS1";
	this->enable=0;
	this->printting=0;
}

printer::printer(char *printer_port) {
	snprintf(buffer_print,sizeof(buffer_print),"%s",printer_port);
	this->port=buffer_print;
	this->enable=0;
	this->printting=0;
}



void printer::print(char * document){
	FILE *fp;
	char path[1035];
	snprintf(buffer_print,sizeof(buffer_print),"python /Stericlinic/Printer/Python/print.py %s %s",this->port.c_str(),document);
	/* Open the command for reading. */
	this->printting=1;
	fp = popen(buffer_print,"r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		return;
	}
	/* close */
	pclose(fp);
	this->printting=0;


}

char printer::getStatus(){
	FILE *fp;
	char path[1035];

	if(this->printting==1){
		return 1;
	}
	/* Open the command for reading. */
	fp = popen("python /Stericlinic/Printer/Python/State.py", "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		return 0;
	}

	puts("impresora:");
	this->enable=0;
	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		printf("%s", path);
		if(strstr (path,"True")){
			this->enable=1;
		}
	}
	puts("\n");

	/* close */
	pclose(fp);

	return this->enable;

}

printer::~printer() {
	// TODO Auto-generated destructor stub
}

