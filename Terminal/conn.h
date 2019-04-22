#ifndef CONN_H
#define CONN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <curl/curl.h>
#include "data.h"
using namespace std;

class Conn {
	private:
		string m_host;
	public:
		Conn();
		Conn(string host );

		//Getters
		const int get_port();
		const string get_host();	
		const void get_server_info();

		//Setter
		void set_host(const string host);
		
		//Other
		bool auth(User u, string pword);
	//	bool connect_server(const char* hname, const int port);
		//POSTS
		bool post_request(const Task t);
		bool post_request(const Bug b);
		bool post_request(const Project p);
		bool post_request(const User u);
		bool post_request(const Phase p);
	
		//GETS
		vector<Project> get_request(char* request);
};
#endif
