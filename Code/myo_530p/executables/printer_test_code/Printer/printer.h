/*
 * printer.h
 *
 *  Created on: Aug 31, 2016
 *      Author: Holguer
 */

#ifndef PRINTER_H_
#define PRINTER_H_

#include <string>
class printer {
private:
	std::string port;
public:
	char enable;
	char printting=0;
	printer();
	printer(char *printer_port);
	void print(char * document);
	char getStatus();
	virtual ~printer();
};

#endif /* PRINTER_H_ */
