#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

class Conn {
	private:
		int m_sockfd;
		bool m_is_connected;
		struct sockaddr_in m_server_addr;
		int m_port;
		struct hostent *m_server;
	public:
		Conn();
		void get_server_info();
		bool connect_server(const char* hname, const int port);
		bool upload(const char* info);
		bool download(char *info);
		bool disconnect_server();
};
