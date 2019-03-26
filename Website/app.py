from flask import Flask, request, g, render_template, redirect, url_for, escape
import sqlite3

#conn = sqlite3.connect('database.db')

app = Flask(__name__)

@app.route('/')
def hello():
    return render_template("login.html")

#def login():
#c = conn.cursor()
#username = input('username')
#c.execute("SELECT uname FROM user WHERE uname = '%s'" % (username))
#one = c.fetchall()
#if one is True:
#    print True 
#else:
#    print False

@app.route('/login_q')#,methods=["POST"])
def login():
    with sqlite3.connect('database.db') as db:
        db.cursor()
        username = escape(request.form['Username'])
        db.execute("SELECT uname FROM user WHERE uname = '%s'" % (username))
        if db.fetchall() is true:
                return render_template("index.html", name = username)
        else:
                return render_template("login.html")
        
if __name__ == '__main__':
    app.run(debug=True)
    #login()s
