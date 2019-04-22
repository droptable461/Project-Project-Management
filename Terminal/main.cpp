#include <iostream>
#include "conn.h"
using namespace std;

int main()
{
	Task t;
	t.title = "task1";
	t.disc = "description1";
	Conn *c = new Conn("http://127.0.0.1:5000");

	cout<< c->get_host() << endl;

	if(c->post_request(t))
		cout<<"Sent Message"<<endl;
	else
		cout<<"Message Not Sent" <<endl;
	return 0;

}
