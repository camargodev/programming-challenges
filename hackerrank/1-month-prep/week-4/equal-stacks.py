FIRST = 0
    
def summed_stack(stack):
    total = 0
    summed_stack = []
    stack_sum = sum(stack)
    for value in stack:
        summed_stack.append(stack_sum-total)
        total += value
    return summed_stack

def get_current_heights(n, stacks, indexes):
    return [stacks[i][indexes[i]] for i in range(n)]

def all_equal(n, stacks, indexes):
    values = get_current_heights(n, stacks, indexes)
    first_value = values[FIRST]
    for value in values:
        if not (value == first_value):
            return False
    return True

def can_shorten_stack(n, indexes, lenghts):
    for i in range(n):
        if indexes[i] >= lenghts[i]:
            return False
    return True

def get_height(stacks, indexes):
    return stacks[FIRST][indexes[FIRST]]    

def shorten_highest_stack(n, stacks, indexes):
    heights = get_current_heights(n, stacks, indexes)
    max_height = max(heights)
    for i in range(n):
        if max_height == heights[i]:
            indexes[i] += 1
    return indexes