def two_arrays(min_value, values_a, values_b):
    values_a.sort()
    values_b.sort(reverse=True)
    for i in range(len(values_a)):
        value_a = values_a[i]
        value_b = values_a[i]
        if value_a+value_b < min_value:
            return "NO"
    return "YES"