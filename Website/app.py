from flask import Flask, request, g, render_template, redirect, url_for, escape, session
import sqlite3
import requests
import json
#from urllib.request import urlopren
from collections import defaultdict
import simplejson
import urllib.parse
from datetime import datetime
from git import Git
from git import Repo


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


def checkLogged():
	if 'uname' in session:
		return True
	return False

@app.route('/login', methods=['GET', 'POST'])
def login():
	if request.method == 'POST':
		db = getDB()
		validlogin = False

		validlogin = db.execute('SELECT uname FROM user WHERE uname = ?', (request.form['username'],)).fetchall()

		if validlogin:
			session['username'] = request.form['username']
			return render_template("index.html",name=session['username'])
	return render_template('login.html')

@app.route('/logout')
def logout():
	if not checkLogged():
		return render_template('login.html')
	session.pop('uname', None)
	return render_template('login.html')

@app.route('/')
def hello():
    return render_template("login.html")

@app.route("/myproj/<proj>/<task>")
def update_py(task="",proj=""):
        c = getDB()

        
        t = [row[0] for row in c.execute("""SELECT DISTINCT title FROM task, columns WHERE columns.proj = (?) AND columns.task_id = task.task_id AND task.title = (?)""",(proj,task)).fetchall()]
        d = [row[0] for row in c.execute("""SELECT DISTINCT task.description FROM task, columns WHERE columns.proj = (?) AND columns.task_id = task.task_id AND task.title = (?)""",(proj,task)).fetchall()]
        bf = [row[0] for row in c.execute("""SELECT DISTINCT fname,line,bug.description FROM task, columns, bug WHERE columns.proj = (?) AND columns.task_id = task.task_id AND task.task_id = bug.t_id AND task.title = (?)""",(proj,task)).fetchall()]
        #bl = [row[0] for row in c.execute("""SELECT DISTINCT line FROM task, columns, bug WHERE columns.proj = (?) AND columns.task_id = task.task_id AND task.task_id = bug.t_id AND task.title = (?)""",(proj,task)).fetchall()]
        #bd = [row[0] for row in c.execute("""SELECT DISTINCT description FROM task, columns, bug WHERE columns.proj = (?) AND columns.task_id = task.task_id AND task.task_id = bug.t_id AND task.title = (?)""",(proj,task)).fetchall()]
        m = [row[0] for row in c.execute("""SELECT DISTINCT dateMade FROM task, columns WHERE columns.proj = (?) AND columns.task_id = task.task_id AND task.title = (?)""",(proj,task)).fetchall()]
        u = [row[0] for row in c.execute("""SELECT DISTINCT uname FROM task, columns, user WHERE columns.proj = (?) AND columns.task_id = task.task_id AND task.title = (?) AND tasks = task.task_id""",(proj,task)).fetchall()]
        #p = [row[0] for row in c.execute("""SELECT DISTINCT commits FROM task, columns WHERE columns.proj = (?) AND columns.task_id = task.task_id AND task.title = (?)""",(proj,task)).fetchall()]
        return render_template("task.html",title = t, disc = d, date = m, user = u, bugf = bf)#, bugd = bd, bugl = bl)

@app.route('/myproj/', methods=['GET','POST','PUT'])
def proj(proj=""):
        c = getDB()
        p = [row[0] for row in c.execute("""SELECT DISTINCT proj FROM user WHERE uname = (?)""",(session['username'],)).fetchall()]
        k = [row[0] for row in c.execute("""SELECT DISTINCT coll FROM columns""").fetchall()]#WHERE proj = (?)""",(current)).fetchall()]
        #if request.method == 'POST':
            #print('here2')
            #currentProject()
        #if 'projec' in session
            #k = retCol()
            #t = retTask()
        if request.method == 'POST':
             addProj()
             addTask()
             addCol()

        return render_template('project.html',projects = p)

@app.route('/myproj/<proj>/', methods=['GET','POST','PUT'])
def myproj(proj):
        c = getDB()
        p = [row[0] for row in c.execute("""SELECT DISTINCT proj FROM user WHERE uname = (?)""",(session['username'],)).fetchall()]
        k = [row[0] for row in c.execute("""SELECT DISTINCT coll FROM columns WHERE proj = (?)""",(str(proj),)).fetchall()]#WHERE proj = (?)""",(current)).fetchall()]
        t = [row[0] for row in c.execute("""SELECT DISTINCT title FROM task, columns WHERE columns.proj = (?) AND columns.task_id = task.task_id""",(proj,)).fetchall()]#WHERE proj = (?)""",(current)).fetchall()]
        #if request.method == 'POST':
            #print('here2')
            #currentProject()
        #if 'projec' in session
            #k = retCol()
            #t = retTask()
        if request.method == 'POST':
            addProj()
            addTask(proj)
            addCol(proj)
        return render_template('myproj.html',projects = p,columns = k, tasks = t)

