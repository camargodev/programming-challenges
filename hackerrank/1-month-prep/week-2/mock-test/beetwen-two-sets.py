def is_array_factor_of_number(number, array):
    for factor in array:
        if number % factor != 0:
            return False
    return True

def is_number_factor_of_array(factor, array):
    for value in array:
        if value % factor != 0:
            return False
    return True

def get_total_x(array_a, array_b):
    min_factor = max(array_a)
    max_factor = min(array_b)
    counter = 0
    
    for factor in range(min_factor, max_factor+1):
        if not is_array_factor_of_number(factor, array_a):
            continue
        if not is_number_factor_of_array(factor, array_b):
            continue
        counter += 1
    return counter