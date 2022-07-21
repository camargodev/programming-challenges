from collections import deque

def build_edges_dict(edges):
    edges_dict = dict()
    for edge in edges:
        if edge[0] not in edges_dict:
            edges_dict[edge[0]] = []
        if edge[1] not in edges_dict:
            edges_dict[edge[1]] = []
        edges_dict[edge[1]].append(edge[0])
        edges_dict[edge[0]].append(edge[1])
    return edges_dict

def get_connected_nodes(edges_dict):
    return edges_dict.keys()

def bfs(starting_node, visited, edges_dict):
    node_deque = deque()
    node_deque.append(starting_node)
    visited.add(starting_node)
    
    while node_deque:
        current_node = node_deque.pop()
        for neighboor in edges_dict[current_node]:
            if neighboor in visited:
                continue
            node_deque.append(neighboor)
            visited.add(neighboor)
    
    return visited

def componentsInGraph(edges):
    edges_dict = build_edges_dict(edges)
    nodes = get_connected_nodes(edges_dict)
    visited = set()
    component_sizes = []
    last_component_size = 0
    
    for starting_node in nodes:
        if starting_node in visited:
            continue
        visited = bfs(starting_node, visited, edges_dict)
        component_sizes.append(len(visited)-last_component_size)
        last_component_size = len(visited)
    
    return [min(component_sizes), max(component_sizes)]