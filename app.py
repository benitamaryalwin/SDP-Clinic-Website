from flask import Flask, request, render_template
import subprocess

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/submit', methods=['POST'])
def submit():
    name = request.form['name']
    age = request.form['age']
    gender = request.form['gender']
    phone = request.form['phone']

    result = subprocess.run(
        ['./patient', '1', name, age, gender, phone],
        capture_output=True,
        text=True
    )

    return render_template('index.html', output=result.stdout)

if __name__ == '__main__':
    app.run(debug=True)