To run the database : shows usernames and what is in the database

	python3 database.py
	-type this before you type python3 app.py


To run the server: 

	type in python3 app.py
	-go onto browser
	-type in localhost:5000/git
	-once you see "sec" go onto terminal and you will see how we were able to do git

To unit test:
	
	python3 unit_test.py 
	-if you hit tab after "python3" and it should autofill the file


In the login page: 
	-to login, you must type in one of the usernames from our database and click the "log in" button 
	-once logged in, the home page will display

In the home page: 
	-the home page simply displays a table of each member of our group and what they were assigned to during our project (ex: allie) 
	-On the right of the top navigation bar, you should see "Welcome, " with the current users name displayed (ex: Welcome, allie)
	-"Welcome,allie" for example, only shows up when you click on a different page than the home page and then you return to the home page 

In the my projects page (adding a project): 
	-click the "My Projects" tab on the top navigation bar
	-You will see an "Add Project" button and a test project links on the side navigation bar
	-for example, if you click on the "testProj2" link on the side navigation bar, it should display to do, doing, and done columns with user's tasks inside of them   
	-when you click on the "testProj2" link on the side navigation bar, you will also see "Add Column" and "Add Task" buttons 
	-To add a project, simply click the "Add Project" button while you are in the "testProj2" page
	-type the manager's name in the "Manager" text box
	-Next, type the project name in the "Project Title" text box 
	-Lastly, type a description of project in the text box underneath "What is the description of the project?"
	-When you are done, click "Submit"
	-After submitting, you will only see the added project when you click on the first test project link

In the my projects page (adding a task):
	-To add a task, simply click the "Add Task" button 
	-type the name of the title in the "Task Title" text box
	-then, type a description of your task in the text box underneath "What is the description of the task?"
	-lastly, type which phase you want the task in within the "Phase" text box 
	-When you are done, click "Submit"
	-After submitting, the task should show up in the particular phase column that you requested in the text box

In the my projects page (adding a column):
	-To add a column, simply click the "Add Column" button
	-type the name of the column you wish to add beside the to do, doing, and done columns
	-Click the "Submit" button when you're done
	-After submitting, refresh the page and you will see the added column
	-When you add a column, all the tasks will be listed every time you add a column

In the timeline page: 
	-click the "Timeline" tab on the top navigation bar
	-On the timeline page, you should see a vertical timeline that displayed what we did for this project at different times (scroll down to see what we did at different stage)

In the how to use page: 
	-click the "How To Use" tab on the top navigation bar
	-On the how to use page, you should see accordion tabs that when clicked, display what each of our pages mean
	-For example, when you hover over "The Login Page" and click on it, a description of that page should display underneath that tab
	-the how to use page remains the same until you click a specific task on the my projects page, then the how to use becomes a page listing the different attributes of a tab

In the log out page: 
	-click the "Log Out" tab on the top navigation bar 	
	-when you click on the "Log Out" tab, you will be directed back to the log in page
