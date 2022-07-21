def to_bin(dec):
    return bin(dec)[2:]

def to_dec(bin_val):
    return int(bin_val, 2)

def calculate_allowed_digits(bin_digit):
    return 2 if bin_digit == '0' else 1
    
def sum_equals_xor(max_value):
    if max_value == 0:
        return 1
    combinations = 1
    for bin_digit in to_bin(max_value):
        allowed_digits = calculate_allowed_digits(bin_digit)
        combinations *= allowed_digits
    return combinations