from cs50 import get_string

txt = get_string("Text: ")

letters = 0

for c in txt:
    if c.isalpha():
        letters += 1

words = len(txt.split())

sentences = txt.count(".") + txt.count("?") + txt.count("!")

L = letters / words * 100
S = sentences / words * 100

grade = 0.0588 * L - 0.296 * S - 15.8

if grade < 1:
    print("Before Grade 1\n")
elif grade >= 16:
    print("Grade 16+\n")
else:
    print(f"Grade {round(grade)}\n")
