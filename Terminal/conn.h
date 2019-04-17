#ifndef CONN_H
#define CONN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include "data.h"
using namespace std;

class Conn {
	private:
		int m_sockfd;
		bool m_is_connected;
		const char* m_host;
		int m_port;
		struct sockaddr_in m_server_addr;
	public:
		Conn();
		Conn(const char* host, const int port);

		//Getters
		const int get_port();
		const char* get_host();	
		const void get_server_info();

		//Setter
		void set_host(const char* host);
		void set_port(const int port);
		
		//Other
		bool ping_server();
		bool disconnect_server();
	//	bool connect_server(const char* hname, const int port);
		bool post_request(const Task t);
		vector<Project> get_request(char* request);
};
#endif
