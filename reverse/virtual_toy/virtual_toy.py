def encrypt(flag):
    ciphertext = []
    for c in flag:
        x = ord(c)
        x += 10
        x *= 1337
        x //= 191
        x ^= 0xfff
        x = -x
        x = ~x
        x <<= 2
        ciphertext.append(x)
    return ciphertext

def check(flag, ciphertext):
    if len(flag) != len(ciphertext):
        return False
    for i in range(0, len(flag)):
        x = ord(flag[i])
        x += 10
        x *= 1337
        x //= 191
        x ^= 0xfff
        x = -x
        x = ~x
        x <<= 2
        if x != ciphertext[i]:
            return False
    return True

flag = 'flag{qemu_is_better_09831912393}' # 32 bytes
ciphertext = encrypt(flag)

print(ciphertext[::-1])
print('Virtual Toy (C) 1991 VMBox Technologies')
password = input('Enter access code: ')
if check(password, ciphertext):
    print('Access granted')
else:
    print('Error')
