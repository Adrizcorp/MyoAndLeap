/*
 * DataLogger.cpp
 *
 *  Created on: Aug 26, 2016
 *      Author: Holguer
 */

#include "DataLogger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>

#include "json.hpp"

char buffer_data_logger[512];
DataLogger::DataLogger() {
	// TODO Auto-generated constructor stub

}

char DataLogger::append_data_toFile(std::string document, std::string text) {
	FILE * pFile;

	pFile = fopen(document.c_str(), "a+");
	if (pFile != NULL) {
		fwrite(text.c_str(), sizeof(char), text.length(), pFile);
		fclose(pFile);
	}

}

char DataLogger::create_new_file(char * document) {
	snprintf(buffer_data_logger, sizeof(buffer_data_logger), "echo > %s",
			document);
	system(buffer_data_logger);
}

char DataLogger::delete_file(char * document) {
	snprintf(buffer_data_logger, sizeof(buffer_data_logger), "rm  %s",
			document);
	system(buffer_data_logger);
}

char DataLogger::CheckDiskStatus() {
	FILE * pFile;
	pFile = fopen("/Stericlinic/Init_config/Init_config", "r");
	if (pFile != NULL) {
		printf("La estructura de Datos del Systema de Archivos es Correcta!\n");
		fclose(pFile);
		return 1;

	}

	printf("La estructura de Datos del Systema de Archivos no es correcta\n");
	return 0;
}

char DataLogger::read_byte(char *document) {
	FILE * pFile;
	char read_byte;
	pFile = fopen(document, "r");
	if (pFile != NULL) {
		fread(&read_byte, 1, 1, pFile);
		fclose(pFile);
		return read_byte;
	}

	return -1;
}

char DataLogger::CheckIfSystemWasShutAbruted() {
	char ret_value = 0;
	if (this->current_cycle != this->last_cycle) {
		ret_value = 1;
		puts("El sistema fue apagado Incorrectamente\n");
	} else {
		ret_value = 0;
		puts("El sistema fue apagado correctamente\n");

	}

	return ret_value;

}

void DataLogger::testJson2() {
	std::string orig_str { "{\n"
			"  \"firstName\": \"John\",\n"
			"  \"lastName\": \"Smith\",\n"
			"  \"isAlive\": true,\n"
			"  \"age\": 25,\n"
			"  \"double\": 42.42,\n"
			"  \"address\": {\n"
			"    \"streetAddress\": \"21 2nd Street\",\n"
			"    \"city\": \"New York\",\n"
			"    \"state\": \"NY\",\n"
			"    \"postalCode\": \"10021-3100\"\n"
			"  },\n"
			"  \"phoneNumbers\": [\n"
			"    {\n"
			"      \"type\": \"home\",\n"
			"      \"number\": \"212 555-1234\"\n"
			"    },\n"
			"    {\n"
			"      \"type\": \"office\",\n"
			"      \"number\": \"646 555-4567\"\n"
			"    }\n"
			"  ],\n"
			"  \"children\": [],\n"
			"  \"spouse\": null,\n"
			"  \"emptyobj\": {},\n"
			"  \"escaped\": \"hello\\\"world\\\\!\"\n"
			"}" };

	json j_complete = json::parse(orig_str);
	j_complete["firstName"] = "Holguer A. Becerra";
	std::cout << std::setw(4) << j_complete << "\n\n";

	std::fstream filestr;
	filestr.open("/Stericlinic/Init_config/Init_config_test",
			std::fstream::out);
	filestr << std::setw(4) << j_complete << "\n\n";
	filestr.close();

	std::string str;
	load_file_into_string("/Stericlinic/Init_config/Init_config_test", &str);

	json j_complete2 = json::parse(str);
	j_complete2["firstName"] = "Holguer A. Becerra 2";
	std::cout << std::setw(4) << j_complete2 << "\n\n";
}

void DataLogger::testJson() {

	int test = 0;
	// create a JSON object
	json j = { { "pi", 3.141 }, { "happy", true }, { "name", "Niels" }, {
			"nothing", nullptr }, { "answer", { { "everything", 42 } } }, {
			"list", { 1, 0, 2 } }, { "object", { { "currency", "USD" }, {
			"value", 42.99 } } } };

	// add new values
	j["new"]["key"]["value"] = {"another", "list"};

	// count elements
	j["size"] = j.size();
	j["size"] = 1;
	j["name"] = "Holguer A. Becerra";
	j["list"]= {5,4,5,7};
	j["list"][4] = 20;
	j["list"][5] = 41;
	test = j["list"][0];
	std::cout << std::setw(4) << "\nvalor_test[" << j["list"].size() << "]= "
			<< j["list"] << '\n';
	std::cout << std::setw(4) << "valor_test[0]= " << test << '\n';
	std::cout << "Json==>" << "\n";
	// pretty print with indent of 4 spaces
	std::cout << std::setw(4) << j << '\n';

}

