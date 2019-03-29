//Created by Dakota Martin
#include "data.h"
#include "CmdArgs.h"
#include <stdio.h>
#include <string.h>
using namespace std;

map<string, Project> projects;
User user;
int loc = 0;

void listProjects()
{
	for(auto curr : projects)
	{
		Project p = curr.second;
		if(p.canSee(user))
			cout << p.title << endl;
	}	
}
string selectProject()
{
	while(true)
	{
		string rv = "";
		cin >> rv;
		if((projects.find(rv) != projects.end() || rv == "quit" || rv == "Quit") && projects[rv].canSee(user))
			return projects[rv].title;
		cout << "Not a Project\n Type [quit] or a valid Project: ";
	}
}

string selectTask(Project pr)
{
	while(true)
	{
		string rv = "";
		cin >> rv;
		for(Phase p : pr.phases)
		{
			if(p.tasks.find(rv) != p.tasks.end() || rv == "quit" || rv == "Quit")
			return p.tasks[rv].title;
		}
		cout << "Not a Task\n Type [quit] or a valid task: ";
	}
}

string projMenu(Project p)
{
	vector<string> toCheck = {"Select","Back","Quit"};
	while(true)
	{
		cout << "Would you like to:" << endl;
		cout << "[Select] a task" << endl;
		if(p.manager == user.name)
		{
			toCheck = {"Select","Add","Back","Remove","Quit"};
			cout << "[Add] a task" << endl;
			cout << "[Remove] a task" << endl;
		}
		cout << "[Back] up" << endl;
		cout << "[Quit]" << endl;
		cout << "Type an Option[]: ";
		string rv = "";
		cin >> rv;
		for(string s : toCheck){
			toupper(rv[0]);
			if(s == rv)
				return rv;
		}

	}
	return "";
}
string taskMenu(Project p, Task t)
{
	vector<string> toCheck = {"Back","Quit"};
	while(true)
	{
		cout << "Would you like to:" << endl;
		if(p.manager == user.name)
		{
			toCheck = {"Add","Back","Edit","Change","Assign","Remove","Remove","Quit"};
			cout << "[Edit] the discription" << endl;
			cout << "[Change] the name" << endl;
			cout << "[Assign] an Employee" << endl;
			cout << "[Remove] an Employee" << endl;
			cout << "[Add] a Bug" << endl;
			cout << "[Complete] a Bug" << endl;
		}
		if(t.canEdit(user))
		{
			toCheck = {"Add","Back","Complete","Quit"};
			cout << "[Add] a Bug" << endl;
			cout << "[Complete] a Bug" << endl;
		}
		cout << "[Back] up" << endl;
		cout << "[Quit]" << endl;
		cout << "Type an Option[]: ";
		string rv = "";
		cin >> rv;
		for(string s : toCheck){
			toupper(rv[0]);
			if(s == rv)
				return rv;
		}

	}
	return "";
}

string mainMenu()
{
	bool manager = false;
	for(auto curr : projects)
	{
		Project p = curr.second;
		if(user.name == p.manager)
			manager = true;
	}
	vector<string> toCheck = {"Select","Quit"};
	while(true)
	{
		cout << "Would you like to:" << endl;
		cout << "[Select] a project" << endl;
		if(manager)
		{
			toCheck = {"Select","Add","Back","Remove","Quit"};
			cout << "[Add] a project" << endl;
			cout << "[Remove] a project" << endl;
		}
		cout << "[Quit]" << endl;
		cout << "Type an Option[]: ";
		string rv = "";
		cin >> rv;
		for(string s : toCheck){
			toupper(rv[0]);
			if(s == rv)
				return rv;
		}

	}
	return "";
}

string parseChoice(string choice, Project curr)
{
	string rv = "Continue";
	if(choice == "Select")
	{
		switch(loc)
		{
			case 0:
				rv = selectProject();
				break;
			case 1:
				rv = selectTask(curr);	
				break;
		}
		loc += 1;
	}
	else if(choice == "Add")
	{
		switch(loc)
		{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
		}
	}
	else if(choice == "Remove")
	{
		switch(loc)
		{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
		}
	}
	else if(choice == "Edit")
	{
	}
	else if(choice == "Change")
	{
	}
	else if(choice == "Assign")
	{
	}
	else if(choice == "Complete")
	{
	}
	else if(choice == "Back")
	{
		loc -= 1;
	}
	else if(choice == "Quit")
	{
		return "Quit";
	}
	return rv;
}

void parseArgs(CmdArgs cmd)
{
}

map<string,Project> getData()
{
	Project p;
	p.title = "One";
	p.disc = "the first Project";
	Task t;
	t.title = "Task";
	t.disc = "the first task";
	Bug b;
	b.file = "firstfile.cpp";
	b.lineNum = 1;
	//get data from controller to fill projects data
	//ie.. this function updates the data (atm is only called at begining of program)
}
bool putData(vector<Project> data){
	

}

int main(int argc, char** argv)
{
	projects = getData();
	if(argc > 1)
	{
		CmdArgs cmd(argc, argv);
		parseArgs(cmd);
	}
	else
	{
		bool quit = false;
		while(!quit)
		{
			//LOGIN STUFFS
			//cout << "Login: ";
			//string uname = "";
			//cin >> uname;
			//there is a global variable "user" (fill it in)
			//LOGIN STUFFS
			string str = "Continue";
			Project pCurr;
			Task tCurr;
			while(str != "Quit")
			{
				string choice = "";
				switch(loc)
				{
					case 0:
						listProjects();
						choice = mainMenu();
						str = parseChoice(choice,pCurr);
						if(str != "Continue")
						{
							pCurr = projects[str];
						}
						break;
					case 1:
						cout << pCurr.listTasks();
						choice = projMenu(pCurr);
						str = parseChoice(choice,pCurr);
						if(str != "Continue")
						{
							for(Phase p : pCurr.phases)
							{
								//THIS MIGHT ERROR OUT PLEASE DEBUG
								if(p.tasks.find(str) != p.tasks.end())
									tCurr = p.tasks.at(str);
							}
						}
						break;
					case 2:
						cout << tCurr.asString();
						choice = taskMenu(pCurr, tCurr);
						str = parseChoice(choice,pCurr);
						break;
				}
			}
			
		}
	}

}
