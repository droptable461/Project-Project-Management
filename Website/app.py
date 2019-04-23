from flask import Flask, request, g, render_template, redirect, url_for, escape, session
import sqlite3
import requests
import json
#from urllib.request import urlopren
from collections import defaultdict
import simplejson
import urllib.parse
from datetime import datetime

#conn = sqlite3.connect('database.db')

app = Flask(__name__)
app.debug = True       #Comment this out once your code is working
app.config.from_object(__name__)
app.config.update( dict(
        DATABASE="database.db",
        SECRET_KEY="one"
))

def connectDB():
	rv = sqlite3.connect('database.db')
	return rv

def getDB():
        if not hasattr(g, 'sqlite_db'):
            g.sqlite_db = connectDB()
        return g.sqlite_db

@app.route('/login', methods=['GET', 'POST'])
def login():
	if request.method == 'POST':
		db = getDB()
		validlogin = False

		validlogin = db.execute('SELECT uname FROM user WHERE uname = ?', (request.form['username'],)).fetchall()

		if validlogin:
			session['username'] = request.form['username']
			return render_template("index.html",name=validlogin)
	return render_template('login.html')

@app.route('/')
def hello():
    return render_template("login.html")

@app.route('/myproj', methods=['GET','POST','PUT'])
def myproj():
        c = getDB()
        p = [row[0] for row in c.execute("""SELECT DISTINCT proj FROM user WHERE uname = (?)""",(session['username'],)).fetchall()]
        k = [row[0] for row in c.execute("""SELECT DISTINCT coll FROM columns""").fetchall()]#WHERE proj = (?)""",(current)).fetchall()]
#dif func for dif proj operations: add(proj or tasks), retrieve(proj and tasks), remove(proj or tasks), modify(proj or tasks)
        if request.method == 'PUT':
            k = retCol()
            t = retTask()
        if request.method == 'POST':
             addProj()
             addTask()
             addCol()

        return render_template('myproj.html',projects = p,columns = k)

def addCol():
    if 'title3' in request.form:
        c = getDB()
        current = request.form['cur']
        c.execute("""INSERT INTO columns(proj,coll) VALUES(?,?)""",(current,request.form['title3'],))
        c.commit()
        c.close()

def retCol():
    c = getDB()
    current = request.form['cur']
    k = [row[0] for row in c.execute("""SELECT coll FROM columns WHERE proj = (?)""",(current)).fetchall()]
    return k

def retTask():
        if True:
            c = getDB()
            current = request.form['cur']
            variable = [row[0] for row in c.execute("""SELECT tasks FROM user NATURAL JOIN project WHERE uname = (?) AND title = (?)""",(session['username'],current)).fetchall()]
            for i in range(len(variable)):
                t[i] = c.execute("""SELECT * FROM task WHERE task_id = ?""", (variable[i],)).fetchall()
            return t
#maybe loop through putting them into a new array? & return the array

def addProj():
	if 'manager' in request.form:
            db = getDB()
            man = request.form['manager']
            title = request.form['title']
            des = request.form['description']
            db.execute("""INSERT INTO project (manager,title,description) VALUES(?,?,?)""",(man,title,des))
            db.execute("""INSERT INTO user (uname,proj) VALUES(?,?)""",(session['username'],title))
            db.commit()
            db.close()
            return

def addTask():
	if 'title2' in request.form:
	    db1 = getDB()
	    #taskID = request.form['task_id']
        #something to link task to the current proj, data from button
        #   current = request.form['cur']
	    taskTitle = request.form['title2']
	    taskDes = request.form['description2']
	    taskPhase = request.form['phase']
	   # taskBug = request.form['bug_id']
	    db1.execute("""INSERT INTO task (title,description,phase) VALUES(?,?,?)""",(taskTitle,taskDes,taskPhase))
	    v = db1.execute("""SELECT task_id FROM task WHERE title = (?)""",(taskTitle,)).fetchall()
	    db1.execute("""INSERT INTO user (uname,tasks) VALUES(?,?)""",(session['username'],v))
	    db1.commit()
	    db1.close()
	return

@app.route('/timeline')
def timeline():
    return render_template('timeline.html')
@app.route('/testProj1')
def testproj1():
    return render_template('testproj1.html')

@app.route('/testProj2')
def testproj2():
    return render_template('testproj2.html')

