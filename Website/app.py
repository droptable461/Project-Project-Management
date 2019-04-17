from flask import Flask, request, g, render_template, redirect, url_for, escape, session
import sqlite3

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
#dif func for dif proj operations: add(proj or tasks), retrieve(proj and tasks), remove(proj or tasks), modify(proj or tasks)
        if request.method == 'PUT':
             retTask()
        if request.method == 'POST':
             addProj()
             addTask()

        return render_template('myproj.html',projects = p)

def retTask():
        if True:
            c = getDB()
            current = request.form['cur']
            variable = [row[0] for row in c.execute("""SELECT tasks FROM user NATURAL JOIN project WHERE uname = (?) AND title = (?)""",(session['username'],current)).fetchall()]
            for i in range(len(variable)):
                c.execute("""SELECT * FROM task WHERE task_id = ?""", (variable[i],)).fetchall()
#maybe loop through putting them into a new array? & return the array

def addProj():
	if 'manager' in request.form:
            db = getDB()
            man = request.form['manager']
            title = request.form['title']
            des = request.form['description']
            db.execute("""INSERT INTO project (manager,title,description) VALUES(?,?,?)""",(man,title,des))
            db.execute("""INSERT INTO users (uname,proj) VALUES(?,?)""",(session['username'],title))
            db.commit()
            db.close()
            return

def addTask():
	if 'title2' in request.form:
	    db1 = getDB()
	    #taskID = request.form['task_id']
        #something to link task to the current proj
	    taskTitle = request.form['title2']
	    taskDes = request.form['description2']
	    taskPhase = request.form['phase']
	   # taskBug = request.form['bug_id']
	    db1.execute("""INSERT INTO task (title,description,phase) VALUES(?,?,?)""",(taskTitle,taskDes,taskPhase))
        v = db1.execute("""SELECT task_id FROM task WHERE title = (?)""",(taskTitle,)).fetchall()
        db1.execute("""INSERT INTO users (uname,tasks) VALUES(?,?)""",(session['username'],v))
        db1.commit()
        db1.close()
	return

@app.route('/timeline')
def timeline():
    return render_template('timeline.html')

@app.route('/howto')
def howto():
    return render_template('howto.html')

@app.route('/index')
def index():
    return render_template('index.html')

@app.route("/test", methods=['GET', 'POST'])
def test():
    #request
     return make_response('Test ..')

@app.route("/task", methods=['GET', 'POST'])
def task():
    #if request.method=="GET":
        #req = requests.get('http://127.0.0.1:5000/task')
        ##print(req.text)
        #print("HTTP Status Code: " + str(req.status_code))
        #print(req.headers)
        #json_response = json.loads(req.content)
        #print(json_response['t_description'])
        language = request.args.get('t_description') #if key doesn't exist, returns None
        return '''<h1>The string is: {}</h1>'''.format(language)

@app.teardown_appcontext
def closeDB(error):
	if hasattr(g, 'sqlite_db'):
            g.sqlite_db.close()


if __name__ == '__main__':
    app.run(host="0.0.0.0")
