from collections import deque

def build_edges_dict(n, edges):
    edges_dict = dict()
    for i in range(n):
        edges_dict[i+1] = []
    for edge in edges:
        node_from = edge[0]
        node_to = edge[1]
        edges_dict[node_from].append(node_to)
        edges_dict[node_to].append(node_from)
    return edges_dict

def bfs(n, m, edges, s):
    costs = [-1]*n
    edges_dict = build_edges_dict(n, edges)
    visited = set()
    queue = deque()
    queue.append((s, 1))
    visited.add(s)
    while queue:
        node, cost = queue.popleft()
        for node_to in edges_dict[node]:
            if node_to in visited:
                continue
            costs[node_to-1] = cost*6
            queue.append((node_to, cost+1))
            visited.add(node_to)
        costs.pop(s-1)
    return costs