#ifndef CONN_H
#define CONN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <map>
#include <vector>
#include <curl/curl.h>
#include "data.h"
using namespace std;
extern char testvar[64];
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
		bool post_request(const Task t, const string p_title);
		bool post_request(const Bug b, const string t_title);
		bool post_request(const Project p, const int uid);
		bool post_request(const User u, int uid=0);
		bool post_request(const Phase p, const string p_title);
	
		//GETS
		map<string, Project> get_request();
};
#endif
