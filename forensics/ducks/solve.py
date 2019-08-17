import csv

# Load data
f = open('download.csv')
reader = csv.reader(f)
data = []
for row in reader:
    data.append(row)
f.close()

num_rows = len(data) - 1
num_cols = len(data[0]) - 1

sums = [0] * num_cols
for x in range(num_cols):
    for y in range(num_rows):
        if len(data[y + 1][x + 1]) == 0:
            val = 1
        else:
            val = 0
        sums[x] += val
print(sums)
ciphertext = ''
for col in data[0][1:]:
    ciphertext += col[-1]
plaintext = ''
for i, sum in enumerate(sums):
    if sum > 10500:
        plaintext += ciphertext[i]
print(plaintext)
