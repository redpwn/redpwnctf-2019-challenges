# Make substitution cipher from layer 2 to layer 3

import random

f = open('layer_3.txt', 'r')
plaintext = f.read()
f.close()

header = """OMG WOW NO WAY
IT'S UTF8 GARBAGE AMONGST THE REGULAR GARBAGE!
IT MUST BE A SUBSTITUTION CIPHER!!!!!
"""

x = 'abcdefghijklmnopqrstuvwxyz'
y = 'αβγδεζηθικλμξπρστυφχψω½⅓⅔¼¾⅕⅖⅗⅘⅙⅚⅐⅛⅜⅝⅞⅑⅒غظضذخثتشرقصفعسنملكيطحزوهدجب诶比西迪伊艾吉艾艾杰开艾艾艾哦屁吉艾艾提伊维豆艾吾贼x*'
lst = list(y)
random.seed(0)
random.shuffle(lst)
y = ''.join(lst)[0:len(x)]
trans = str.maketrans(x, y)
ciphertext = plaintext.translate(trans)
output = header + ciphertext
print(output, end='')