@app.route('/howto')
def howto():
    return render_template('howto.html')

@app.route('/index')
def index():
    return render_template('index.html',uname = session['username'])


@app.route('/task', methods=['GET', 'POST'])
def task():
        c = getDB()
        language = request.form.get('t_description')
        two = request.form.get('t_title')
        three = request.form.get('p_title')
        #language = "tejas"
        #two = "roma"
        #three = "sima"
        now = datetime.now()
        formatted_date = now.strftime('%m-%d-%Y %H:%M:%S')
        c.execute("""INSERT INTO task(title,description,phase,dateMade) VALUES(?,?,?,?)""",(language,two,three,formatted_date))
        c.commit()
        c.close() 
        
        #print(language)
        #print(two)
        #print(three)
        #return '''<h1>The string is: {}</h1>'''.format(language)
    
        return '''<h1>The string is: {}</h1>'''.format('task')
    
@app.route('/bug', methods=['GET', 'POST'])
def bug():
        c = getDB()
        #one = request.form.get('b_line')
        #two = request.form.get('b_file')
        #three = request.form.get('b_description')
        #four = request.form.get('t_title')

        one = "tejas"
        two = "roma"
        three = "sima"
        four = "dhruvi"
        now = datetime.now()
        formatted_date = now.strftime('%m-%d-%Y %H:%M:%S')
        c.execute("""INSERT INTO bug(line,fname,description) VALUES(?,?,?)""",(one,two,three))
        c.commit()
        c.close() 

        return '''<h1>The string is: {}</h1>'''.format('bug')

@app.route('/project', methods=['GET', 'POST'])
def project():
        c = getDB()
        one = request.form.get('p_title')
        two = request.form.get('p_description')
        three = request.form.get('uid')
        #one = "tejas"
        #two = "roma"
        #three = "sima"
        now = datetime.now()
        formatted_date = now.strftime('%m-%d-%Y %H:%M:%S')
        c.execute("""INSERT INTO project(manager,title,description) VALUES(?,?,?)""",(one,two,three))
        c.commit()
        c.close() 
        return '''<h1>The string is: {}</h1>'''.format('project')
    
@app.route('/user', methods=['GET', 'POST'])
def user():
        c = getDB()
        #one = request.form.get('uname')      
        one = "tejas"
        now = datetime.now()
        formatted_date = now.strftime('%m-%d-%Y %H:%M:%S')
        c.execute("""INSERT INTO user(uname) VALUES (?)""",(one,))
        c.commit()
        c.close() 
        return '''<h1>The string is: {}</h1>'''.format('user')
    
@app.route('/phase', methods=['GET', 'POST'])
def phase():
        c = getDB()
        #one = request.form.get('ph_title')
        #two = request.form.get('p_title')
        
        one = "tejas"
        two = "roma"
      
        now = datetime.now()
        formatted_date = now.strftime('%m-%d-%Y %H:%M:%S')
        c.execute("""INSERT INTO (manager,title) VALUES(?,?)""",(one,two))
        c.commit()
        c.close() 
        return '''<h1>The string is: {}</h1>'''.format('phase')

@app.route('/git', methods=['GET', 'POST'])
def git():
#name , date , message
#https://api.github.com/repos/droptable461/Project-Project-Management/commits
#commit { author { name and date
#commit { message
#https://api.github.com/repos/droptable461/Project-Project-Management/commits?per_page=100&sha=f97103bab8a64a9656fa8139052bc4759aa9b625
#https://api.github.com/repos/droptable461/Project-Project-Management/commits?since=2019-04-21T19:42:22Z
#https://api.github.com/repos/droptable461/Project-Project-Management/commits?page=2&per_page=100

    link = 'https://api.github.com/repos/droptable461/Project-Project-Management/events'
    r = requests.get('https://api.github.com/repos/droptable461/Project-Project-Management/commits')
   
    for item in r.json():
        for key in item['commit']['committer']:
            print(item['commit']['committer']['name'])
            print(item['commit']['committer']['date'])
            print(item['commit']['message'])
    return 'suc'

@app.teardown_appcontext
def closeDB(error):
	if hasattr(g, 'sqlite_db'):
            g.sqlite_db.close()


if __name__ == '__main__':
    app.run(host="0.0.0.0")
    task()
