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

@app.route('/myproj', methods=['GET','POST'])
def myproj():
        c = getDB()
        p = [row[0] for row in c.execute("""SELECT DISTINCT proj FROM user WHERE uname = (?)""",(session['username'],)).fetchall()]
        #for j in range(len(p)):
            #print(p[j])

        if request.method == 'POST':
                addproj()
       # else:
        #        addtask()

        return render_template('myproj.html',p)
        
#dif func for dif proj operations: add(proj or tasks), retrieve(proj and tasks), remove(proj or tasks), modify(proj or tasks)
def addproj():
    if request.method == 'POST':
        db = getDB()
        man = request.form['manager']
        title = request.form['title']
        des = request.form['description']
        db.execute("INSERT INTO project (manager,title,description) VALUES(?,?,?)",(man,title,des))
        db.commit()
    return True

#def addtast():
#    if request.method == 'POST':
#        db = getDB()
        

@app.route('/inbox')
def inbox():
    return render_template('inbox.html')

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

@app.teardown_appcontext
def closeDB(error):
	if hasattr(g, 'sqlite_db'):
            g.sqlite_db.close()


if __name__ == '__main__':
    app.run(host="0.0.0.0")
