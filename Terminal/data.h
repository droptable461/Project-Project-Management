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
		           //could add more but im not sure what kind of information we should have
		
		string asString();
};
class Task{
	public:
		vector<Bug> bugs;    //bugs associated to the task
		set<User> users;    //Users assigned to the task
		string title;      //the name of the task
		string disc;      //general discription of the task
		string date;

		Task();
		Task(string t, string d);

		string asString();
		string listUsers();
		string listBugs();
		bool canEdit(User u);
};

class Phase{
	public:
		map<string,Task> tasks; //a map of task title to task (makes my life easier)
		string title;
		Phase();
		string listTasks();

}

class Project{
	public:
		vector<Phase> phases;
		//this would not nessaserally be displayed as its just for figuring out who would be able to see this
		string manager; //this could be an int/id
		string title;  //the name of the project
		string disc;  //the discription of the project

		string listTasks();
		string listUsers();
		string asString();
		bool canSee(User u);
};

