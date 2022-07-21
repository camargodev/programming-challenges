def arrayManipulation(n, queries):
    values = [0 for _ in range(n)]
    for query in queries:
        start, end, value = query
        values[start-1] += value
        if end < len(values):
            values[end] -= value
    
    max_value = 0
    current_value = 0
    for value in values:
        current_value += value
        if current_value > max_value:
            max_value = current_value 
                
    return max_value