from flask import Flask, url_for, redirect, session, render_template
app = Flask(__name__)

@app.route("/")
def index():
    return "You are at the index page!"

@app.route("/sample")
def sample():
    return "You are on the sample page!"

@app.route("/show/<number>")
def show(number):
    return "You passed in {}".format(number)

 #examples from a problem set
@app.route("/login", methods='['GET', 'POST'])
def login():
    if not request.form.get("username")
    return apology("must provide username")

@app.route("/login", methods='['GET', 'POST'])
def login():
    if request.method =="POST":
        # do one thing
        else:
            #do something else