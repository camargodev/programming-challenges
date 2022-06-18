import os

def diagonal_difference(n, matrix):
    main_diagonal_sum = 0
    other_diagonal_sum = 0
    for i in range(n):
        main_diagonal_sum += matrix[i][i]
        other_diagonal_sum += matrix[n-i-1][i]
    return abs(main_diagonal_sum-other_diagonal_sum)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')
    n = int(input().strip())
    matrix = []
    for _ in range(n):
        matrix.append(list(map(int, input().rstrip().split())))
    result = diagonal_difference(n, matrix)
    fptr.write(str(result) + '\n')
    fptr.close()