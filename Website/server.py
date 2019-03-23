from flask import Flask, g, render_template 

app = Flask(__name__)
app.debug = True

@app.route('/')
def main():
    return render_template('index.html')

@app.route('/login')
def login(): 
    return render_template('login.html')



if __name__ == '__main__': 
    app.run()
