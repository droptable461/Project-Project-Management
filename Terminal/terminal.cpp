//Created by Dakota Martin
//#include <sqlite3.h>
#include "data.h"
#include "lib/CmdArgs.h"
#include <stdio.h>
#include <string.h>
using namespace std;

map<string, Project> projects;
User user;
int loc = 0;

void check(int i)
{
	cout << "Check["<<i<<"]"<<endl;
}
void listProjects()
{
	if(projects.size() <= 0)
	{
		cout << "No projects are set up." << endl;
		return;
	}
	for(auto curr : projects)
	{
		Project p = curr.second;
		if(p.canSee(user) || user.id == -1)
			cout << p.title << endl;
	}	
}

string selectProject()
{
	while(true)
	{
		string rv = "";
		getline(cin,rv);
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
		getline(cin, rv);
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
	vector<string> toCheck = {"Select","Back","Quit","Move"};
	while(true)
	{
		cout << "Would you like to:" << endl;
		cout << "[Select] a task" << endl;
		if(p.manager == user.name || user.id == -1)
		{
			toCheck = {"Select","Add","Back","Remove","Quit","Move","Create","Erase"};
			cout << "[Add] a task" << endl;
			cout << "[Remove] a task" << endl;
			cout << "[Create] a Phase" << endl;
			cout << "[Erase] a Phase" << endl;
		}
		cout << "[Move] a task to a phase" << endl;
		cout << "[Back] up" << endl;
		cout << "[Quit]" << endl;
		cout << "Type an Option[]: ";
		string rv = "";
		getline(cin,rv);
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
	vector<string> toCheck = {"Back","Quit","Move"};
	while(true)
	{
		cout << "Would you like to:" << endl;
		if(p.manager == user.name || user.id == -1)
		{
			toCheck = {"Back","Edit","Change","Assign","Remove","Report","Quit"};
			cout << "[Edit] the discription" << endl;
			cout << "[Change] the name" << endl;
			cout << "[Assign] an Employee" << endl;
			cout << "[Remove] an Employee" << endl;
			cout << "[Report] a Bug" << endl;
			cout << "[Complete] a Bug" << endl;
		}
		if(t.canEdit(user))
		{
			toCheck = {"Report","Back","Complete","Quit","Move"};
			cout << "[Report] a Bug" << endl;
			cout << "[Complete] a Bug" << endl;
		}
		cout << "[Back] up" << endl;
		cout << "[Quit]" << endl;
		cout << "Type an Option[]: ";
		string rv = "";
		getline(cin,rv);
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
	if(projects.size() > 0)
	{
		for(auto curr : projects)
		{
			Project p = curr.second;
			if(user.name == p.manager)
				manager = true;
		}
	}
	else if(user.name == "admin")
		manager = true;
	else
		manager = false;
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
		getline(cin,rv);
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
		cout << "Title: ";
		string title = "";
		getline(cin,title);
		cout << "Description: " << endl;
		string disc = "";
		getline(cin,disc);
		
		switch(loc)
		{
			case 0:
			{
				check(2);
				Project p(user.name, title, disc);
				projects.insert(pair<string,Project>(p.title, p));
				check(3);
				break;
			}
			case 1:
			{
				Task t(title, disc);
				projects[curr.title].addTask(t);
				break;
			}
		}
		check(40000);
	}
	else if(choice == "Remove")
	{
		/*if(projects.size() <= 0)
		{
			cout << "There are no projects to remove" << endl;
			return rv;
		}
		cout << "Title: ";
		string title = "";
		cin >> title;

		switch(loc)
		{
			case 0:
				for(auto p : projects)
				{
					if(p.second.title == title)
					{
						projects.erase(title);
						return rv;
					}
				}
				cout << "Not a valid project title, no project was deleted" << endl;
				break;
			case 1:
				for(
				break;
			case 2:
				break;
		}*/
	}
	else if(choice == "Create")
	{
	}
	else if(choice == "Erase")
	{
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
	check(3);
	return rv;
}

void parseArgs(CmdArgs cmd)
{
}

map<string,Project> getData()
{
/*	sqlite3 * db;
	int rc;
	rc = sqlite3_open("../Website/database.db", &db);
*/	
	
		
	//get data from controller to fill projects data
	//ie.. this function updates the data (atm is only called at begining of program)
}
bool putData(vector<Project> data){
	

}

int main(int argc, char** argv)
{
	check(0);
	//projects = getData();
	if(argc > 1)
	{
	//	CmdArgs cmd(argc,argv);
	//	parseArgs(cmd);
	}
	else
	{
		//LOGIN STUFFS
		check(-1);
		cout << "Login: ";
		string uname = "";
		getline(cin, uname);
		if(uname == "admin")
		{
			User u;
			u.name = uname;
			u.id = -1;
			user = u;
			
		}
		else
		{
			cout << "Not a user" << endl;
			return 0;
		}
		check(-2);
		//there is a global variable "user" (fill it in)
		//LOGIN STUFFS
		string str = "Continue";
		Project pCurr;
		Phase fCurr;
		Task tCurr;
		while(str != "Quit")
		{
			string choice = "";
			switch(loc)
			{
				case 0:
					check(5);
					listProjects();
					choice = mainMenu();
					str = parseChoice(choice,pCurr);
					check(8);
					if(str != "Continue" || str != "Quit")
					{
						check(22);
						pCurr = projects[str];
					}
					break;
				case 1:
					check(4);
					cout << pCurr.listTasks();
					choice = projMenu(pCurr);
					str = parseChoice(choice,pCurr);
					if(str != "Continue"|| str != "Quit")
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
