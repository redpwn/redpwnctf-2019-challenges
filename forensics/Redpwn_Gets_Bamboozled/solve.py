#!/usr/bin/env python3

from PIL import Image

with open('data.txt', 'r') as f:
    data = f.readlines()

# Get image dimensions
(w, h) = tuple(map(int, data[0].split()))

# Get pixels
pixels = list(map(lambda pix: tuple(map(int, pix[1:-1].split())),
                  data[1].split(', ')))

# Plot pixels
im = Image.new("RGB", (w, h))
for y in range(h):
    for x in range(w):
        im.putpixel((x, y), pixels[y * w + x])

# Image created is a red background with grey dots, where each hex
# digit of the dot color is the same. Concatenate the hex digits
# together to decode the image.
num = 0
for y in range(50, 750 + 1, 100):
    for x in range(100, 500 + 1, 100):
        pix = im.getpixel((x, y))
        # If the pixel is not the red background
        if pix != (0xff, 0x0c, 0x00):
            num <<= 4
            num |= pix[0] & 0xf


def int_to_str(i):
    s = ''
    while i != 0:
        s += chr(i & 0xFF)
        i >>= 8
    return s[::-1]


print(int_to_str(num))
