#include "data.h"

using namespace std;

void Project::assignPhase(Task tas, string phas)
{
	if(phases.size() > 0)
	{
		for(Phase p : phases)
		{
			p.tasks.erase((tas.title));
		}
		for(Phase p : phases)
		{
			if(phas == p.title)
			{
				p.tasks[tas.title] = tas;
				return;
			}
		}
	}
	Phase p;
	p.title = phas;
	p.tasks[tas.title] = tas;
	phases.push_back(p);
}
bool Project::canSee(User u)
{
	if(u.name == manager)
	{
		return true;
	}
	if(phases.size() <= 0)
	{
		return false;
	}
	for(Phase p : phases)
	{
		if(p.tasks.size() <= 0)
		{
			return false;
		}

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
string Project::listPhases()
{
	if(phases.size() <= 0)
	{
		return "No Phases.\n";
	}
	string rv = "";
	for(Phase p : phases)
	{
		rv += p.title + "\n";
	}
	return rv;
}
string Project::listTasks()
{
	if(phases.size() <= 0)
	{
		return "No tasks..\n";
	}
	string rv = "";
	for(Phase p : phases)
	{
		rv += p.title + ":\n";
		rv += p.listTasks();
	}
	return rv;
}

string Project::listUsers()
{
	string rv = "";
	set<int> all;
	if(phases.size() <= 0)
		return "No users.\n";
	for(Phase p : phases)
	{
		if(p.tasks.size() <= 0)
			return "No users.\n";
		for(auto t : p.tasks)
		{
			if(t.second.users.size() <= 0)
				return "No users.\n";
			for(User u : t.second.users)
			{
				if(all.find(u.id) == all.end())
				{
					rv += u.name + "\n";
					all.insert(u.id);
				}
			}
		}
			
	}
	return rv;
}

Project::Project()
{
	Phase p;
	p.title = "To do";
	phases.push_back(p);
}
Project::Project(string u, string t, string d)
{
	Phase p;
	p.title = "To do";
	phases.push_back(p);
	title = t;
	disc = d;
}

void Project::addTask(Task t)
{
	phases[0].tasks.insert(pair<string,Task>(t.title, t));
}
string Project::asString()
{
	string rv = "";
	rv += title + "\n";
	int tasks = 0;
	if(phases.size() > 0)
	{
		for(Phase p : phases)
		{
			tasks += p.tasks.size();
		}
	}
	rv += "Number of Tasks: " + to_string(tasks) + "\n";
	rv += disc + "\n";
	return rv;
}

bool Task::canEdit(User u)
{
	if(users.size() <= 0)
		return false;
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
	if(users.size() <= 0)
		return "No users.\n";
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
	if(bugs.size() <= 0)
		return "No Bugs.\n";
	for(Bug b : bugs)
	{
		rv += b.asString();
	}
	return rv;
}
Bug::Bug(){}
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

Phase::Phase()
{

}
string Phase::listTasks()
{
	string rv = "";
	//cout << "DEBUG: " << tasks.size() << endl;
	if(tasks.size() <= 0)
		return "No tasks.\n";
	for(auto t : tasks)
	{
			rv += t.second.title + "\n";
	}
	return rv;
}
User::User(){}
User::User(string n, int i)
{
	name = n;
	id = i;
}

