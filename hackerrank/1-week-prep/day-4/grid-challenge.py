def grid_challenge(rows, grid):
    sorted_grid = []
    cols = len(grid[0])
    for row in grid:
        sorted_grid.append(sorted(row))
    for i in range(cols):
        column_values = []
        for j in range(rows):
            column_values.append(sorted_grid[j][i])
        if column_values != sorted(column_values):
            return 'NO'
    return 'YES'