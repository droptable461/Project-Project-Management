from flask import Flask, g, render_template 

app = Flask(__name__)
app.debug = True

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/index')
def main():
    return render_template('index.html')

@app.route('/myproj')
def myproj():
    return render_template('myproj.html')

@app.route('/inbox')
def inbox():
    return render_template('inbox.html')

@app.route('/howto')
def howto():
    return render_template('howto.html')

if __name__ == '__main__': 
    app.run()
