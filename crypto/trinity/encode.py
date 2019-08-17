import sys

morse_table = {
    "a": ".-",
    "b": "-...",
    "c": "-.-.",
    "d": "-..",
    "e": ".",
    "f": "..-.",
    "g": "--.",
    "h": "....",
    "i": "..",
    "j": ".---",
    "k": "-.-",
    "l": ".-..",
    "m": "--",
    "n": "-.",
    "o": "---",
    "p": ".--.",
    "q": "--.-",
    "r": ".-.",
    "s": "...",
    "t": "-",
    "u": "..-",
    "v": "...-",
    "w": ".--",
    "x": "-..-",
    "y": "-.--",
    "z": "--..",
    " ": " ",
    "\n": ""
}

trinity_table = {
    ".": "0",
    "-": "1",
    " ": "2"
}

def morse_encode(s):
    return ' '.join([ morse_table[c] for c in s ])

def trinity_encode(s):
    return ''.join([ trinity_table[c] for c in morse_encode(s) ])

plaintext = sys.stdin.read()
ciphertext = trinity_encode(plaintext)
print(ciphertext)
