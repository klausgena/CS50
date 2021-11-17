# TODO: if 0 shares, but history: change index?
# TODO: (more important) if sum of shares = 0, do not send to template
# (functions index and sell). That avoids unnecessary complexity of template.
# CHange sell flash message
# Also not correct: original_price in index (if several times bought, which price to show?)
# een chart in javascript met de evolutie over de tijd (op tijd gesorteerde list met prijzen)
# Flash when you buy
# TODO: add a profile page (change name and password)

import os
from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    symbols = db.execute("SELECT DISTINCT symbol, SUM (shares) AS shares, price FROM purchases WHERE user_id=? GROUP BY symbol", session["user_id"])
    cash_left = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    grand_total = 0
    results = []
    for symbol in symbols:
        # SQL and lookup dicts have price key. We should make a new one.
        symbol['old_price'] = symbol.pop('price')
        result = lookup(symbol['symbol'])
        # combine SQL and lookup result dicts
        result = result | symbol
        result['total_value'] = result['price'] * result['shares']
        grand_total = grand_total + result['total_value']
        results.append(result)
    total = grand_total + cash_left[0]['cash']
    print(results) #test
    return render_template("index.html", results=results, cash=cash_left, grand_total=grand_total, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        print(shares)
        results = lookup(symbol)
        if results == None:
            return apology("Symbol doesn't exist or server doesn't respond.")
        elif shares.isdigit() == False or int(shares) < 1:
            return apology("Shares should be positive integer!")
        else:
            q_cash = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])
            cash_left = q_cash[0]['cash']
            share_price = results['price']
            # get current time
            current_time = datetime.now()
            print(f"Cash left: {cash_left}")
            if share_price * int(shares) > cash_left:
                return apology("Not enough cash, sorry!")
            else:
                cash_new_amount = cash_left - (share_price * int(shares))
                db.execute("INSERT INTO purchases (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", session['user_id'], symbol, int(shares), share_price)
                db.execute("UPDATE users SET cash=? WHERE id=?", cash_new_amount, session['user_id'])
                return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    results = db.execute("SELECT * FROM purchases WHERE user_id=?", session['user_id'])
    print(results)
    return render_template("history.html", results=results)


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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        results = lookup(symbol)
        if results == None:
            return apology("Symbol doesn't exist or server doesn't respond.")
        else:
            results["price"] = usd(results["price"])
            return render_template("quoted.html", results=results)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
            username = request.form.get("username")
            password = request.form.get("password")
            confirmation = request.form.get("confirmation")
            rows = db.execute("SELECT * FROM users WHERE username=?", username)
            if username == "":
                return apology("Username empty.")
            elif len(rows) != 0 and rows[0]['username'] == username:
                return apology("Username exists. Choose another.")
            elif password != confirmation or password == "":
                return apology("Password blank or doesn't match.")
            else:
                hash = generate_password_hash(password)
                db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
                return render_template("login.html")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    symbols = db.execute("SELECT DISTINCT symbol, SUM(shares) AS shares FROM purchases WHERE user_id=? GROUP BY symbol", session['user_id'])
    if request.method == "GET":
        print(symbols)
        return render_template("sell.html", symbols=symbols)
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        symbol_list = [symbol['symbol'] for symbol in symbols]
        print(symbol_list)
        print(shares)
        if symbol == None or symbol not in symbol_list:
            return apology("Sorry, but you didn't indicate the stock or do not own it.")
        max_shares = [shares['shares'] for shares in symbols if symbol in shares['symbol']][0]
        if shares.isdigit() == False or int(shares) < 1 or int(shares) > int(max_shares):
            return apology("Shares should be a positive integer or you tried to sell too many shares!")
        else:
            q_cash = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])
            # lookup current share price
            results = lookup(symbol)
            # Query for chosen symbol price
            if results == None:
                return apology("Symbol doesn't exist or server doesn't respond.")
            else:
                current_price = results["price"]
            cash_left = q_cash[0]['cash']
            # you sell, so you receive money for the sold amount of shares at the current price
            cash_new_amount = cash_left + (current_price * int(shares))
            # shares is negative value (you sell them)
            shares = 0 - int(shares)
            db.execute("INSERT INTO purchases (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", session['user_id'], symbol, shares, current_price)
            db.execute("UPDATE users SET cash=? WHERE id=?", cash_new_amount, session['user_id'])
            # flash a message indicating that blabla has been updated
            flash(f"{abs(shares)} shares sold of {symbol.upper()}. Good riddance! You have {usd(cash_new_amount)} left. What are you waiting for?")
            return redirect("/")

@app.route("/profile", methods=["GET", "POST"])
def profile():
    """Edit your profile"""
    return apology("TODO")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
