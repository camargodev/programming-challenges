def throw_card(n):
    ls = [i+1 for i in range(n)]
    retls = []
    while len(ls) > 1:
        sz = len(ls)
        odd_ls = ls[::2]
        retls += odd_ls
        ls = ls[1::2]
        if sz % 2 != 0:
            first = ls[0]
            ls = ls[1:sz] + [first]

    return retls, ls[0]

while True:
    n = int(input())
    if n == 0:
        break
    retls, remain = throw_card(n)
    str_retls = ", ".join([str(num) for num in retls])
    print("Discarded cards: " + str(str_retls))
    print("Remaining card: " + str(remain))