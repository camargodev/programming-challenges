MOD = 1000007

while True:
    val = input()
    if val == 0:
        break
    res = (11*val**2 + val**4)/12
    res = res % MOD
    print(res)