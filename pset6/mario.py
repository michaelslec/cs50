#!/bin/python3
import cs50


# get integer from 1-8
while True:
    height = cs50.get_int("Height: ")
    if height > 0 and height < 9:
        break

padding = height - 1

for i in range(height):
    for j in range(padding - i):
        print(' ', end="")

    for j in range(i + 1):
        print('#', end="")

    print('  ', end="")

    for j in range(i + 1):
        print('#', end="")

    print('')
