import sys

morse_table = {
    ".-": "a",
    "-...": "b",
    "-.-.": "c",
    "-..": "d",
    ".": "e",
    "..-.": "f",
    "--.": "g",
    "....": "h",
    "..": "i",
    ".---": "j",
    "-.-": "k",
    ".-..": "l",
    "--": "m",
    "-.": "n",
    "---": "o",
    ".--.": "p",
    "--.-": "q",
    ".-.": "r",
    "...": "s",
    "-": "t",
    "..-": "u",
    "...-": "v",
    ".--": "w",
    "-..-": "x",
    "-.--": "y",
    "--..": "z",
    " ": " ",
    "": " ",
}

trinity_table = {
    "0": ".",
    "1": "-",
    "2": " ",
    "\n": ""
}

def morse_decode(s):
    letters = s.split(' ')
    return ''.join([ morse_table[c] for c in letters ])

def trinity_decode(s):
    morse = ''.join([ trinity_table[c] for c in s ])
    return morse_decode(morse)

ciphertext = sys.stdin.read()
plaintext = trinity_decode(ciphertext)
print(plaintext)
