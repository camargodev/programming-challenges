def binary_to_decimal(bit_array):
    exp = 0
    decimal = 0
    for bit in bit_array:
        decimal += bit * (2**exp)
        exp += 1
    return decimal

def flipping_bits(decimal):
    total = binary_to_decimal([1]*32)
    return total-decimal