def grid_challenge(n, grid):
    sorted_grid = []
    m = len(grid[0])
    for row in grid:
        sorted_grid.append(''.join(sorted(row)))
    for i in range(m):
        column_values = []
        for j in range(n):
            column_values.append(sorted_grid[j][i])
        if column_values != sorted(column_values):
            return 'NO'
    return 'YES'