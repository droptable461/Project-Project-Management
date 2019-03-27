#!bin/python
import sqlite3
conn = sqlite3.connect('database.db')
def clearDatabase():
	c = conn.cursor()
	c.execute('''DROP TABLE IF EXISTS project''')
	c.execute('''DROP TABLE IF EXISTS task''')
	c.execute('''DROP TABLE IF EXISTS bug''')
	c.execute('''DROP TABLE IF EXISTS user''')
	c.execute('''DROP TABLE IF EXISTS uttable''')
def createDatabase():
	c = conn.cursor()
	c.execute('''CREATE TABLE project
			(manager text, title text, description text)''')
	c.execute('''CREATE TABLE task
			(p_id int, title text, description text)''')
	c.execute('''CREATE TABLE bug
			(t_id int, line int, fname text, description text)''')
	c.execute('''CREATE TABLE user
			(uname text)''')
	c.execute('''CREATE TABLE uttable
			(u_id int, t_id int)''')
	conn.commit()
def fillDatabase():
    c = conn.cursor()
    c.execute('''INSERT INTO user(uname)
                       VALUES('lewis1')''')
    c.execute('''INSERT INTO user(uname)
                        VALUES('lewis2')''')
    c.execute('''INSERT INTO project(manager, title, description)
                        VALUES('lewis1', 'Project 1', 'Test project 1')''')
    c.execute('''INSERT INTO task(p_id, title, description)
                        VALUES(0, 'Do this thing', 'this thing needs done!')''')
    c.execute('''INSERT INTO task(p_id, title, description)
                        VALUES(0, 'Do more things', 'Completing tasks is crucial to success!')''')
    c.execute('''INSERT INTO task(p_id, title, description)
                        VALUES(0, 'Do all of the things', 'Finish your work to advance')''')
    c.execute('''INSERT INTO uttable(u_id , t_id) VALUES (1, 2)''')

    conn.commit()
def main():
	clearDatabase()
	createDatabase()
        fillDatabase()
	

if __name__ == "__main__":
	main()
