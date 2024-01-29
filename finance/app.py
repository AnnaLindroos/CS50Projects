import os
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():

    portfolio = db.execute("SELECT * FROM portfolio WHERE user = ?", session["user_id"])
    cashBalance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0].get('cash')
    values = db.execute("SELECT val FROM portfolio WHERE user = ?", session["user_id"])
    totalValue = 0
    for i in range(len(values)):
        totalValue += values[i].get('val')

    return render_template("index.html", portfolios=portfolio, cashBalance=cashBalance, totalValue=totalValue)
    """Show portfolio of stocks"""


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    # If reached via POST
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Ensure symbol exists
        elif lookup(request.form.get("symbol")) == None:
            return apology("Stock symbol not found", 400)

        # Ensure shares was submitted
        if not request.form.get("shares"):
            return apology("Must submit number of shares to buy", 400)

        # Ensure shares is an integer input
        elif not re.search("^[1-9]+[0-9]*$", request.form.get("shares")):
            return apology("Shares must be a positive number", 400)

        # Ensure number of shares is a positive integer
        elif int(request.form.get("shares")) <= 0:
            return apology("Shares must be a positive whole number", 400)

        # Find out how many shares user wants to buy
        shares = int(request.form.get("shares"))

        # Find out which stock user wants to buy
        symbol = request.form.get("symbol").upper()

        # Look up stock's current price
        lookupDict = lookup(request.form.get("symbol"))

        # Find out how much the stocks will cost the user
        total = lookupDict.get("price") * shares

        # Find out how much money user has
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        money = rows[0].get('cash')

        # Ensure that user can afford stocks
        if float(money) >= total:
            transactionDb = db.execute("INSERT INTO transactions (price, symbol, shares, user_id, type) VALUES(?, ?, ?, ?, ?)",
                                       total, request.form.get("symbol"), shares, session["user_id"], "Purchase")

            if len(db.execute("SELECT stocks_owned FROM portfolio WHERE user = ? AND stocks_owned = ?", session["user_id"], symbol)) > 0:

                userStocks = db.execute(
                    "SELECT stock_shares FROM portfolio WHERE user = ? AND stocks_owned = ?", session["user_id"], symbol)
                currentShares = userStocks[0].get('stock_shares') + shares
                userValue = currentShares * lookupDict.get("price")

                db.execute("UPDATE portfolio SET stock_shares = ? WHERE user = ? AND stocks_owned = ?",
                           currentShares, session["user_id"], symbol)
                db.execute("UPDATE portfolio SET price_per_stock = ? WHERE user = ? AND stocks_owned = ?",
                           lookupDict.get("price"), session["user_id"], symbol)
                db.execute("UPDATE portfolio SET val = ? WHERE user = ? AND stocks_owned = ?",
                           userValue, session["user_id"], symbol)

            else:

                userValue = shares * lookupDict.get("price")
                db.execute("INSERT INTO portfolio (user, stocks_owned, stock_shares, price_per_stock, val) VALUES(?, ?, ?, ?, ?)",
                           session["user_id"], symbol, shares, lookupDict.get("price"), userValue)

            amountLeft = money - total
            db.execute("UPDATE users SET cash = ? WHERE id = ?", amountLeft, session["user_id"])
            return redirect("/")
        else:
            return apology("Not enough cash", 403)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():

    transaction = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", transactions=transaction)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # If reached via POST
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Ensure symbol exists
        elif lookup(request.form.get("symbol")) == None:
            return apology("Stock symbol not found", 400)

        lookupDict = lookup(request.form.get("symbol"))

        return render_template("quoted.html", name=lookupDict.get("name"), price=lookupDict.get("price"), symbol=lookupDict.get("symbol"))

    # If reached via GET
    else:

        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not re.search("^(.*[A-Z])(.*[0-9].*)$", request.form.get("password")):
            return apology("Password must contain at least one capital letter and a number", 400)

        # Ensure that the password and verification field match
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("password not verified", 400)

        # Query database for username
        elif len(db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))) > 0:
            return apology("Username already taken", 400)

        # Hash password
        hash = generate_password_hash(request.form.get("password"))

        # Insert user into database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), hash)

        # Query database for username in order to remember which user has logged in
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Remember the user and create session
        session["user_id"] = rows[0]["id"]

        # Send user to homepage
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Ensure user owns the stock(s)
        elif len(db.execute("SELECT stocks_owned FROM portfolio WHERE user = ? AND stocks_owned = ?", session["user_id"], request.form.get("symbol"))) <= 0:
            return apology("Must be an owned stock", 400)

        # Ensure shares was submitted
        elif not request.form.get("shares"):
            return apology("Must submit number of shares to buy", 403)

        # Ensure shares is an integer
        elif int(request.form.get("shares")) == False:
            return apology("Shares must be a positive number", 400)

        # Ensure number of shares is a positive integer
        elif int(request.form.get("shares")) <= 0:
            return apology("Shares must be a positive whole number", 400)

        # Find out how many shares user wants to sell
        shares = int(request.form.get("shares"))

        # Find out which stock user wants to sell
        symbol = request.form.get("symbol")

        # Ensure number of shares is a positive integer
        if shares <= 0:
            return apology("Shares must be a positive value", 400)

        # Ensure user owns the number of shares submitted
        extractShares = db.execute("SELECT * FROM portfolio WHERE user = ? AND stocks_owned = ?", session["user_id"], symbol)
        resultShares = extractShares[0].get('stock_shares')
        if int(resultShares) <= shares:
            return apology("Must be an owned number of shares", 400)

       # Look up stock's current price
        lookupDict = lookup(request.form.get("symbol"))

        # Find out how much money the user will get
        total = lookupDict.get("price") * shares

        transactionDb = db.execute("INSERT INTO transactions (price, symbol, shares, user_id, type) VALUES(?, ?, ?, ?, ?)",
                                   total, request.form.get("symbol"), shares, session["user_id"], "Sell")

        # Find out how much money user has
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        money = rows[0].get('cash')

        userStocks = db.execute("SELECT stock_shares FROM portfolio WHERE user = ? AND stocks_owned = ?",
                                session["user_id"], symbol)
        currentShares = userStocks[0].get('stock_shares') - shares
        userValue = currentShares * lookupDict.get("price")

        if currentShares == 0:
            db.execute("DELETE FROM portfolio WHERE stocks_owned = ?", symbol)

        else:

            db.execute("UPDATE portfolio SET stock_shares = ? WHERE user = ? AND stocks_owned = ?",
                       currentShares, session["user_id"], symbol)
            db.execute("UPDATE portfolio SET price_per_stock = ? WHERE user = ? AND stocks_owned = ?",
                       lookupDict.get("price"), session["user_id"], symbol)
            db.execute("UPDATE portfolio SET val = ? WHERE user = ? AND stocks_owned = ?",
                       userValue, session["user_id"], symbol)

        amountLeft = money + total
        db.execute("UPDATE users SET cash = ? WHERE id = ?", amountLeft, session["user_id"])
        return redirect("/")

    else:
        optionMenu = db.execute("SELECT stocks_owned FROM portfolio WHERE user = ?", session["user_id"])
        return render_template("sell.html", optionMenus=optionMenu)

