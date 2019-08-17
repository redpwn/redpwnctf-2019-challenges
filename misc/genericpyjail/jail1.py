#!/usr/bin/env python 

from __future__ import print_function

print("wow! there's a file called flag.txt right here!")
banned = [
    "import",
    "ast",
    "eval",
    "=",
    "pickle",
    "os",
    "subprocess",
    "i love blacklisting words!",
    "input",
    "sys",
    "windows users",
    "print",
    "execfile",
    "hungrybox",
    "builtins",
    "open",
    "most of these are in here just to confuse you",
    "_",
    "dict",
    "[",
    ">",
    "<",
    ":",
    ";",
    "]",
    "exec",
    "hah almost forgot that one",
    "for",
    "@"
    "dir",
    "yah have fun",
    "file"
]

while 1:
    print(">>>", end=' ')
    data = raw_input()
    for no in banned:
        if str(no).lower() in str(data).lower():
            print("That's not allowed here")
            break
    else: # this means nobreak
        data = eval(data)
        if("code" not in str(data)):
            data = str(data)
        exec(data)
