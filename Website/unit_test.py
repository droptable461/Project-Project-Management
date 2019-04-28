from flask import Flask, request, g, redirect, escape, render_template, current_app, session
import unittest
import requests, json,time
import app
from app import app,hello, connectDB, getDB,login, myproj,addCol, retCol,retTask,addProj,addTask, timeline, testproj1,testproj2,howto,index
import sqlite3

app_context = app.app_context()
app_context.push()

current_app.name

class Test(unittest.TestCase):

    with app.app_context():
        print(current_app.name)

    def setUp(self):
        app.config['TESTING'] = True
        app.config['WTF_CSRF_ENABLED'] = False
        app.config['DEBUG'] = False
        self.app = app.test_client()

    def tearDown(self):
        pass

#compare the connection's status code to 200, which is "ok"
    def test_connection(self):
        response = self.app.get('/', follow_redirects=True)
        self.assertEqual(response.status_code, 200)

#test if homepage is displaying correctly
    def test_hello(self):
        with app.test_request_context():
            self.assertEqual(hello(),render_template("login.html"))
    
    def test_timeline(self):
            with app.test_request_context():
                self.assertEqual(timeline(),render_template("timeline.html"))

    #def test_testproj1(self):
            #with app.test_request_context():
                #self.assertEqual(testproj1(),render_template("testproj1.html"))  

    #def test_testproj2(self):
            #with app.test_request_context():
                #self.assertEqual(testproj2(),render_template("testproj2.html"))  

    def test_howto(self):
            with app.test_request_context():
                self.assertEqual(howto(),render_template("howto.html"))
                
    #def test_myproj(self):
            #with app.test_request_context():
                #session['username'] = 0
                #self.maxDiff = None
                #self.assertEqual(myproj(),render_template("myproj.html"))

    def test_index(self):
            with app.test_request_context():
                session['username'] = 0
                self.assertEqual(index(),render_template('index.html',uname = session['username']))  
                
                
    def test_task(self):
            c = getDB()
            language = 'test 1'
            two = 'test 1'
            three = 'test 1'
            c.execute("""INSERT INTO task(title,description,phase) VALUES(?,?,?)""",(language,two,three,))
            
            name = str(c.execute("""SELECT title,description,phase FROM task WHERE title = 'test 1' AND description = 'test 1' AND phase = 'test 1'""").fetchall())
            self.assertEqual(name,"[('test 1', 'test 1', 'test 1')]")

    
    def test_bug(self):
            c = getDB()
            one = 1
            two = 'test 1'
            three = 'test 1'
            four = 'test 1'
            c.execute("""INSERT INTO bug(task_id,line,fname,description) VALUES(?,?,?,?)""",(one,two,three,four))
            name = str(c.execute("""SELECT task_id,line,fname,description FROM bug WHERE task_id = 1 AND description = 'test 1' AND line = 'test 1' AND fname = 'test 1' """).fetchall())
            self.assertEqual(name,"[(1, 'test 1', 'test 1', 'test 1')]")

    
    def test_project(self):
            c = getDB()
            one = 'test 1'
            two = 'test 1'
            three = 'test 1'
            c.execute("""INSERT INTO project(manager,title,description) VALUES(?,?,?)""",(three,one,two))
            name = str(c.execute("""SELECT manager,title,description FROM project WHERE description = 'test 1' AND title = 'test 1' AND manager = 'test 1' """).fetchall())
            self.assertEqual(name,"[('test 1', 'test 1', 'test 1')]")
        
    
    def test_phase(self):
            c = getDB()
            one = 'test 1'
            two = 'test 1'
            c.execute("""INSERT INTO columns(proj,coll) VALUES(?,?)""",(two,one))
            name = str(c.execute("""SELECT proj,coll FROM columns WHERE proj = 'test 1' AND coll = 'test 1' """).fetchall())
            self.assertEqual(name,"[('test 1', 'test 1')]")
            

    def test_user(self):
        c = getDB()
        one = 'test 1'
        c.execute("""INSERT INTO user(uname) VALUES (?)""",(one,))
        name = str(c.execute("""SELECT uname FROM user WHERE uname = 'test 1' """).fetchall())
        self.assertEqual(name,"[('test 1',)]")
            
if __name__ == "__main__":
    unittest.main()
