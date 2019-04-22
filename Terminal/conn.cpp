#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include "conn.h"
#define DEFAULT_ADDR "0.0.0.0"
#define DEFAULT_PORT 533
using namespace std;
Conn::Conn(): m_host(DEFAULT_ADDR)
{}
Conn::Conn(const string host ): m_host(host)
{}

const string Conn::get_host(){
	return m_host;
}

void Conn::set_host(const string host){
	m_host = host;
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

bool Conn::post_request(const Task t)
{
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();


	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/task");
		string values = "";
		values.append((string)"t_description=" + t.disc + (string)"&t_title=" + t.title);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return false;
		}
		curl_easy_cleanup(curl);
	}
	else
		return false;
	curl_global_cleanup();
	return true;

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

