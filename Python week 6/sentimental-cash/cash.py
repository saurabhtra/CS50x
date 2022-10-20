# TODO
from sys import exit
from cs50 import get_float


def main():
    # asking how many dollars does the customer is owes
    dollars = get_dollars()
    print(f"dollars{dollars}")

    # calculating the number of quarters to give the customer

    quarters = cal_quarters(dollars)

    dollars = dollars - quarters * 25

    # calculating the no of dimes

    dimes = cal_dimes(dollars)
    dollars = dollars - dimes * 10

    # calculating the no. of nickels
    nickels = cal_nickels(dollars)
    dollars = dollars - nickels * 5

    # calculating pennies
    pennies = cal_pennies(dollars)
    dollars = dollars - pennies * 1

    coins = quarters + dimes + nickels + pennies
    print(coins)

# implementation of get_dollar function


def get_dollars():
    # looping the user to coprate
    while True:
        try:
            n = get_float("Changed owed: ")
            try:
                if n > 0:
                    # if all condition are setisfies the finally convert dollars into pennies and then into int
                    return int(n * 100)
            except:
                pass
        except ValueError:
            pass

# implementing function to calculate max no of numbers of quarters


def cal_quarters(dollars):
    if dollars >= 25:
        return int(dollars / 25)
    else:
        return 0


def cal_dimes(dollars):
    if dollars >= 10:
        return int(dollars / 10)
    else:
        return 0


def cal_nickels(dollars):
    if dollars >= 5:
        return int(dollars / 5)
    else:
        return 0


def cal_pennies(dollars):
    if dollars >= 1:
        return int(dollars/1)
    else:
        return 0


"__name__" == "__main__"

main()