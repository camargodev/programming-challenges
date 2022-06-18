import os

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

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')
    t = int(input().strip())
    for t_itr in range(t):
        n = int(input().strip())
        grid = []
        for _ in range(n):
            grid_item = input()
            grid.append(grid_item)
        result = grid_challenge(n, grid)
        fptr.write(result + '\n')
    fptr.close()