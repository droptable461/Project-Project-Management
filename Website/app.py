from flask import Flask, request, g, render_template, redirect, url_for, escape, session
import sqlite3

#conn = sqlite3.connect('database.db')

app = Flask(__name__)
app.secret_key = 'one'

@app.route('/')
def hello():
    return render_template("login.html")

#thomas version
#@app.route('/',methods=["POST"])
#def login():
#    with sqlite3.connect('database.db') as db:
#        c = db.cursor()
#        if "uname" in request.form:
#            username = escape(request.form["uname"])
#            print (username)
#           c.execute("SELECT uname FROM user WHERE uname=?",  (username,))
#            check = c.fetchone()
#            print (check)
#            if check == username:
#                    return render_template("index.html", name = username)
#            else:
#                    print ("failed")
#                    return render_template("login.html")

#tejas v
@app.route('/login', methods=['GET', 'POST'])
def login():
	if request.method == 'POST':
	    with sqlite3.connect('database.db') as db:
		validlogin = False

		validlogin = db.execute('SELECT * FROM user WHERE uname = ?', (request.form['username'],)).fetchall()

		if validlogin:
			session['username'] = request.form['username']
			return render_template("index.html")
	        else:
                        return render_template('login.html')

@app.route('/myproj')
def myproj():
    return render_template('myproj.html')

@app.route('/inbox')
def inbox():
    return render_template('inbox.html')

@app.route('/howto')
def howto():
    return render_template('howto.html')


#@app.route('/myproj', methods=['GET', 'POST'])
#def myproj():
	#if request.method == 'POST':
		#db = getDB()
		#error = None
		#info = False

		#info = db.execute('SELECT * FROM task WHERE uname = ?', (request.form['username'],)).fetchall()

		#if validlogin:
			#session['username'] = request.form['username']
			#return redirect(url_for('index'))
	#return render_template('login.html')

@app.route('/index')
def index():
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)
