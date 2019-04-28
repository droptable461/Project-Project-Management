#include <stdio.h>
#include <iostream>
#include <utility>
#include <stdlib.h>
#include <map>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include "conn.h"
#define DEFAULT_ADDR "0.0.0.0"
#define DEFAULT_PORT 533
char testvar[64];
using namespace std;
size_t writeback(void *ptr, size_t size, size_t nmemb, string* data){
	data->append((char*) ptr, size * nmemb);
	return size * nmemb;
}


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
		string values = "";
		values.append((string)"t_description=" + t.disc + (string)"&t_title=" + t.title + "&p_title=" + p_title);

		//printf("Sending %s to %s\n", values.c_str(), sub_url.c_str());

		curl_easy_setopt(curl, CURLOPT_URL, sub_url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values.c_str());
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
		string values = "";
		values.append((string)"b_line=" + to_string(b.lineNum) + "&b_file=" + b.file 
			+ "&b_description=" + b.disc + "&t_title=" + t_title);
		//printf("Sending %s to %s\n", values.c_str(), sub_url.c_str());

		curl_easy_setopt(curl, CURLOPT_URL, sub_url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values.c_str());
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			//fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
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
		string values = "";
		values.append((string)"p_title=" + p.title + "&p_description=" + p.disc 
			+ "&uid=" + to_string(uid));
		//printf("Sending %s to %s\n", values.c_str(), sub_url.c_str());

		curl_easy_setopt(curl, CURLOPT_URL, sub_url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values.c_str());
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			//fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return false;
		}
	}
	else
		return false;
	curl_global_cleanup();
	return true;

}
bool Conn::post_request(const User u, int uid){
	CURL *curl;
	CURLcode res;
	
	curl_global_init(CURL_GLOBAL_ALL);
	
	curl = curl_easy_init();
	
	if(curl) {

		string sub_url = m_host + "/user";
		string values = "";
		values.append((string)"uname="+ u.name);
		//printf("Sending %s to %s\n", values.c_str(), sub_url.c_str());

		curl_easy_setopt(curl, CURLOPT_URL, sub_url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeback);
		string tmp;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &tmp);
		uid = atoi(tmp.c_str());

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
		string values = "";
		values.append((string)"ph_title="+ p.title + "&p_title=" + p_title);
		//printf("Sending %s to %s\n", values.c_str(), sub_url.c_str());

		curl_easy_setopt(curl, CURLOPT_URL, sub_url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, values.c_str());
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			//fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return false;
		}
	}
	else
		return false;
	curl_global_cleanup();
	return true;


}
void check(int a)
{
cout << "[" << a << "]" << endl;
}
map<string, Project> parse_response(string res){
	map<string, Project> ret;
	check(0);
	//Do da parse
	char val;
	int cursor = 0;
	bool in_proj, in_task, in_bug, in_user = false;
	for(int i = 0; i < res.length(); ++i){
	//	check(555);
		if(res[i] == '$')
			break;
		if(res[i] == '^'){
			check(11);
			while( res[i] != '#' || res[i] != '&' || res[i]!='$'){
				i++;
				Project tmpp;
		//		check(12);
				if(res[i] == '#')
					break;
				if(res[i] == '('){
		//			check(13);
					i += 2;
					string tmp = "";
					while(res[i] != '\''){
						tmp = tmp + res[i];
		//				cout<< res[i] << endl;
						i++;
						if(res[i] == '#')
							break;
					}
					cout<< tmp << endl;
					check(i);
		//			check(14);
					++i;
					while(res[i] != '\''){
						i++;
		//				cout<<res[i] << endl;
						if(res[i] == '#')
							break;
					}
					if(tmp.length() > 0)
						tmpp.manager = tmp;
					tmp = "";
					while(res[i] != '\''){
						tmp = tmp + res[i];
						i++;
						if(res[i] == '#')
							break;
					}
					cout<< tmp << endl;
					check(i);
		//			check(15);
					++i;
					while(res[i] != '\''){
						 i++;
						if(res[i] == '#')
							break;
					}
					if(tmp.length() > 0)
						tmpp.disc = tmp;
					tmp = "";
					while(res[i] != '\''){
						tmp = tmp + res[i];
						i++;
						if(res[i] == '#')
							break;
					}
					cout << tmp << endl;
					if(tmp.length() > 0)
						tmpp.disc = tmp;
					ret[tmpp.title] = tmpp;
					
						
		//			 check(16);
					
				}
			}
			//while( val!= '&' || val != '$'){
			//	cursor++;
			//	val = res[cursor];
			//	Task tempt;
			//	if(val == '('){
			//	}
			//}
			
		}
	//	cout<< i << endl;

	}
	for( pair<string, Project> x : ret)
		cout<< x.first << ": " << x.second.title << endl;
	return ret;
}
map<string, Project> Conn::get_request()
{
	CURL* curl;
	CURLcode res;
	
	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	
	if(curl) {

		string sub_url = m_host + "/update";
		curl_easy_setopt(curl, CURLOPT_URL, sub_url.c_str());
		curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

		string response;
		string header;

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);	
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return map<string, Project> {{}};
		}
		return parse_response(response);
	}
}

