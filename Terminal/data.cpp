#include "data.h"

using namespace std;

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

Project::Project(string u, string t, string d)
{
	title = t;
	disc = d;
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
Task::Task(){}
Task::Task(string t, string d)
{
	title = t;
	disc = d;
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

Bug::Bug(int ln, string f, string d)
{
	lineNum = ln;
	completed = false;
	file = f;
	disc = d;
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

User::User(string n, int i)
{
	name = n;
	id = i;
}