void DataLogger::load_file_into_string(char *document,
		std::string * output_string) {
	std::ifstream ifs(document);
	std::string content((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));

	*output_string = content;

}

void DataLogger::load_init_configs() {
	std::string content;
	this->load_file_into_string("/Stericlinic/Init_config/Init_config",
			&content);

	this->init_configs = json::parse(content);
	this->current_cycle = this->init_configs["general"]["current_cycle"];
	this->last_cycle = this->init_configs["general"]["last_cycle"];
	//std::cout << std::setw(4) << this->init_configs << '\n';

}

void DataLogger::load_admin_pass() {
	load_file_into_string("/Stericlinic/Init_config/steripass_admin",
			&this->admin_pass);
	//std::cout << "admin Pass: " << this->admin_pass << '\n';
}

void DataLogger::load_usr_pass() {
	load_file_into_string("/Stericlinic/Init_config/steripass_user",
			&this->user_pass);

	//std::cout << "user Pass: " << this->user_pass << '\n';
}

void DataLogger::save_init_configs() {
	std::fstream filestr;
	filestr.open("/Stericlinic/Init_config/Init_config",
			std::fstream::in | std::fstream::out);
	filestr << std::setw(4) << this->init_configs << "\n\n";
	filestr.close();
}

void DataLogger::save_string2File(char *document, std::string * output_string) {
	std::fstream filestr;
	filestr.open(document, std::fstream::in | std::fstream::out);
	filestr << *output_string;
	filestr.close();
}

void DataLogger::save_admin_pass() {
	this->save_string2File("/Stericlinic/Init_config/steripass_admin",
			&this->admin_pass);
}

void DataLogger::save_usr_pass() {
	this->save_string2File("/Stericlinic/Init_config/steripass_user",
			&this->user_pass);
}

//cycles utilities
void DataLogger::create_a_cycle(int number) {
	std::string content;
	std::fstream filestr;
	this->load_file_into_string("/Stericlinic/Cycles/cycle_template", &content);

	this->current_cycle_2_save = json::parse(content);
	this->current_cycle_2_save["cycle"]["number"] = number;

	char numero[100];
	sprintf(numero, "/Stericlinic/Cycles/cycle%d", number);
	std::string archivo(numero);
	this->current_cycle_file = archivo;

	this->create_new_file((char*) this->current_cycle_file.c_str());

	filestr.open((char*) this->current_cycle_file.c_str(),
			std::fstream::in | std::fstream::out);
	filestr << std::setw(4) << this->current_cycle_2_save << "\n\n";
	filestr.close();

	//std::cout << std::setw(4) << this->current_cycle_file.c_str() << '\n';

}

char DataLogger::load_a_cycle(int number) {
	char numero[100];
	sprintf(numero, "/Stericlinic/Cycles/cycle%d", number);
	std::string archivo(numero);
	this->current_cycle_file = archivo;
	std::string content;


	FILE * pFile;
	pFile = fopen((char*)archivo.c_str(), "r");
	if (pFile != NULL) {
		fclose(pFile);
	}else{
		puts("Cyclo no existe\n");
		return 0;
	}


	this->load_file_into_string((char*) archivo.c_str(), &content);

	this->current_cycle_2_save = json::parse(content);

	return 1;
//	std::cout << std::setw(4) << this->current_cycle_2_save << '\n';
}

void DataLogger::save_cycle() {
	std::fstream filestr;
	char numero[100];

	if (this->read_byte((char*) this->current_cycle_file.c_str()) == -1) {
		return;
	}

	filestr.open((char*) this->current_cycle_file.c_str(),
			std::fstream::in | std::fstream::out);
	filestr << std::setw(4) << this->current_cycle_2_save << "\n\n";
	filestr.close();

}

void DataLogger::delete_cycle() {
	this->delete_file((char*) this->current_cycle_file.c_str());
}

