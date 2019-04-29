TERMINAL:
	-run the executable named (whatever you name it brandon)
	-currently is not connected to the database/controller in any way
		~use hardcoded user "admin" to login (has manager privelage to all projects)
	-currently the only commands that work would be the add commands for the project/task
		~this is just so you can move to the other menus to see them
		~use Select command to move to other menus
COMPILE WITH:
	g++ terminal.cpp conn.cpp data.cpp -lcurl -o term
RUN WITH:
	./term
TESTING WITH MAIN.CPP
	STEP ONE:
		compile with: g++ main.cpp conn.cpp data.cpp -lcurl
	STEP TWO:
		run the Website/app.py server locally
	STEP THREE:
		run with: ./a.out
