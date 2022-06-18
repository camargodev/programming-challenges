def mini_max_sum(numbers):
    total = sum(numbers)
    min_number = min(numbers)
    max_number = max(numbers)
    min_sum = total - max_number
    max_sum = total - min_number
    print("%s %s" % (min_sum, max_sum))