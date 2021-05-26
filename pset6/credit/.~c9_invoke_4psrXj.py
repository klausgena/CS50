from cs50 import get_int

# this function checks if a credit card
# number is valid or not.


def prompt_for_number():
    number = get_int("What's your credit card number? ")
    return numberjjjjjjjjjjjjjjjj


def check_brand(card):
    # print brand
    length = calculate_length(card)
    first_digits = get_first_digits(card)
    brand = ""
    if length < 13 or length > 16:
        brand = "INVALID"
    elif (length == 13 or length == 16) and (int(first_digits / 10)) == 4:
        brand = "VISA"
    elif length == 15 and first_digits == 34 or first_digits == 37:
        brand = "AMEX"
    elif length == 16:
        for x in range(51, 56):
            if first_digits == x:
                brand = "MASTERCARD"
                break
        else:
            brand = "INVALID"
    else:
        brand = "INVALID"
    return brand


def checksum(card):
    # calculate checksum
    valid = False
    length = calculate_length(card)
    sum_1 = 0
    sum_2 = 0
    total = 0
    new_number = card
    number = 0
    for x in range(length):
        if x % 2 != 1:
            number = new_number % 10
            new_number = int(new_number / 10)
            sum_1 = sum_1 + number
        else:
            number = new_number % 10
            new_number = int(new_number / 10)
            number = number * 2
            if number > 9:
                a = int(number / 10)
                b = number % 10
                number = a + b
            sum_2 = sum_2 + number
    total = sum_1 + sum_2
    if total % 10 == 0:
        valid = True
    else:
        valid = False
    return valid


def calculate_length(number):
    # how long is the card number?
    length = 0
    modulo = 10
    new_number = 0
    while number != new_number:
        new_number = number % modulo
        length = length + 1
        modulo = modulo * 10
    return length


def get_first_digits(number):
    # what are the first 2 digits?
    length = calculate_length(number)
    divider = 1
    for x in range(length - 2):
        divider = int(divider * 10)
    return int(number / divider)


def main():
    # check card number for different companies
    card = prompt_for_number()
    brand = check_brand(card)
    valid = checksum(card)
    if (valid == True):
        print(brand)
    else:
        print("INVALID")


main()
