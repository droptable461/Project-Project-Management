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
Conn::Conn(): m_is_connected(true), m_port(0)
{}

void Conn::get_server_info()
{
	if(m_is_connected){
		cout<< "CONNECTED. \n";
		cout<< "Server IP: " << m_server_addr.sin_addr.s_addr << endl;
		cout<< "Port: " << m_port << endl;
		cout<< "Socket File: " << m_sockfd << endl;
		return;
	}
	else{
		cout<< "NOT CONNECTED \n";
		return;
	}
	
}

bool Conn::connect_server(const char* hname=DEFAULT_ADDR, const int port=DEFAULT_PORT)
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

}
bool Conn::upload(const char* info)
{
	if(!m_is_connected)
		return false;
	int check = write(m_sockfd, info, sizeof(info));
	if(check < 0)
		return false;

	else
		return true;
}
bool Conn::download(char* info)
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
