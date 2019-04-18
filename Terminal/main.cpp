#include <iostream>
#include "conn.h"
using namespace std;

int main()
{
	Task t;
	t.title = "task1";
	t.disc = "description1";
	Conn *c = new Conn("127.0.0.1:5000/task", 5000);
	c->get_server_info();
	if(c->ping_server())
		cout<<"Connected"<< endl;
	else
		cout<<"Error Connecting..."<<endl;

	if(c->post_request(t))
		cout<<"Sent Message"<<endl;
	else
		cout<<"Message Not Sent" <<endl;
	return 0;

}
