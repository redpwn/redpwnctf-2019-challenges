dp = [[1]]

# generate the table of nCr (dp[n][r])
def create_table():
    for i in range(1, 1000):
        cur = []
        for j in range(i + 1):
            if j == 0 or j == i:
                cur.append(1)
            else:
                cur.append(dp[i - 1][j - 1] + dp[i - 1][j])
        dp.append(cur)

# gets the value nCk from the dp
def c(n, k):
    if n < 0 or k > n:
        return 0
    return dp[n][k]

def main():
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    create_table()

    ans = 0

    for i in range(n):
        for pos in range(n):
            ans += (a[i] ^ b[pos]) * c(i, pos) * (2**(n - i - 1)) 

    print('%010d' % (ans % 10**10))


if __name__ == '__main__':
    main()

