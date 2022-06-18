def flipping_matrix(matrix):
    n = len(matrix)
    submatrix_size = n//2
    max_sum = 0
    for i in range(submatrix_size):
        for j in range(submatrix_size):
            val_1 = matrix[i][j]
            val_2 = matrix[n-i-1][j]
            val_3 = matrix[i][n-j-1]
            val_4 = matrix[n-i-1][n-j-1]
            max_val = max([val_1, val_2, val_3, val_4])
            max_sum += max_val
    return max_sum