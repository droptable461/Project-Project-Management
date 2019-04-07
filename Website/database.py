#!bin/python
import sqlite3
conn = sqlite3.connect('database.db')
def clearDatabase():
	c = conn.cursor()
	c.execute("""DROP TABLE IF EXISTS project""")
	c.execute("""DROP TABLE IF EXISTS task""")
	c.execute("""DROP TABLE IF EXISTS bug""")
	c.execute("""DROP TABLE IF EXISTS user""")
def createDatabase():
	c = conn.cursor()
	c.execute("""CREATE TABLE project(manager TEXT, title TEXT, description TEXT, tasks REFERENCES task(task_id),PRIMARY KEY(title,tasks))""")
	c.execute("""CREATE TABLE task(task_id INTEGER, title TEXT, description TEXT, phase TEXT, bug_id REFERENCES bug(b_id), PRIMARY KEY(task_id,title))""")
	c.execute("""CREATE TABLE bug(b_id PRIMARY KEY, line INTEGER, fname TEXT, description TEXT)""")
	c.execute("""CREATE TABLE user(uname text, proj TEXT REFERENCES project(title), tasks REFERENCES task(task_id), PRIMARY KEY(uname, tasks))""")
	conn.commit()
def populateDatabase():
        c = conn.cursor()
        c.execute("""INSERT INTO user (uname,proj,tasks) VALUES ('thomas','testProj1',2)""")
        c.execute("""INSERT INTO user (uname,proj,tasks) VALUES ('thomas','testProj1',3)""")
        c.execute("""INSERT INTO user (uname,proj,tasks) VALUES ('thomas','testProj2',5)""")

        c.execute("""INSERT INTO user (uname) VALUES ('tejas')""")
        c.execute("""INSERT INTO user (uname) VALUES ('allie')""")
        c.execute("""INSERT INTO user (uname) VALUES ('breonna')""")
        c.execute("""INSERT INTO user (uname) VALUES ('dakota')""")
        c.execute("""INSERT INTO user (uname) VALUES ('brandon')""")
        c.execute("""INSERT INTO user (uname) VALUES ('dymacek')""")

        c.execute("""INSERT INTO project (manager,title,description,tasks) VALUES ('Tman1','testProj1','abcdefghijklmnop',1)""")
        c.execute("""INSERT INTO project (manager,title,description,tasks) VALUES ('Tman1','testProj1','abcdefghijklmnop',2)""")
        c.execute("""INSERT INTO project (manager,title,description,tasks) VALUES ('Tman1','testProj1','abcdefghijklmnop',3)""")
        c.execute("""INSERT INTO project (manager,title,description,tasks) VALUES ('Tman1','testProj2','qrstuvwxyz',4)""")
        c.execute("""INSERT INTO project (manager,title,description,tasks) VALUES ('Tman1','testProj2','qrstuvwxyz',5)""")

        c.execute("""INSERT INTO task(task_id,title,description,phase) VALUES(1,'testTask1','onetwothree','todo')""")
        c.execute("""INSERT INTO task(task_id,title,description,phase) VALUES(2,'testTask2','fourfive','todo')""")
        c.execute("""INSERT INTO task(task_id,title,description,phase) VALUES(3,'testTask3','sixseven','todo')""")
        c.execute("""INSERT INTO task(task_id,title,description,phase) VALUES(4,'testTask4','eightnine','todo')""")
        c.execute("""INSERT INTO task(task_id,title,description,phase) VALUES(5,'testTask5','teneleven','todo')""")
        c.execute("""INSERT INTO task(task_id,title,description,phase) VALUES(6,'testTask6','twelvethirteen','todo')""")

        conn.commit()

def newproj():
    man = 'Tman6'
    title = 'testproj7'
    des = 'testtesttest'
    db = conn.cursor()
    db.execute("INSERT INTO project (manager,title,description) VALUES(?,?,?)",(man,title,des))

    conn.commit()

    p = [row[0] for row in db.execute("""SELECT * FROM project""").fetchall()]
    for j in range(len(p)):
        print(p[j])


def retproj():
    c = conn.cursor()
    p = [row[0] for row in c.execute("""SELECT DISTINCT proj FROM user WHERE uname = ('thomas')""").fetchall()]
    for j in range(len(p)):
        print(p[j])

    conn.commit()

def rettask():
    c = conn.cursor()
    variable = [row[0] for row in c.execute("""SELECT tasks FROM user NATURAL JOIN project WHERE uname = ('thomas') AND title = ('testProj1')""").fetchall()]
    for i in range(len(variable)):
        print(c.execute("""SELECT * FROM task WHERE task_id = ?""", (variable[i],)).fetchall())

    conn.commit()

def main():
        clearDatabase()
        createDatabase()
        populateDatabase()
        retproj()
        rettask()
        newproj()
        
if __name__ == "__main__":
	main()
