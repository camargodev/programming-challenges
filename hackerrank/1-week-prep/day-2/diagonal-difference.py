def diagonal_difference(n, matrix):
    main_diagonal_sum = 0
    other_diagonal_sum = 0
    for i in range(n):
        main_diagonal_sum += matrix[i][i]
        other_diagonal_sum += matrix[n-i-1][i]
    return abs(main_diagonal_sum-other_diagonal_sum)