from collections import deque

WALL = 'X'

class Node:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        
    def __eq__(self, other):
        if isinstance(other, Node):
            return self.x == other.x and self.y == other.y
        return False

def calculate_neighboors(grid, n, node):
    neighboors = []
    x, y = node.x, node.y
    
    offset = 0
    while x+offset+1 < n and grid[x+offset+1][y] != WALL:
        offset += 1
        neighboors.append((x + offset, y))
    offset = 0
    while x-offset-1 >= 0 and grid[x-offset-1][y] != WALL:
        offset += 1
        neighboors.append((x - offset, y))
    offset = 0
    while y+offset+1 < n and grid[x][y+offset+1] != WALL:
        offset += 1
        neighboors.append((x, y + offset))
    offset = 0
    while y-offset-1 >= 0 and grid[x][y-offset-1] != WALL:
        offset += 1
        neighboors.append((x, y - offset))
      
    neighboor_nodes = [Node(node[0], node[1]) for node in neighboors]
    return neighboor_nodes

def minimum_moves(grid, n, start_x, start_y, goal_x, goal_y):
    queue = deque()
    visited = set()
    
    start_node = Node(start_x, start_y)
    goal = Node(goal_x, goal_y)
    queue.append((1, start_node))
    visited.add((start_node.x, start_node.y))
    
    while queue:
        cost, node = queue.popleft()
        neighboors = calculate_neighboors(grid, n, node)
        for neighboor in neighboors:
            if neighboor == goal:
                return cost
            if (neighboor.x, neighboor.y) in visited: 
                continue
            queue.append((cost + 1, neighboor))
            visited.add((neighboor.x, neighboor.y))