def get_positives(arr):
    return [num for num in arr if num > 0]

def max_subarray_sum(array):
    max_so_far = min(array)
    max_ending_here = 0
    
    for value in array:
        max_ending_here += value
        max_so_far = max(max_so_far, max_ending_here)
        max_ending_here = max(max_ending_here, 0)
        
    return max_so_far
    
def max_subarray(arr):
    positives = get_positives(arr)
    if len(positives) == 0:
        max_non_positive = max(arr)
        return [max_non_positive, max_non_positive]
    return [max_subarray_sum(arr), sum(positives)]