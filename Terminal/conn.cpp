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

bool Conn::post_request(const Task t, string p_title, string ph_title)
{
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();


	if(curl) {

		string sub_url = m_host + "/task";
		string values = "";
		values.append((string)"t_description=" + t.disc + (string)"&t_title=" + t.title + "&p_title=" + p_title + "&ph_title=" + ph_title);

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
//void check(int a)
//{
//cout << "[" << a << "]" << endl;
//}

/*
^('Tman1', 'testProj1', 'abcdefghijklmnop', 1, None) #(1, 'testTask1', 'onetwothree', 'todo', None, None) &(1, 'tejas', 'roma', 'sima') *('thomas', 'testProj1', 2)*/ 
map<string, Project> parse_response(string res, Conn* curr){
	map<string, Project> ret;
	//check(0);
	//Do da parse
	string proj, task, bug, usr; 
	int p1, p2;
	p1 = res.find_first_of('^');
	if(p1 < 0){
		fprintf(stderr, "Update Message Error");
		return map<string, Project>();
	}
	p2 = res.find_first_of('#');
	proj = res.substr(p1+1, (p2 - p1) - 1);
//	printf("Projects: %s\n", proj.c_str());
	p1 = p2;
	p2 = res.find_first_of('&');
	task = res.substr(p1+1, (p2-p1)-1);
//	printf("Tasks: %s\n", task.c_str());
	p1 = p2;
	p2 = res.find_first_of('*');
	bug = res.substr(p1+1, (p2-p1)-1);
	//printf("Bugs: %s\n", bug.c_str());
	p1 = p2;
	p2 = res.find_first_of('$');
	usr = res.substr(p1+1, (p2-p1)-1);
//	printf("Users: %s\n", usr.c_str());

	//Project Parsing
	p1 = 0;
	p2 = 0;
	int end = proj.find_last_of('\'');
	bool first_loop = true;
	while(p2 < end){
		Project proj_tmp;
		string proj_mod;
		string man, desc, title;
		if(first_loop){
			p1 = proj.find('\'');
			first_loop = false;
		}
		else
		
		p1 = proj.find('\'', p2+1);
		p2 = proj.find('\'', p1+1);
		man = proj.substr(p1+1, (p2-p1)-1);
		p1 = proj.find('\'', p2+1);
		p2 = proj.find('\'', p1+1);
		title = proj.substr(p1+1, (p2-p1)-1);
		p1 = proj.find('\'', p2+1);
		p2 = proj.find('\'', p1+1);
		desc = proj.substr(p1+1, (p2-p1)-1);
		if(p1 == -1 || p2 == -1)
			break;
		proj_tmp.title = title;
		proj_tmp.manager = man;
		proj_tmp.disc = desc;
		ret[proj_tmp.title] = proj_tmp;
	//	printf("Manager: %s\n", man.c_str());
	//	printf("Title: %s\n", title.c_str());
	//	printf("Description: %s\n", desc.c_str());
	}
	//	printf("Origin: %s\n", proj.c_str());
	p1 = 0;
	p2 = 0;
	end = task.find_last_of('\'');
	first_loop = true;
//	printf("Origin: %s\n", task.c_str());
	while(p2 < end){
		Task task_tmp;
		Phase ph_tmp;
		ph_tmp.title = "bohemith";
		string ph_title, title, desc, pr_title;
		if(first_loop){
			p1 = task.find('\'');
			first_loop = false;
		}
		else
			p1 = task.find('\'', p2+1);
		p2 = task.find('\'', p1+1); 
		title = task.substr(p1+1, (p2-p1)-1);
		p1 = task.find('\'', p2+1);
		p2 = task.find('\'', p1+1);
		desc = task.substr(p1+1, (p2-p1)-1);
		p1 = task.find('\'', p2+1);
		p2 = task.find('\'', p1+1);
		ph_title = task.substr(p1+1, (p2-p1)-1);

		p1 = task.find('\'', p2+1);
		p2 = task.find('\'', p1+1);
		pr_title = task.substr(p1+1, (p2-p1)-1);
//		printf("Task:\nTitle: %s\nDescription: %s\nPhase: %s\nProject: %s\n", title.c_str(), desc.c_str(), ph_title.c_str(), pr_title.c_str());	
		if(p1 == -1 || p2 == -1)
			break;
		Project p_tmp = ret[pr_title];
		int count = 0;
		if(p_tmp.phases.empty()){
			ph_tmp.title = ph_title;
			p_tmp.phases.push_back(ph_tmp);
		}
		else{
			for(int i = 0; i < p_tmp.phases.size(); ++i)
				if(p_tmp.phases[i].title == ph_title){
					count = i;
					break;
				}
			if(ph_tmp.title == "bohemith"){
				ph_tmp.title = ph_title;
				p_tmp.phases.push_back(ph_tmp);
				count = p_tmp.phases.size()-1;
			}
		}
		task_tmp.title = title;
		task_tmp.disc = desc;
		p_tmp.phases[count].tasks[title] = task_tmp;

		ret[p_tmp.title] = p_tmp; 
		
				

	} 
	p1 = 0;
	p2 = 0;
	first_loop = true;
	end = bug.find_last_of('\'');
	while(p2 < end){
		Bug tmpb;
		int lineNum;
		string fname, desc, t_title, p_title;
		
		if(first_loop){
			p1 = bug.find_first_of('(');
			first_loop = false;
		}	
		else
			p1 = bug.find('(', p2+1);
		p2 = bug.find(',',p1+1);
		lineNum = atoi(bug.substr(p1+1, (p2-p1)-1).c_str());
		
		p1 = bug.find('\'', p2);
		p2 = bug.find('\'', p1+1);
		fname = bug.substr(p1+1, (p2-p1)-1);
		
		p1 = bug.find('\'', p2+1);
		p2 = bug.find('\'', p1+1);
		desc = bug.substr(p1+1, (p2-p1)-1);
	
		p1 = bug.find('\'', p2+1);
		p2 = bug.find('\'', p1+1);
		t_title = bug.substr(p1+1, (p2-p1)-1);

		p1 = bug.find('\'', p2+1);
		p2 = bug.find('\'', p1+1);
		p_title = bug.substr(p1+1, (p2-p1)-1);

		if(p1 == -1 || p2 == -1){
			break;
		}

		tmpb.lineNum = lineNum;
		tmpb.file = fname;
		tmpb.disc = desc;
		
		for(int i = 0; i < ret[p_title].phases.size(); ++i){
			if(ret[p_title].phases[i].tasks.count(t_title))
				ret[p_title].phases[i].tasks[t_title].bugs.push_back(tmpb);
		}	

//		printf("Bugs:\nLine: %d\nDescription: %s\nFile: %s\nTask: %s\n", lineNum, desc.c_str(), fname.c_str(), t_title.c_str());	
	}
	
	p1=0;
	p2=0;
	first_loop = true;
	end = usr.find_last_of('\'');
	while(p2< end){
		User tmpu;
		string uname;
		if(first_loop){
			p1 = usr.find_first_of('\'');
			first_loop = false;
		}
		else
			p1 = usr.find('\'', p2+1);
		p2 = usr.find('\'', p1+1);
		uname = usr.substr(p1+1, (p2-p1)-1);
		if(p1 == -1 || p2 == -1){
			break;
		}
		tmpu.name = uname;
		tmpu.id = 1;
		curr->u_list.push_back(tmpu);
	}

	
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
		return parse_response(response, this);
	}
}

