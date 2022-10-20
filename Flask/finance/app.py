import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from project.helpers import apology, login_required, lookup, usd
import datetime

# Configure application
app = Flask(__name__)


# export API_KEY=pk_36142fda7ba6496e85cbb85cd6d42c88
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
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    # transaction_db = db.execute("SELECT symbol, SUM(shares) AS shares ,price FROM track_buy WHERE user_id = ?  GROUP BY symbol",user_id)
    transaction_db = db.execute(
        "SELECT * FROM track_buy WHERE user_id = ?  GROUP BY symbol", user_id)
    cash_db = db.execute("SELECT cash FROM users where id = ?", user_id)
    cash = cash_db[0]["cash"]

    return render_template("index.html", database=transaction_db, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # for GET method render buy.html
    if request.method == "GET":
        return render_template("buy.html")
    # for post method extracting info from buy.html form
    # And manupulating the database accordingly
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
    # error handling of float number

    # try:
    #     x=float(x)

    # except:
    #     print("error")
    # y= int(float(x))
    # if y== x/100:
    #     print(y)
    # else:
    #
        try:
            shares = float(shares)
        except:
            return apology("VALUE ERROR")

        tem = int(shares)

        if shares - tem != 0.0:
            return apology("ENTER VALID NUMBER OF Shares")

        shares = tem

        if shares < 0:
            return apology("Invalid Share")
        if not symbol:
            return apology("MUST GIVE Symbol")

        stock = lookup(symbol.upper())
        if stock == None:
            return apology("Symbol Doen't exists")

        transaction_value = shares * stock["price"]
        user_id = session["user_id"]
        user_cash_db = db.execute(
            "SELECT cash FROM users WHERE id = :id", id=user_id)

        user_cash = user_cash_db[0]["cash"]
        if transaction_value > float(user_cash):
            return apology("Not Enough Money")

        updt_cash = float(user_cash) - transaction_value

        # updating users table
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   updt_cash, user_id)

        date = datetime.datetime.now()
        # updating track_buy table
        db.execute("INSERT INTO track_buy (user_id, symbol,shares,price,date) VALUES(?,?,?,?,?) ",
                   user_id, stock["symbol"], shares, stock["price"], date)

        price_stock = stock["price"]
        flash(f"Bought! {shares} of $ {transaction_value} {price_stock}")
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transaction_db = db.execute(
        "SELECT * FROM track_buy WHERE user_id = :id", id=user_id)
    return render_template("history.html", tansactions=transaction_db)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

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
        if not symbol:
            return apology("MUST GIVE Symbol")
        stock = lookup(symbol.upper())
        if stock == None:
            return apology("Symbol Doen't exists")
        return render_template("quoted.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username:
            return apology("ENTER A VALID USER NAME")

        if not password:
            return apology("ENTER A VALID PASSWORD")

        if not confirmation:
            return apology("ENTER A VALID CONFIRMATION")

        if password != confirmation:
            return apology("PASSWORD DON'T MATCH")

        hash = generate_password_hash(password)
        try:
            new_user = db.execute(
                "INSERT INTO users (username, hash) VALUES(?,?)", username, hash)
        except:
            return apology("UserName Already There")

        session["user_id"] = new_user

        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "GET":

        symbols_user = db.execute(
            "SELECT symbol FROM track_buy WHERE user_id= :id GROUP BY symbol HAVING SUM(shares) > 0", id=user_id)
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols_user])
    else:
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        try:
            shares = float(shares)
        except:
            return apology("VALUE ERROR")

        tem = int(shares)

        if shares - tem != 0.0:
            return apology("ENTER VALID NUMBER OF Shares")

        shares = tem

        if shares < 0:
            return apology("Invalid Share")

        user_shares = db.execute(
            "SELECT SUM(shares) AS shares from track_buy WHERE user_id= :id AND symbol= :sym GROUP BY symbol", id=user_id, sym=symbol)

        real_shares = user_shares[0]["shares"]
        print(real_shares)
        if shares > real_shares:
            return apology(f"YOU DONT HAVE THAT MUCH SHARES OF {symbol}")
        stock = lookup(symbol.upper())

        if stock == None:
            return apology("Symbol Doen't exists")

        transaction_value = shares * stock["price"]

        user_id = session["user_id"]

        user_cash_db = db.execute(
            "SELECT cash FROM users WHERE id = :id", id=user_id)

        user_cash = user_cash_db[0]["cash"]

        updt_cash = user_cash + transaction_value

        # updating users table
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   updt_cash, user_id)

        date = datetime.datetime.now()
        # updating track_buy table

        db.execute("INSERT INTO track_buy (user_id, symbol,shares,price,date) VALUES(?,?,?,?,?)",
                   user_id, stock["symbol"], (-1)*shares, stock["price"], date)
        flash(f"SOLD! {usd(transaction_value)}")
        return redirect("/")
