//Created by Dakota Martin
#include "data.h"
#include "CmdArgs.h"
#include <stdio.h>
using namespace std;

map<string, Project> projects;
User user;

void listProjects()
{
	for(Project p : projects)
	{
		if(p.canSee(user))
			cout << p.title << endl;
	}	
}
Project selectProject()
{
	while(true)
	{
		string rv = "";
		cin >> rv;
		if((projects.find(rv) != projects.end() || rv == "quit") && projects[rv].canSee(user))
			return projects[rv];
		cout << "Not a Project\n Type [quit] or a valid Project: ";
	}
}

string selectTask(Project p)
{
	while(true)
	{
		string rv = "";
		cin >> rv;
		if(p.tasks.find(rv) != p.tasks.end() || rv == "quit")
			return p.tasks[rv];
		cout << "Not a Task\n Type [quit] or a valid task: ";
	}
}

string projMenu(Project p)
{
	vector<string> toCheck = {"Select","select","Back","back","Quit","quit"};
	while(true)
	{
		cout << "Would you like to:" << endl;
		cout << "[Select] a task" << endl;
		if(p.manager == user.name)
		{
			toCheck = {"Select","select","Add","add","Back","back","Remove","remove","Quit","quit"}
			cout << "[Add] a task" << endl;
			cout << "[Remove] a task" << endl;
		}
		cout << "[Back] up" << endl;
		cout << "[Quit]" << endl;
		cout << "Type an Option[]: ";
		string rv = "";
		cin >> rv;
		if(toCheck.find(rv) != toCheck.end())
			return rv;

	}
	return "";
}
string taskMenu(Project p, Task t)
{
	vector<string> toCheck = {"Select","select","Back","back","Quit","quit"};
	while(true)
	{
		cout << "Would you like to:" << endl;
		cout << "[Select] a task" << endl;
		if(p.manager == user.name)
		{
			toCheck = {"Select","select","Add","add","Back","back","Edit","edit","Change","change","Assign","assign","UnAssign","unassign","Remove","remove","Quit","quit"}
			cout << "[Edit] the discription" << endl;
			cout << "[Change] the name" << endl;
			cout << "[Assign] an Employee" << endl;
			cout << "[UnAssign] an Employee" << endl;
			cout << "[Add] a Bug" << endl;
			cout << "[Remove] a Bug" << endl;
		}
		if(t.canEdit(user))
		{
			//more options
		}
		cout << "[Back] up" << endl;
		cout << "[Quit]" << endl;
		cout << "Type an Option[]: ";
		string rv = "";
		cin >> rv;
		if(toCheck.find(rv) != toCheck.end())
			return rv;

	}
	return "";
}

void parseArgs(CmdArgs cmd)
{
}

vector<Project> getData()
{
	//get data from controller to fill projects data
	//ie.. this function updates the data (atm is only called at begining of program)
}

int main(int argc, char** argv)
{
	projects = getData();
	if(argc > 1)
	{
		CmdArgs cmd(argv);
		parseArgs(cmd);
	}
	else
	{
	}

}
