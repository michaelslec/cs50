#!/bin/python3
from cs50 import get_string
from sys import argv, exit
import re

alphabet = re.compile('[^a-zA-Z]')


def profanity(tokenized, dictionary):
    bleeped_sentence = ""
    for word in tokenized:
        word_alpha = alphabet.sub('', word)

        if word_alpha.lower() in dictionary:
            bleeped_sentence += "*" * len(word_alpha) \
                                + word[len(word_alpha):] \
                                + " "
        else:
            bleeped_sentence += word + " "

    return bleeped_sentence


def main():
    if len(argv) != 2:
        exit("Usage: ./bleep.py file")

    banned_words = set(line.strip() for line in open(argv[1]))

    user_input = get_string("input: ").split()

    christian = profanity(user_input, banned_words)
    print(christian)


if __name__ == "__main__":
    main()
