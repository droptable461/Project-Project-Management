#include <stdio.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "conn.h"
#define DEFAULT_ADDR "0.0.0.0"
#define DEFAULT_PORT 533
using namespace std;
Conn::Conn(): m_host(DEFAULT_ADDR), m_is_connected(false), m_port(-1)
{}
Conn::Conn(const char* host, const int port): m_host(host), m_is_connected(false), m_port(port)
{}

const int Conn::get_port(){

	return m_port;
}
const char* Conn::get_host(){
	return m_host;
}

const void Conn::get_server_info()
{
	cout<< "Server IP: " << m_server_addr.sin_addr.s_addr << endl;
	cout<< "Port: " << m_port << endl;
	cout<< "Socket File: " << m_sockfd << endl;
	if(m_is_connected){
		cout<< "CONNECTED. \n";
	}
	else{
		cout<< "NOT CONNECTED \n";
	}
	return;
	
}
void Conn::set_host(const char* host){
	m_host = host;
}
void Conn::set_port(const int port){
	m_port = port;
}

/*bool Conn::connect_server(const char* hname=DEFAULT_ADDR, const int port=DEFAULT_PORT)
{
	m_port = port;
	m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sockfd < 0){
		//error("Socket opening error!");
		return false;
	}
	if (hname == NULL){
		//error("Server is Null!");
		return false;
	}
	bzero((char *) &m_server_addr, sizeof(m_server_addr));
	bcopy(hname, (char*)&m_server_addr.sin_addr.s_addr,
		 sizeof(hname));
	m_server_addr.sin_port = htons(m_port);
	if(connect(m_sockfd, (struct sockaddr *) &m_server_addr, sizeof(m_server_addr)) < 0)
		return false;

	else{
		m_is_connected = true;
		return true;
		
	}

}*/
bool Conn::ping_server(){
	if(m_is_connected)
	{
		return true;
	}
	else{
		m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if(m_sockfd<0){
			perror("Socket");
			return false;
		}
		
		bzero((char* ) &m_server_addr, sizeof(m_server_addr));

		m_server_addr.sin_family = AF_INET;
		m_server_addr.sin_port = htons(m_port);
		inet_pton(AF_INET, m_host, &m_server_addr.sin_addr.s_addr);

		cout<<(char*)&m_server_addr.sin_addr << endl;
		if(connect(m_sockfd, (struct sockaddr*)&m_server_addr, sizeof(struct sockaddr_in)) < 0){
			perror("Connect");
			m_is_connected = false;
		}
		else
			m_is_connected = true;
	}
	return m_is_connected;
}

bool Conn::post_request(const Task t)
{
	if(m_is_connected){
	string values = "";
	/*if(!t.bugs.empty())
		for(int i = 0; i < t.bugs.size(); ++i)
		{
			string x = (string)"bug" + to_string(i) + (string)"_linenum=" + to_string(t.bugs[i].lineNum) 
				+ (string)"&bug" + to_string(i) + (string)"_file=" + t.bugs[i].file 
				+ (string)"&bug" + to_string(i) + (string)"_descr=" + t.bugs[i].disc + (string)"&";
			values.append(x);
		}
	if(!t.users.empty()){
		int count = 0;
		for(User i : t.users){
			string x = (string)"user" + to_string(count) + "_name=" + i.name
				+ "&user" + to_string(count) + (string)"_id=" + to_string(i.id) + (string)"&";
		
			values.append(x);
			count++;
		}
	}*/
	values.append((string)"?t_description=" + t.disc + (string)"&t_title=" + t.title);
	
	string request = "POST /task HTTP/1.0\r\nContent-Type: text/html\r\nContent-Length: "+ to_string(values.length()) + "\r\n\r\n" + values;
	
	const char* info = request.c_str();
	cout<< info;
	int check = write(m_sockfd, info, strlen(info));
	if(check < 0)
		return false;

	else
		return true;
	}
	else{
		return false; 
	}
}
/*vector<Project> Conn::get_request(char* request)
{	
	char* info;
	if(!m_is_connected)
		return false;

	int check = read(m_sockfd, info, 255);

	if( check < 0)
		return false;
	else
		return true;
}*/
bool Conn::disconnect_server(){
	close(m_sockfd);
	m_is_connected = false;

}
