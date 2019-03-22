from flask import Flask
from flask import Flask, flash, redirect, render_template, request, session, abort
import os 

app = Flask(__name__)
#app.debug = True

@app.route('/')
def home():
    #return "Hey"
    if not session.get('logged_in'):
        return render_template('login.html')
    else:
        return "Hello Boss!"

@app.route('/login', methods=['POST'])
def do_admin_login():
    if request.form['password'] == 'password' and request.form['username'] == 'admin': session['logged_in'] = True
    else: 
        flash('wrong password')
        return home()

@app.route('/logout')
def logout():
    session['logged_in'] = False
    return home()





#def login():
    #return 'DROPTABLE 461 Log In Page'

#@app.route('/user/<username>')
#def profile(username):
    #return '{}\'s profile'.format(username)

#with app.test_request_context():
    #print(url_for('home'))
    #print(url_for('login'))
    #print(url_for('profile', username='John Doe'))



#    error = None
 #   if request.method == 'POST':
  #      if request.form['username'] != 'admin' or request.form['password'] != 'admin':
   #         error = 'Invalid Credentials. Please try again.'
    #    else:
     #       return redirect(url_for('static', filename='style.css'))
   # return render_template('templates/auth/login.html', error=error) 


if __name__ == '__main__':
    app.secret_key = os.urandom(12)
    app.run(debug=True,host='0.0.0.0', port=4000)
