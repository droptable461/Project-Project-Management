#!bin/python
import sqlite3
conn = sqlite3.connect('database.db')
def clearDatabase():
	c = conn.cursor()
	c.execute("""DROP TABLE IF EXISTS project""")
	c.execute("""DROP TABLE IF EXISTS task""")
	c.execute("""DROP TABLE IF EXISTS bug""")
	c.execute("""DROP TABLE IF EXISTS user""")
	c.execute("""DROP TABLE IF EXISTS columns""")
def createDatabase():
        c = conn.cursor()
        c.execute("""CREATE TABLE project(  manager TEXT,
                                            title TEXT,
                                            description TEXT,
                                            PRIMARY KEY(title))""")

        c.execute("""CREATE TABLE task( task_id INTEGER,
                                        title TEXT, 
                                        description TEXT,
                                        phase TEXT,
                                        dateMade DATE,
                                        PRIMARY KEY(task_id))""")
        c.execute("""CREATE TABLE bug(  t_id REFERENCES task(task_id),
                                        line INTEGER,
                                        fname TEXT,
                                        description TEXT)""")

        c.execute("""CREATE TABLE user( uname text,
                                        proj TEXT REFERENCES project(title),
                                        tasks REFERENCES task(task_id),
                                        PRIMARY KEY(uname, tasks))""")

        c.execute("""CREATE TABLE columns(proj TEXT REFERENCES project(title),coll TEXT, task_id REFERENCES task(task_id))""")

        conn.commit()
def populateDatabase():
        

        c = conn.cursor()
        
        c.execute("""INSERT INTO user (uname,proj,tasks) VALUES ('allie','testProj1',2)""")
        c.execute("""INSERT INTO user (uname,proj,tasks) VALUES ('thomas','testProj1',3)""")
        c.execute("""INSERT INTO user (uname,proj,tasks) VALUES ('thomas','testProj2',5)""")

        c.execute('''INSERT INTO bug (t_id, line, fname, description) VALUES ('2', '10', 'fml', 'blah blah')''')

        c.execute("""INSERT INTO user (uname,proj) VALUES ('tejas','testProj2')""")
        c.execute("""INSERT INTO user (uname,proj) VALUES ('allie','testProj2')""")
        c.execute("""INSERT INTO user (uname,proj) VALUES ('breonna','testProj2')""")
        c.execute("""INSERT INTO user (uname,proj) VALUES ('dakota','testProj2')""")
        c.execute("""INSERT INTO user (uname,proj) VALUES ('brandon','testProj2')""")
        c.execute("""INSERT INTO user (uname,proj) VALUES ('dymacek','testProj2')""")

        c.execute("""INSERT INTO project (manager,title,description) VALUES ('Tman1','testProj1','abcdefghijklmnop')""")
        c.execute("""INSERT INTO project (manager,title,description) VALUES ('Tman1','testProj2','qrstuvwxyz')""")

        c.execute("""INSERT INTO columns(proj,coll) VALUES ('testProj2','todo')""")
        c.execute("""INSERT INTO columns(proj,coll) VALUES ('testProj2','doing')""")
        c.execute("""INSERT INTO columns(proj,coll) VALUES ('testProj2','done')""")

        c.execute("""INSERT INTO task(title,description) VALUES('testTask1','Updating the myproj page')""")
        c.execute("""INSERT INTO task(title,description) VALUES('testTask2','Updating the myproj page')""")
        c.execute("""INSERT INTO task(title,description) VALUES('testTask3','sixseven')""")
        c.execute("""INSERT INTO task(title,description) VALUES('testTask4','eightnine')""")
        c.execute("""INSERT INTO task(title,description) VALUES('testTask5','teneleven')""")
        c.execute("""INSERT INTO task(title,description) VALUES('testTask6','twelvethirteen')""")
        
        c.execute("""INSERT INTO columns(proj,coll,task_id) VALUES ('testProj2','todo','1')""")
        c.execute("""INSERT INTO columns(proj,coll,task_id) VALUES ('testProj2','todo','2')""")
        c.execute("""INSERT INTO columns(proj,coll,task_id) VALUES ('testProj2','doing','3')""")
        c.execute("""INSERT INTO columns(proj,coll,task_id) VALUES ('testProj2','done','4')""")
        c.execute("""INSERT INTO columns(proj,coll,task_id) VALUES ('testProj2','doing','5')""")
        c.execute("""INSERT INTO columns(proj,coll,task_id) VALUES ('testProj2','done','6')""")

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
    print (p)
    for j in range(len(p)):
        print(p[j])


def rettask():
    c = conn.cursor()
    variable = [row[0] for row in c.execute("""SELECT tasks FROM user NATURAL JOIN project WHERE uname = ('thomas') AND title = ('testProj1')""").fetchall()]
    for i in range(len(variable)):
        print(c.execute("""SELECT * FROM task WHERE task_id = ?""", (variable[i],)).fetchall())


def main():
        clearDatabase()
        createDatabase()
        populateDatabase()
        retproj()
        rettask()
        newproj()

if __name__ == "__main__":
	main()
