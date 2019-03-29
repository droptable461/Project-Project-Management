//Created by: Dakota Martin March,20,2019

#include <vector>
#include <iostream>
#include <set>
#include <map>
using namespace std;

class User{
	public:
		string name;
		int id;
};

class Bug{
	public:
		int lineNum;  //the line number that the bug is on
		string file; //the file that the bug is located in
		string disc;//a short discription of the bug
		bool completed;           //could add more but im not sure what kind of information we should have
		
		string asString();
};
class Task{
	public:
		vector<Bug> bugs;    //bugs associated to the task
		set<User> users;    //Users assigned to the task
		string title;      //the name of the task
		string disc;      //general discription of the task

		string asString();
		string listUsers();
		string listBugs();
		bool canEdit(User u);
};

class Phase{
	public:
		map<string,Task> tasks; //a map of task title to task (makes my life easier)
		string title;

		string listTasks();


};

class Project{
	public:
		vector<Phase> phases;//a list of phases that holds the tasks
		//this would not nessaserally be displayed as its just for figuring out who would be able to see this
		string manager; //this could be an int/id
		string title;  //the name of the project
		string disc;  //the discription of the project

		void assignPhase(Task t,Phase p);
		string listTasks();
		string listUsers();
		string asString();
		bool canSee(User u);
};


void Project::assignPhase(Task tas, Phase phas)
{
	for(Phase p : phases)
	{
		p.tasks.erase((tas.title));
	}
	phas.tasks[tas.title] = tas;
}
bool Project::canSee(User u)
{
	for(Phase p : phases)
	{
		for(auto t : p.tasks)
		{
			for(User us : t.second.users)
			{
				if(u.id == us.id && u.name == us.name)
				{
					return true;
				}
			}
		}
	}
	return false;
}
string Project::listTasks()
{
	string rv = "";
	for(Phase p : phases)
	{
		rv += p.listTasks();
	}
	return rv;
}

string Project::listUsers()
{
	string rv = "";
	set<int> all;
	for(Phase p : phases)
	{
		for(auto t : p.tasks)
		{
			for(User u : t.second.users)
			{
				if(all.find(u.id) != all.end())
				{
					rv += u.name + "\n";
					all.insert(u.id);
				}
			}
		}
			
	}
	return rv;
}

string Project::asString()
{
	string rv = "";
	rv += title + "\n";
	int tasks = 0;
	for(Phase p : phases)
	{
		tasks += p.tasks.size();
	}
	rv += "Number of Tasks: " + to_string(tasks) + "\n";
	rv += disc + "\n";
	return rv;
}

bool Task::canEdit(User u)
{
	for(User us : users)
	{
		if(us.id == u.id && us.name == u.name)
			return true;
	}
	return false;
}

string Task::asString()
{
	string rv = "";
	rv += title + "\n";
	rv += "Number of Users: " + to_string(users.size()) + "\n";
	rv += disc + "\n";
	return rv;
}

string Task::listUsers()
{
	string rv = "";
	for(User u : users)
	{
		rv += u.name + "\n";
	}
	return rv;
}

string Task::listBugs()
{
	string rv = "";
	for(Bug b : bugs)
	{
		rv += b.asString();
	}
	return rv;
}

string Bug::asString()
{
	string rv = "";
	rv += "File: " + file + "\n";
	rv += "Line Number: " + to_string(lineNum) + "\n";
	rv += disc + "\n\n";
	return rv;
}

string Phase::listTasks()
{
	string rv = "";
	for(auto t : tasks)
	{
			rv += t.second.title + "\n";
	}
	return rv;
}
