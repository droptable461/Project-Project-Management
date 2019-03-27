from flask import Flask, request, g, render_template, redirect, url_for, escape
import sqlite3

#conn = sqlite3.connect('database.db')

app = Flask(__name__)

@app.route('/')
def hello():
    return render_template("login.html")

@app.route('/',methods=["POST"])
def login():
    with sqlite3.connect('database.db') as db:
        c = db.cursor()
        if "uname" in request.form:
            username = escape(request.form["uname"])
            print (username)
            c.execute("SELECT uname FROM user WHERE uname=?",  (username,))
            check = c.fetchone()
            print (check)
            if check == username:
                    return render_template("index.html", name = username)
            else:
                    print ("failed")
                    return render_template("login.html")

@app.route('/index')
def main():
    return render_template('index.html')
        
if __name__ == '__main__':
    app.run(debug=True)