@app.route('/currProj', methods=['GET'])
def currentProject():
    #if 'current' in request.form:
    print('here')
    print(request.args.get('current',''))
    print('here2')
    session['projec'] = request.args.get('current','')
    print(session['projec'])
    print('here3')

def addCol(proj=""):
    if 'title3' in request.form:
        c = getDB()
        c.execute("""INSERT INTO columns(proj,coll) VALUES(?,?)""",(proj,request.form['title3'],))
        c.commit()
        c.close()
    return myproj(proj)

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

def addTask(proj=""):
    if 'title2' in request.form:
        db1 = getDB()
	    #taskID = request.form['task_id']
        #something to link task to the current proj, data from button
        #   current = request.form['cur']
        taskTitle = request.form['title2']
        taskDes = request.form['description2']
        taskPhase = ""
        taskPhase = request.form['phase']
        taskDate = request.form['date']
#taskBug = request.form['bug_id']
        db1.execute("""INSERT INTO task (title,description,dateMade,phase) VALUES(?,?,?,?)""",(taskTitle,taskDes,taskDate,taskPhase))
        v = [row[0] for row in db1.execute("""SELECT task_id FROM task WHERE title = (?)""",(taskTitle,)).fetchall()]
        #db1.execute("""INSERT INTO user (uname,tasks) VALUES(?,?)""",(session['username'],v))

        db1.execute("""INSERT INTO columns (proj,coll,task_id) VALUES(?,?,?)""",(proj,taskPhase,v[0]))
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
        four = request.form.get('ph_id')
        var1 = c.execute("""SELECT phase_id FROM columns WHERE coll = (?) AND proj = (?) LIMIT 1""",(four,three,)).fetchall()
        now = datetime.now()
        formatted_date = now.strftime('%m-%d-%Y %H:%M:%S')
        c.execute("""INSERT INTO task(title,description,phase,dateMade) VALUES(?,?,?,?)""",(language,two,str(var1),formatted_date))
        c.commit()
        c.close()
        return "suc"

@app.route('/bug', methods=['GET', 'POST'])
def bug():
        c = getDB()
        one = request.form.get('b_line')
        two = request.form.get('b_file')
        three = request.form.get('b_description')
        four = request.form.get('t_title')
        five = request.form.get('p_title')
        var1 = c.execute("""SELECT task_id FROM task,columns  WHERE task.phase = columns.phase_id  AND columns.proj = (?) AND task.title = (?) LIMIT 1""",(five,four,)).fetchall()
        c.execute("""INSERT INTO bug(task_id,line,fname,description) VALUES(?,?,?,?)""",(str(var1),one,two,three))
        c.commit()
        c.close()
        return

@app.route('/project', methods=['GET', 'POST'])
def project():
        c = getDB()
        one = request.form.get('p_title')
        two = request.form.get('p_description')
        three = request.form.get('uid')
        c.execute("""INSERT INTO project(manager,title,description) VALUES(?,?,?)""",(three,one,two))
        c.commit()
        c.close()
        return

@app.route('/user', methods=['GET', 'POST'])
def user():
        c = getDB()
        one = request.form.get('uname')
        now = datetime.now()
        formatted_date = now.strftime('%m-%d-%Y %H:%M:%S')
        c.execute("""INSERT INTO user(uname) VALUES (?)""",(one,))
        c.commit()
        c.close()
        return

@app.route('/update', methods=['GET', 'POST'])
def update():
    c = getDB()
    proj = c.execute('''SELECT DISTINCT manager, title, description FROM project''').fetchall()
    task = c.execute('''SELECT DISTINCT title, description, coll, proj  FROM task LEFT JOIN columns''').fetchall()
    bug = c.execute('''SELECT DISTINCT line, fname, bug.description, task.title, proj FROM  bug LEFT JOIN task INNER JOIN columns on t_id=task.task_id AND task.task_id=columns.task_id''').fetchall()
    u = c.execute('''SELECT DISTINCT * FROM user''').fetchall()

    c.close()
    raw = "^"
    for x in proj:
        raw = raw + str(x)
        raw = raw + " "
    raw = raw + "#"
    for x in task:
        raw = raw + str(x)
        raw = raw + " "
    raw = raw + "&"
    for x in bug:
        raw = raw + str(x)
        raw = raw + " "
    raw = raw + "*"
    for x in u:
        raw = raw + str(x)
        raw = raw + " "
    raw = raw + "$"

    return raw


@app.route('/phase', methods=['GET', 'POST'])
def phase():
        c = getDB()
        one = request.form.get('ph_title')
        two = request.form.get('p_title')
        c.execute("""INSERT INTO columns(proj,coll) VALUES(?,?)""",(two,one))
        c.commit()
        c.close()
        return

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
            one = item['commit']['committer']['name']
            two = item['commit']['committer']['date']
            three = item['commit']['message']
            four = one + print('/n') + two + '/n'
            return four

@app.teardown_appcontext
def closeDB(error):
	if hasattr(g, 'sqlite_db'):
            g.sqlite_db.close()


if __name__ == '__main__':
    app.run(host="0.0.0.0")
