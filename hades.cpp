#define HADES "HADES"
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <thread>

#include "clog.h"
#include "shell.h"
#include "ui.h"
#include "network_utils.h"
int help(int, char **);
int sockfd  = -1; //FIXME
//Fl_OpenCV *open_highgui;

/* 
 * Checks and sends the data to the server 
 */
int send_data(int count, char **args){
	if(count < 1)return -2;
	for(int file_i = 0; file_i < count; file_i++){
		if(write_data(sockfd, args[file_i], BUFFER_SIZE) < 0){
			printf("write failed\n");
		}
		printf("%s\n", args[file_i]);
	}
	return -1;
}

int display_data(int count, char **args){
	if(count < 1)return -2;
	return -1;
}

int list_devices(int count, char **args){
	return -1;
}

int send_raw(int count, char **args){
	if(count < 1)return -2;
	return -1;
}

int hades_connect(int count, char **args){
	if(count < 2)return -2;
	return sockfd = connect_server(args[0], atoi(args[1]));
}

job jobs[] = {
	{"help", "prints this help line", help},
	{"connect", "connect to a hades server", hades_connect},
	{"raw", "send raw data for processing commands, for debugging purposes only", send_raw},
	{"show", "displays the selected data", display_data},
	{"list", "lists the connected devices with the server", list_devices},
	{"send", "sends data to the server for processing", send_data}
};

int jlen =  sizeof(jobs)/sizeof(job);

/*
 * Help message always returns 0
 */
int help(int count, char **args){
	if(count > 1){
		for(int arg_i = 0; arg_i < count; arg_i++){
			sh_help(jlen, jobs, args[arg_i]);
		}
		return 0;
	}
	sh_help(jlen, jobs);
	return 0;
}

int main(int argc, char *argv[]){
	std::ios_base::sync_with_stdio(false);
	log_inf(HADES, "Starting GUI");
	//connect_server("localhost", 12300); //TECH DEPT
	if(argc < 2){
		load_ui(jlen, jobs, false, "hades> ");
	} else load_ui(jlen, jobs);
	return 0;
}
