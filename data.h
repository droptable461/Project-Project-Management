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
		char pos; //can be changed but im thinking along the lines of m:manager, e:employee, c:client..
};

class Bug{
	public:
		int lineNum;  //the line number that the bug is on
		string file; //the file that the bug is located in
		string disc;//a short discription of the bug
		           //could add more but im not sure what kind of information we should have
		
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
};

class Project{
	public:
		map<string,Task> tasks; //a map of task title to task (makes my life easier)
		//this would not nessaserally be displayed as its just for figuring out who would be able to see this
		string manager; //this could be an int/id
		string title;  //the name of the project
		string disc;  //the discription of the project

		string listTasks();
		string listUsers();
		string asString();
};

string Project::listTasks()
{
	string rv = "";
	for(Task t : tasks)
	{
		rv += t.title + "\n";
	}
	return rv;
}

string Project::listUsers()
{
	string rv = "";
	set<int> all;
	for(Task t : tasks)
	{
		for(User u : t.users)
		{
			if(all.find(u.id) != all.end())
			{
				rv += u.name + "\n";
				all.insert(u.id);
			}
		}
			
	}
	return rv;
}

string Project::asString()
{
	string rv = "";
	rv += title + "\n";
	rv += "Number of Tasks: " + to_string(tasks.size()) + "\n";
	rv += disc + "\n";
	return rv;
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
