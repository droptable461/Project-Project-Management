#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include "conn.h"
#define DEFAULT_ADDR "0.0.0.0"
#define DEFAULT_PORT 533
char testvar[64];
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

bool Conn::post_request(const Task t, string p_title)
{
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();


	if(curl) {
		string sub_url = m_host + "/task";
		curl_easy_setopt(curl, CURLOPT_URL, sub_url.c_str());
		string values = "";
		values.append((string)"t_description=" + t.disc + (string)"&t_title=" + t.title + "&p_title=" + p_title);


		curl_easy_setopt(curl, CURLOPT_READDATA, &testvar);
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
bool Conn::post_request(const Bug b, const string t_title){
	CURL *curl;
	CURLcode res;
	
	curl_global_init(CURL_GLOBAL_ALL);
	
	curl = curl_easy_init();
	
	if(curl) {

		string sub_url = m_host + "/bug";
		
		curl_easy_setopt(curl, CURLOPT_URL, sub_url.c_str());
		string values = "";
		values.append((string)"b_line=" + to_string(b.lineNum) + "&b_file=" + b.file 
			+ "&b_description=" + b.disc + "&t_title=" + t_title);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return false;
		}
	}
	else
		return false;
	curl_global_cleanup();
	return true;

}
bool Conn::post_request(const Project p, const int uid){
	CURL *curl;
	CURLcode res;
	
	curl_global_init(CURL_GLOBAL_ALL);
	
	curl = curl_easy_init();
	
	if(curl) {

		string sub_url = m_host + "/project";
		
		curl_easy_setopt(curl, CURLOPT_URL, sub_url.c_str());
		string values = "";
		values.append((string)"p_title=" + p.title + "&p_description=" + p.disc 
			+ "&uid=" + to_string(uid));
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return false;
		}
	}
	else
		return false;
	curl_global_cleanup();
	return true;

}
bool Conn::post_request(const User u){
	CURL *curl;
	CURLcode res;
	
	curl_global_init(CURL_GLOBAL_ALL);
	
	curl = curl_easy_init();
	
	if(curl) {

		string sub_url = m_host + "/user";
		
		curl_easy_setopt(curl, CURLOPT_URL, sub_url.c_str());
		string values = "";
		values.append((string)"uname="+ u.name);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return false;
		}
	}
	else
		return false;
	curl_global_cleanup();
	return true;

} 
bool Conn::post_request(const Phase p, const string p_title){
	CURL *curl;
	CURLcode res;
	
	curl_global_init(CURL_GLOBAL_ALL);
	
	curl = curl_easy_init();
	
	if(curl) {

		string sub_url = m_host + "/phase";
		
		curl_easy_setopt(curl, CURLOPT_URL, sub_url.c_str());
		string values = "";
		values.append((string)"ph_title="+ p.title + "&p_title=" + p_title);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return false;
		}
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

