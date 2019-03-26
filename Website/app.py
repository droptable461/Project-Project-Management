from flask import Flask, request, render_template
import socket

app = Flask(__name__)

@app.route('/')
def hello():
    return render_template('index.html')

if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('localhost', 5501))
    port = sock.getsockname()[1]
    sock.close()
    app.run(port=port)
