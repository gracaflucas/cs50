from cs50 import get_int


def main():
    while True:
        ccNumber = get_int("Card Number: ")
        if ccNumber >= 0:
            break

    if check_sum(ccNumber):
        print_brand(ccNumber)
    else:
        print("INVALID")


def check_sum(ccNumber):
    sum = 0
    digitCount = 0

    while ccNumber > 0:
        if digitCount % 2 == 0:
            sum += ccNumber % 10
        else:
            digit = 2 * (ccNumber % 10)
            sum += digit // 10 + digit % 10
        ccNumber //= 10
        digitCount += 1

    return (sum % 10 == 0)


def print_brand(ccNumber):

    ccNumber_str = str(ccNumber)

    if ccNumber_str.startswith(("34", "37")) and len(ccNumber_str) == 15:
        print("AMEX")
    elif ccNumber_str.startswith(("51", "52", "53", "54", "55")) and len(ccNumber_str) == 16:
        print("MASTERCARD")
    elif ccNumber_str.startswith("4") and (len(ccNumber_str) == 13 or len(ccNumber_str) == 16) and int(ccNumber_str[0]) == 4:
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
