def super_digit(n, k):
    p = int(n)
    super_digit = calculate_super_digit(p)*k
    while not is_super_digit(super_digit):
        super_digit = calculate_super_digit(super_digit)
    return super_digit
    
def calculate_super_digit(n):
    super_digit = 0
    for digit in str(n):
        super_digit += int(digit)
    return super_digit
    
def is_super_digit(n):
    return n < 10