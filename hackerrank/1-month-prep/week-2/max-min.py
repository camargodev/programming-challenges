def max_min(length, values):
    values.sort()
    diffs = [values[i]-values[i-length+1] for i in range(length-1, len(values))]
    return min(diffs)