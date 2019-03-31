#!bin/python
import sqlite3
conn = sqlite3.connect('database.db')
def clearDatabase():
	c = conn.cursor()
	c.execute('''DROP TABLE IF EXISTS project''')
	c.execute('''DROP TABLE IF EXISTS task''')
	c.execute('''DROP TABLE IF EXISTS bug''')
	c.execute('''DROP TABLE IF EXISTS user''')
def createDatabase():
	c = conn.cursor()
	c.execute('''CREATE TABLE project(manager TEXT, title TEXT PRIMARY KEY UNIQUE, description TEXT, tID REFERENCES task(task_id))''')
	c.execute('''CREATE TABLE task(task_id INTEGER PRIMARY KEY UNIQUE AUTOINCREMENT, title TEXT, description TEXT, phase TEXT, bug_id REFERENCES bug(b_id))''')
	c.execute('''CREATE TABLE bug(b_id PRIMARY KEY UNIQUE AUTOINCREMENT, line INTEGER, fname TEXT, description TEXT)''')
	c.execute('''CREATE TABLE user(uname text PRIMARY KEY UNIQUE, proj TEXT REFERENCES project(title), tasks REFERENCES task(task_id))''')
	conn.commit()
def populateDatabase():
        c = conn.cursor()
        c.execute('''INSERT INTO user (uname) VALUES ('thomas')''')
        c.execute('''INSERT INTO user (uname) VALUES ('tejas')''')
        c.execute('''INSERT INTO user (uname) VALUES ('allie')''')
        c.execute('''INSERT INTO user (uname) VALUES ('breonna')''')
        c.execute('''INSERT INTO user (uname) VALUES ('dakota')''')
        c.execute('''INSERT INTO user (uname) VALUES ('brandon')''')
        c.execute('''INSERT INTO user (uname) VALUES ('dymacek')''')
        conn.commit()

def main():
	clearDatabase()
	createDatabase()
        populateDatabase()

if __name__ == "__main__":
	main()
