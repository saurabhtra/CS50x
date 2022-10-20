# TODO


def main():

    # taking the text from user and storing it in text variable
    text = input("Text : ")
    w = count_word(text)
    l = count_letter(text)
    s = count_sentence(text)
    grade(l, s, w)


# implementing function for calculating letters in the text
def count_letter(text):
    count = 0
    for i in range(len(text)):
        if text[i].isalpha():
            count += 1
    return count


# implementing function for calculating words in the text
def count_word(text):
    count = 0
    for i in range(len(text)):
        if text[i] == ' ':
            count += 1
    return count + 1


# implementing function for calculating sentences in the text
def count_sentence(text):
    count = 0
    for i in range(len(text)):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':
            count += 1
    return count


# Implementing grade function for calculating Grade of the the text
def grade(l, s, w):
    L = float((l * 100.00) / w)
    S = float((s * 100.00) / w)
    grade = round(0.0588 * L - 0.296 * S - 15.8)
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


"__name__" == "__main__"

main()