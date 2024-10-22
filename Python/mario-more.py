def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            print("Invalid input. Positive interger only. ")


height = get_int("Height? ")

while height > 8 or height < 1:
    print("Height must be between 1 and 8")
    height = get_int("Height? ")

for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i + "  " + "#" * i)
