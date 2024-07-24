import cs50


# count num of letters per 100 words
# count num of sentences per 100 words

text = cs50.get_string("Text: ")

numofWords = 1
numofSents = 0
numofLets = 0
for c in text:
    if c == ' ':
        numofWords += 1
    elif c in {'.', '?', '!'}:
        numofSents += 1
    elif c.isalpha():
        numofLets += 1

L = numofLets/numofWords * 100
S = numofSents/numofWords * 100

index = round(0.0588 * L - 0.296 * S - 15.8)

if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")



