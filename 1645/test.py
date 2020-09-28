N = 6
K = 2

INF = 10001

seq = [3, -2, 5, -1, 7, 8]
mtx = [[-1 for x in range(N)] for y in range(K)] 
#  3: 1 + (5) = 3
# -2: 1 + (5) = 3 
#  5: 1 + (7) = 2
# -1: 1 + (7) = 2
#  7: 1
#  8: 0 



def count():
    if K == 1: 
        return N
    curr = N-K
    count = 0
    while curr >= 0:
        nextv = curr+1
        minnext = INF
        minnextidx = INF
        # print("\nChecking index " + str(curr) + " [val: " + str(seq[curr]) + "]")
        while nextv < N:
            if seq[nextv] > seq[curr] and seq[nextv] < minnext:
                minnext = seq[nextv]
                minnextidx = nextv
            nextv += 1
        currcount = 0
        # print("  minnext = " + str(minnextidx) + " [val: " + str(seq[minnextidx]) + "]")
        if minnextidx != INF and mtx[0][minnextidx] >= 0:
            currcount = mtx[0][minnextidx]
            # print("  got " + str(currcount) + " from cache")
        nextv = curr+1
        while nextv <= minnextidx:
            if seq[curr] < seq[nextv]:
                currcount += 1
                mtx[0][curr] = currcount
                # print("  put " + str(currcount) + " on cache for " + str(curr))
            nextv += 1
        count += currcount
        # print(seq)
        # print(mtx)
        curr -= 1
    return count 
val = count()
print(val)
