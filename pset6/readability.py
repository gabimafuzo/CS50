from cs50 import get_string

text = get_string("Text: ")

letters = 0
words = 1
sentences = 0

for i in range(len(text)):
    if 'A' <= text[i] <= 'Z' or 'a' <= text[i] <= 'z':
        letters += 1
    elif text[i] == ' ':
        words += 1
    elif text[i] in ('!', '.', '?'):
        sentences += 1

# Coleman-Liau index
# Here, L is the average number of letters per 100 words in the text, and S is the average
# number of sentences per 100 words in the text.

L = (letters * 100) / words
S = (sentences * 100) / words

index = ((0.0588 * L) - (0.296 * S)) - 15.8


Grade = round(index)

if (Grade >= 16):
    print("Grade 16+")
elif (Grade < 1):
    print("Before Grade 1")
else:
    print(f"Grade {Grade}")
