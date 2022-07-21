def birthday(values, target_sum, length):
    def count(current, target):
        return 1 if current == target else 0
    
    current_sum = sum(values[:length])
    possibilities = count(current_sum, target_sum)
    for i in range(length, len(values)):
        current_sum = current_sum - values[i-length] + values[i]
        possibilities += count(current_sum, target_sum)
    return possibilities