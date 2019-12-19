#!/bin/python3
import cs50
import sys


def check_keyword():
    if len(sys.argv) != 2:
        sys.exit("Usage: ./vigenere.py keyword")
    elif not sys.argv[1].isalpha():
        sys.exit("Keyword must be alphabetical")

    return sys.argv[1].lower()


def hash(char):
    if char.isupper():
        return ord(char) - ord('A')
    else:
        return ord(char) - ord('a')


def encipher(plaintext, k):
    k_index = 0
    ciphertext = ""

    for c in plaintext:
        if c.isalpha():
            shift_value = hash(k[k_index])
            # print("shift_value:", shift_value)
            k_index = (k_index + 1) % len(k)
            # print("k_index:", k_index)
            shift_index = (hash(c) + shift_value) % 26
            # print("shift_index:", shift_index)

            if c.isupper():
                shift_index += ord('A')
            else:
                shift_index += ord('a')

            # print("chr(shift_index):", chr(shift_index))
            ciphertext += chr(shift_index)
        else:
            ciphertext += c

    return ciphertext


def main():
    k = check_keyword()
    plaintext = cs50.get_string("plaintext: ")
    ciphertext = encipher(plaintext, k)
    print("ciphertext:", ciphertext)


if __name__ == "__main__":
    main()
