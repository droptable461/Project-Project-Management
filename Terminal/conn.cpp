#include <stdio.h>
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
		m_socketfd = socket(AF_INET, SOCK_STREAM, 0);
		if(m_sockfd<0){
			return false;
		}
		bzero((char* ) &m_server_addr, sizeof(m_server_addr));
		bcopy(m_host, (char*)&m_server_addr.sin_addr.s_addr, sizeof(hname));
		m_server_addr.sin_port = htons(m_port);
		if(connect(m_sockfd, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr)) < 0)
			m_is_connected = false;
		else
			m_is_connected = true;
	}
	return m_is_connected;
}
}
bool Conn::post_request(const Task t)
{
	if(m_is_connected){
	string values = "";
	if(!t.bugs.empty())
		for(int i = 0; i < t.bugs.size(); ++i)
		{
			string x = "bug" + i + "_linenum=" + t.bugs[i].linenum 
				+ "&bug" + i + "_file=" + t.bugs[i].file 
				+ "&bug" + i + "_descr=" + t.bugs[i].disc + "&";
			values.append(x);
		}
	if(!t.users.empty())
		int count = 0;
		for(User i : t.users){
			string x = "user" + count + "_name=" + i.name
				+ "&user" + count + "_id=" + i.id + "&";
		
			values.append(x);
		}
	values.append("t_description=" + t.disc + "&t_title=" + t.title;
	
	string request = "POST /task HTTP/1.1\nHost: " + m_host + "\n Content-Type: application/x-www-form-urlencoded\nContent-Length: " + values.length() +"\n"+ values;
	const char* info = request.c_str();
	int check = write(m_sockfd, info, sizeof(info));
	if(check < 0)
		return false;

	else
		return true;
	}
	else{
		return false; 
	}
}
vector<Project> Conn::get_request(char* request)
{
	if(!m_is_connected)
		return false;

	int check = read(m_sockfd, info, 255);

	if( check < 0)
		return false;
	else
		return true;
}
bool Conn::disconnect_server(){
	close(m_sockfd);
	m_is_connected = false;

}
