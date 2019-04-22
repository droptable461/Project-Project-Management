#include <iostream>
#include "conn.h"
using namespace std;

int main()
{
	User u;
	Project p;
	Phase ph;
	Task t;
	Bug b;
	u.name = "lewisbr";
	p.title = "project1";
	p.disc = "description1";
	ph.title = "phase1";
	b.lineNum = 10;
	b.file = "bug1";
	b.disc = "description1";
	t.title = "task1";
	t.disc = "description1";
	Conn *c = new Conn("http://127.0.0.1:5000");
//USER TEST
	cout<<"Testing USER Post........";
	if(c->post_request(u))
		cout<<"SENT" << endl;
	else
		cout<<"FAILED" << endl;
//PROJECT TEST
	cout<<"Testing PROJECT Post.....";
	if(c->post_request(p, 0);
		cout<<"SENT" << endl;
	else
		cout<<"FAILED" << endl;
//PHASE TEST
	cout<< "Testing PHASE Post......";
	if(c->post_request(ph,"project1"))
		cout<<"SENT" << endl;
	else
		cout<<"FAILED" <<endl;
//TASK TEST
	cout<< "Testing TASK Post.......";
	if(c->post_request(t,"project1")){
		cout<< "SENT" << endl;
	}
	else
		cout<< "FAILED" << endl;
//BUG TEST
	cout<<"Testing BUG Post.........";
	if(c->post_request(b, "task1" );
		cout<< "SENT" << endl;
	else
		cout<<"FAILED"<< endl;
}
