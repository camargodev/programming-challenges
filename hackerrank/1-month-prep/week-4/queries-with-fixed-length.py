def solve(array, queries):
    min_values = []
    for query in queries:
        sub_array = array[0:query]
        max_value = max(sub_array)
        min_value = max_value
        offset = 0
        while query+offset < len(array):
            removed_max = (sub_array[offset%query] == max_value)
            sub_array[offset%query] = array[query+offset]
            if removed_max:
                max_value = max(sub_array)
                if max_value < min_value:
                    min_value = max_value
            offset += 1
        min_values.append(min_value)
    return min_values
            
