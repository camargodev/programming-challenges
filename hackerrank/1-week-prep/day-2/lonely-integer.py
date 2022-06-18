def lonely_integer(numbers):
    unique_numbers = set(numbers)
    for number in unique_numbers:
        if numbers.count(number) == 1:
            return number