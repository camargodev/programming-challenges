PLACING = 0
PLAYING = 1
EMPTY = -1
NEW_BOMB = 3

def make_starter_grid(grid):
    converted_grid = []
    for row in grid:
        converted_row = []
        for cell in row:
             content = EMPTY if cell == '.' else NEW_BOMB-1
             converted_row.append(content)
        converted_grid.append(converted_row)
    return converted_grid
    
def make_output_grid(grid):
    converted_grid = []
    for row in grid:
        converted_row = ''
        for cell in row:
             content = '.' if cell == EMPTY else 'O'
             converted_row += content
        converted_grid.append(converted_row)
    return converted_grid

def define_blowed_cells(i, j):
    return set([(i-1,j),(i,j-1),(i+1,j),(i,j+1)])
    
def consume_grid(action, grid, rows, columns):
    blowed_cells = []
    for i in range(rows):
        for j in range(columns):
            if grid[i][j] > 0:
                grid[i][j] -= 1
                
            if grid[i][j] == EMPTY:
                grid[i][j] = NEW_BOMB
            if grid[i][j] == 0:
                grid[i][j] = EMPTY
                blowed_cells += define_blowed_cells(i, j)
    
    for coord in blowed_cells:
        i, j = coord
        if i in range(rows) and j in range(columns):
            grid[i][j] = EMPTY
                
    return grid
    
def bomber_man(seconds, grid, rows, columns):
    if seconds == 0:
        return grid
    
    grid = make_starter_grid(grid)

    seconds -= 1
    grid = consume_grid(PLAYING, grid, rows, columns)
    if seconds == 0:
        return make_output_grid(grid)
    
    seconds = seconds % 4
    
    while seconds > 0:
        print(seconds)
        grid = consume_grid(PLAYING, grid, rows, columns)
        seconds -= 1
    
    return make_output_grid(grid)