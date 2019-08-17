from PIL import Image

IMG = Image.open('lol.png')

def msb(channel):
    plaintext = ''
    c = 0
    count = 0
    (width, height) = IMG.size
    for x in range(width):
        for y in range(height):
            if count == 8:
                plaintext += chr(c)
                count = 0
                c = 0
            pixel = IMG.getpixel((x, y))
            bit = pixel[channel] >> 7
            c <<= 1
            c |= bit
            count += 1
    return plaintext

for channel in range(3):
    print('Trying channel ' + str(channel))
    data = msb(channel)
    if 'flag{' in data:
        flag_end = data.find('}')
        flag = data[:flag_end + 1]
        print(flag)
        break
