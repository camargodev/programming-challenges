def counting_sort(numbers):
    ocurrences = [0]*100
    for number in numbers:
        ocurrences[number] += 1
    return ocurrences