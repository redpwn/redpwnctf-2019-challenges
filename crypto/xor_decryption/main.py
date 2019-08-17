def xor(string, key):
    output = ""
    for i in range(len(string)):
        output += chr(ord(string[i]) ^ ord(key[i % len(key)]))
    return output


def main():
    f = open("megawatt.txt", "r")
    string = f.read()
    key = "flag{7ux'5_un6u3554bl3_x0r_k3y_973068}"
    output = xor(string, key)
    o = open("output.txt", "w+")
    o.write(output)
    o.close()


main()
