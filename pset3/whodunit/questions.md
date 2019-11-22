# Questions

## What's `stdint.h`?

A file that declares primitive integer types that have a specified width, and limits of of these types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To apply structure to data files using structs or other methods.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

- 8
- 32
- 32
- 16

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

- ASCII: BM
- Hexadecimal: 0x42 0x4D
- Decimal: 66 77

## What's the difference between `bfSize` and `biSize`?

bfSize refers to the total size of the file, where as biSize refers to the size of the BITMAPINFOHEADER struct

## What does it mean if `biHeight` is negative?

The bitmap file will be read top-down with the origin in the top-left corner

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in `copy.c`?

permissions

## Why is the third argument to `fread` always `1` in our code?

To read only the first `sizeof(struct)` bits in the file

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

```c
// determine padding for scanlines
int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
```

`sizeof(RGBTRIPLE)` is three `BYTE` variables (`rgbtBlue`, `rgbtGreen`, `rgbtRed`).
Early on in bmp.h, we define `BYTE` by saying `typedef uint8_t  BYTE`, so `BYTE == 8 bytes`
Thus, `sizeof(RGBTRIPLE)` equates to `8 * 3 = 24`.

We are assuming `bi.biWidth` is `3`, so `bi.biWidth * sizeof(RGBTRIPLE)` equates to `3 * 24 = 72`.

Now, we have `4 - (72 % 4)`. `72 % 4 = 0`, so `4 - 0 = 4`.

Finally, `4 % 4 = 0`.

Thus, the answer is `0`.

## What does `fseek` do?

To move a file ptr's position without taking input or output

## What is `SEEK_CUR`?

Using `SEEK_CUR` in conjunction with `fseek` will move the ptr n bytes from the current position of the file ptr
