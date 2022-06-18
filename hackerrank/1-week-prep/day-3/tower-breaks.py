import os

def tower_breakers(n, m):
    if m == 1:
        return 2
    return 2 if n % 2 == 0 else 1

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')
    t = int(input().strip())
    for t_itr in range(t):
        first_multiple_input = input().rstrip().split()
        n = int(first_multiple_input[0])
        m = int(first_multiple_input[1])
        result = tower_breakers(n, m)
        fptr.write(str(result) + '\n')
    fptr.close()