from flask import Flask, request, g, render_template, redirect, url_for, escape
import sqlite3

conn = sqlite3.connect('database.db')

#app = Flask(__name__)

#@app.route('/')
#def hello():
    #return 'Hello, world! running on'

#def login():
c = conn.cursor()
username = input('username')
c.execute("SELECT uname FROM user WHERE uname = '%s'" % (username))
one = c.fetchall()
if one is True:
    return True 
else:
    return False

#@app.route('/login', methods=['POST'])
#def login():
    #c = conn.cursor()
    #username = escape(request.form['uname'])
    #c.execute("SELECT uname FROM user WHERE uname = '%s'" % (username))
    #if fetchall() is true:
            #return render_template("index.html", name = username)
    #else:
            #return render_template("login.html")
        
if __name__ == '__main__':
    #app.run(debug=True)
    #login()s
