# TODO
from sys import exit


def main():

    # this function will take input from user and check the codition of the input
    num = condition_checker()

    # this function will validate the number is of and credit card or not
    validate_checker(num, len(num))


def condition_checker():
    while True:
        try:
            num = input("Number: ")
            digit = len(num)
            x = int(num)
            if digit == 15 or digit == 16 or digit == 13:
                return num
            else:
                print("INVALID")
                exit(1)
            # try:
            #     if digit == 15 or digit == 16 or digit == 13:
            #         return num
            # except:
            #     print("INVALID")
            #     pass

        except ValueError:
            print("INVALID")
            exit(1)


def validate_checker(num, n):
    even_sum = 0
    odd_sum = 0
    first_two_digit = int(int(num) / pow(10, n - 2))
    # print(f"first_2_digit = {first_two_digit}")
    first_digit = int(int(num) / pow(10, n - 1))

    count = n
    i = count - 1
    temp = int(num)
    temp2 = int(num)
    while count > 0:
        temp_int = 0
        temp = int(temp / 10)
        temp_int = (temp % 10) * 2
        temp_int = temp_int % 10 + int(temp_int / 10)
        even_sum += temp_int
        temp = temp / 10

        odd_sum += temp2 % 10

        temp2 = int(temp2 / 100)
        count = count - 2

    final_sum = even_sum + odd_sum
    # print(final_sum % 10, final_sum, even_sum, odd_sum)

    if final_sum % 10 == 0:
        if first_two_digit == 34 or first_two_digit == 37:
            print("AMEX")
        elif first_two_digit >= 51 and first_two_digit <= 55:
            print("MASTERCARD")
        elif first_digit == 4:
            print("VISA")
        else:
            print("INVALID")
            exit(1)

    else:
        print("INVALID")
        exit(1)


main()
