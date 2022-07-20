YES = "YES"
NO = "NO"

def balancedSums(values):
    if len(values) == 1:
        return YES
    if sum(values[1:]) == 0 or sum(values[:1]) == 0:
        return YES
    left_sum = values[0]
    right_sum = sum(values[2:])
    if left_sum == right_sum:
        return YES
    for i in range(2, len(values)):
        left_sum += values[i-1]
        right_sum -= values[i]
        if left_sum == right_sum:
            return YES
    return NO