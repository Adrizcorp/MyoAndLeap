/*
 * DataLogger.h
 *
 *  Created on: Aug 26, 2016
 *      Author: Holguer
 */

#ifndef DATALOGGER_H_
#define DATALOGGER_H_

//json docs https://github.com/nlohmann/json/tree/develop/doc/examples

#include <string>


#include "json.hpp"


using json = nlohmann::json;




class DataLogger {

public:
	std::string current_cycle_file;
	std::string current_cycle_file2print;
	json current_cycle_2_save;
	json init_configs;
	int current_cycle;
	int last_cycle;
	std::string admin_pass;
	std::string user_pass;

	DataLogger();

	//Basic functions
	char CheckDiskStatus();
	char CheckIfSystemWasShutAbruted();
	char append_data_toFile(std::string document, std::string text);
	char create_new_file(char * document);
	char delete_file(char * document);
	char read_byte(char *document);
	void load_file_into_string(char *document,std::string * output_string);
	void save_string2File(char *document, std::string * output_string);
	//Datalogger
	void load_init_configs();
	void load_admin_pass();
	void load_usr_pass();
	void save_init_configs();
	void save_admin_pass();
	void save_usr_pass();
	//cycles utilities
	void create_a_cycle(int number);
	char load_a_cycle(int number);
	void save_cycle();
	void delete_cycle();
	void cycle2Printfile(int sampler);//sampler en segundos



	// Json Test, DO not run
	void testJson();
	void testJson2();
	virtual ~DataLogger();
};

#endif /* DATALOGGER_H_ */
