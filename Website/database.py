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
			(manager text, p_id serial, title text, description text)''')
	c.execute('''CREATE TABLE task
			(t_id int, title text, description text)''')
	c.execute('''CREATE TABLE bug
			(b_id serial, t_id int, line int, fname text, description text)''')
	c.execute('''CREATE TABLE user
			(uname text, u_id)''')
	c.execute('''CREATE TABLE uttable
			(u_id, t_id)''')
	conn.commit()

def main():
	clearDatabase()
	createDatabase()
	

if __name__ == "__main__":
	main()
