def most_repeat(offset, length, string):
    index = offset
    count = [0] * 256
    while index < len(string):
        count[ord(string[index])] += 1
        index += length
    m = [0, 0]
    for i in range(len(count)):
        if count[i] > m[0]:
            m[0] = count[i]
            m[1] = i
    return chr(m[1])


def repeat_count(length, string):
    result = []
    for i in range(length):
        result.append(most_repeat(i, length, string))
    return result


def generate_key(expected, recieved):
    result = ""
    expected = [expected] * len(recieved)
    for i in range(len(recieved)):
        result += chr(ord(expected[i]) ^ ord(recieved[i]))
    return result


def main():
    f = open("output.txt", "r")
    string = f.read()
    repeats = repeat_count(38, string)
    print(generate_key(" ", repeats))


main()