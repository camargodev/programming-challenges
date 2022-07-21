from collections import deque

def roads_and_libraries(num_cities, cost_lib, cost_road, connections):
    if cost_lib < cost_road:
        return cost_lib * num_cities
    number_of_subgraphs = calculate_number_of_subgraphs(num_cities, connections)
    total_lib_cost = number_of_subgraphs * cost_lib
    total_road_cost = (num_cities - number_of_subgraphs) * cost_road
    return total_lib_cost + total_road_cost
    
def calculate_number_of_subgraphs(n, connections):
    visited = set()
    edges = [set() for _ in range(n)]
    for connection in connections:
        a, b = connection
        edges[a-1].add(b-1)
        edges[b-1].add(a-1)
    number_of_subgraphs = 0
    for node in range(n):
        if node not in visited:
            bfs(node, n, visited, edges)
            number_of_subgraphs += 1
    return number_of_subgraphs

def bfs(node, n, visited, edges):
    deck = deque()
    visited.add(node)
    deck.append(node)
    while deck:
        current_node = deck.pop()
        node_edges = edges[current_node]
        for edge_destiny in node_edges:
            if edge_destiny not in visited:
                visited.add(edge_destiny)
                deck.append(edge_destiny)
 