void DataLogger::cycle2Printfile(int sampler) {
	char numero[100];
	json::string_t dato;
	double promedio_temp = 0.0;
	double promedio_pressure = 0.0;
	double numero_de_datos = 0;
	sprintf(numero, "/Stericlinic/Cycle2Print/cycle%d",
			(int) this->current_cycle_2_save["cycle"]["number"]);
	std::string archivo(numero);
	this->create_new_file((char*) archivo.c_str());

	this->current_cycle_file2print=archivo;

	int i;
	this->append_data_toFile((char*) archivo.c_str(),
			"--------------------------------\n");
	this->append_data_toFile((char*) archivo.c_str(), "Fecha: ");
	dato = this->current_cycle_2_save["cycle"]["date"];
	this->append_data_toFile((char*) archivo.c_str(), dato);
	this->append_data_toFile((char*) archivo.c_str(), "\n");
	this->append_data_toFile((char*) archivo.c_str(), "Inicio: ");
	dato = this->current_cycle_2_save["cycle"]["startC"];
	this->append_data_toFile((char*) archivo.c_str(), dato);
	this->append_data_toFile((char*) archivo.c_str(), "\n");
	this->append_data_toFile((char*) archivo.c_str(), "Fin: ");
	dato = this->current_cycle_2_save["cycle"]["endC"];
	this->append_data_toFile((char*) archivo.c_str(), dato);
	this->append_data_toFile((char*) archivo.c_str(), "\n");
	this->append_data_toFile((char*) archivo.c_str(), "Ciclo: ");
	sprintf(numero, "%d", (int) this->current_cycle_2_save["cycle"]["number"]);
	dato = numero;
	this->append_data_toFile((char*) archivo.c_str(), dato);
	this->append_data_toFile((char*) archivo.c_str(), "\n");
	this->append_data_toFile((char*) archivo.c_str(), "Tipo: ");
	sprintf(numero, "%d", (int) this->current_cycle_2_save["cycle"]["type"]);
		dato = numero;
	this->append_data_toFile((char*) archivo.c_str(), dato);
	this->append_data_toFile((char*) archivo.c_str(), "\n");
	this->append_data_toFile((char*) archivo.c_str(),
			"--------------------------------\n");
	this->append_data_toFile((char*) archivo.c_str(), "Parametros Ciclo\n");
	this->append_data_toFile((char*) archivo.c_str(), "Est: \n  ");
	sprintf(numero, "%d", (int) this->current_cycle_2_save["cycle"]["Testeri"]);
	dato = numero;
	this->append_data_toFile((char*) archivo.c_str(), dato);
	this->append_data_toFile((char*) archivo.c_str(), "\nSec: \n  ");
	sprintf(numero, "%d", (int) this->current_cycle_2_save["cycle"]["TSecado"]);
	dato = numero;
	this->append_data_toFile((char*) archivo.c_str(), dato);
	this->append_data_toFile((char*) archivo.c_str(),
			"\n--------------------------------\n");
	this->append_data_toFile((char*) archivo.c_str(), "Preparacion:\n");

	for (i = 0;
			i
					< this->current_cycle_2_save["Temp1"]["estabilizacion"]["time"].size();
			i = i + sampler) {
		dato = this->current_cycle_2_save["Temp1"]["estabilizacion"]["time"][i];
		this->append_data_toFile((char*) archivo.c_str(), dato);
		this->append_data_toFile((char*) archivo.c_str(), "  ");
		sprintf(numero, "  %0.2f",
				(double) this->current_cycle_2_save["Temp1"]["estabilizacion"]["data"][i]);
		dato = numero;
		this->append_data_toFile((char*) archivo.c_str(), dato);
		this->append_data_toFile((char*) archivo.c_str(), " C\370  ");
		this->append_data_toFile((char*) archivo.c_str(), "");

		sprintf(numero, "%0.2f",
				(double) this->current_cycle_2_save["Pressure1"]["estabilizacion"]["data"][i]);
		dato = numero;
		this->append_data_toFile((char*) archivo.c_str(), dato);
		this->append_data_toFile((char*) archivo.c_str(), " psi\n");
	}

	this->append_data_toFile((char*) archivo.c_str(), "Esterilizando:\n");

	for (i = 0;
			i < this->current_cycle_2_save["Temp1"]["esteri"]["time"].size();
			i = i + sampler) {
		dato = this->current_cycle_2_save["Temp1"]["esteri"]["time"][i];
		this->append_data_toFile((char*) archivo.c_str(), dato);
		this->append_data_toFile((char*) archivo.c_str(), "  ");
		sprintf(numero, "  %0.2f",
				(double) this->current_cycle_2_save["Temp1"]["esteri"]["data"][i]);
		double valor=  (double) this->current_cycle_2_save["Temp1"]["esteri"]["data"][i];
		promedio_temp =valor+promedio_temp;
		promedio_temp = promedio_temp / 2.0;
		dato = numero;
		this->append_data_toFile((char*) archivo.c_str(), dato);
		this->append_data_toFile((char*) archivo.c_str(), " C\370");
		this->append_data_toFile((char*) archivo.c_str(), "  ");

		sprintf(numero, "%0.2f",
				(double) this->current_cycle_2_save["Pressure1"]["esteri"]["data"][i]);

		valor=  (double) this->current_cycle_2_save["Pressure1"]["esteri"]["data"][i];
		promedio_pressure =valor+
				promedio_pressure;
		promedio_pressure = promedio_pressure / 2.0;

		dato = numero;
		this->append_data_toFile((char*) archivo.c_str(), dato);
		this->append_data_toFile((char*) archivo.c_str(), " psi\n");

	}

	this->append_data_toFile((char*) archivo.c_str(), "Secado:\n");

	for (i = 0;
			i < this->current_cycle_2_save["Temp1"]["secado"]["time"].size();
			i = i + sampler) {
		dato = this->current_cycle_2_save["Temp1"]["secado"]["time"][i];
		this->append_data_toFile((char*) archivo.c_str(), dato);
		this->append_data_toFile((char*) archivo.c_str(), "  ");
		sprintf(numero, "  %0.2f",
				(double) this->current_cycle_2_save["Temp1"]["secado"]["data"][i]);
		dato = numero;
		this->append_data_toFile((char*) archivo.c_str(), dato);
		this->append_data_toFile((char*) archivo.c_str(), " C\370");
		this->append_data_toFile((char*) archivo.c_str(), "  ");

		sprintf(numero, "%0.2f",
				(double) this->current_cycle_2_save["Pressure1"]["secado"]["data"][i]);
		dato = numero;
		this->append_data_toFile((char*) archivo.c_str(), dato);
		this->append_data_toFile((char*) archivo.c_str(), " psi\n");
	}

	this->append_data_toFile((char*) archivo.c_str(), "Descarga:\n");

	for (i = 0;
			i < this->current_cycle_2_save["Temp1"]["descarga"]["time"].size();
			i = i + sampler) {
		dato = this->current_cycle_2_save["Temp1"]["descarga"]["time"][i];
		this->append_data_toFile((char*) archivo.c_str(), dato);
		this->append_data_toFile((char*) archivo.c_str(), "  ");
		sprintf(numero, "  %0.2f",
				(double) this->current_cycle_2_save["Temp1"]["descarga"]["data"][i]);
		dato = numero;
		this->append_data_toFile((char*) archivo.c_str(), dato);
		this->append_data_toFile((char*) archivo.c_str(), " C\370");
		this->append_data_toFile((char*) archivo.c_str(), "  ");

		sprintf(numero, "%0.2f",
				(double) this->current_cycle_2_save["Pressure1"]["descarga"]["data"][i]);
		dato = numero;
		this->append_data_toFile((char*) archivo.c_str(), dato);
		this->append_data_toFile((char*) archivo.c_str(), " psi\n");
	}

	this->append_data_toFile((char*) archivo.c_str(), "Tiempo inicio Ciclo:\n");
	this->append_data_toFile((char*) archivo.c_str(), "  ");
	dato = this->current_cycle_2_save["cycle"]["startC"];
	this->append_data_toFile((char*) archivo.c_str(), dato);
	this->append_data_toFile((char*) archivo.c_str(), "\n");
	this->append_data_toFile((char*) archivo.c_str(),
			"Tiempo Comienzo Esteri:\n");
	this->append_data_toFile((char*) archivo.c_str(), "  ");
	dato = this->current_cycle_2_save["cycle"]["startE"];
	this->append_data_toFile((char*) archivo.c_str(), dato);
	this->append_data_toFile((char*) archivo.c_str(), "\n");
	this->append_data_toFile((char*) archivo.c_str(),
			"Tiempo Descarga:\n");
	this->append_data_toFile((char*) archivo.c_str(), "  ");
	dato = this->current_cycle_2_save["cycle"]["startS"];
	this->append_data_toFile((char*) archivo.c_str(), dato);
	this->append_data_toFile((char*) archivo.c_str(), "\n");

	this->append_data_toFile((char*) archivo.c_str(),
			"--------------------------------\n");
	this->append_data_toFile((char*) archivo.c_str(), "Temp Promedio: ");
	sprintf(numero, "%0.2f C\370\n", promedio_temp);
	dato = numero;
	this->append_data_toFile((char*) archivo.c_str(), dato);
	this->append_data_toFile((char*) archivo.c_str(), "Presion Promedio: ");
	sprintf(numero, "%0.2f psi\n", promedio_pressure);
	dato = numero;
	this->append_data_toFile((char*) archivo.c_str(), dato);
	this->append_data_toFile((char*) archivo.c_str(),
				"--------------------------------\n");
	double tipo_ciclo=(double) this->current_cycle_2_save["cycle"]["type"];
	if(promedio_temp<=(tipo_ciclo-1.5) || promedio_temp>=(tipo_ciclo+1.5)){
		this->append_data_toFile((char*) archivo.c_str(),
						"Ciclo:  | Fallo |  \n");
	}
	else{
		this->append_data_toFile((char*) archivo.c_str(),
								"Ciclo:  | Aprobado |  \n");
	}

	this->append_data_toFile((char*) archivo.c_str(),
				"--------------------------------\n");

}

DataLogger::~DataLogger() {
	// TODO Auto-generated destructor stub
}

