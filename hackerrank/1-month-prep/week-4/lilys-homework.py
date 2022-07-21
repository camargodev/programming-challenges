def lilys_with_sorted_array(saved_values, sorted_values):
    values = saved_values.copy()
    indexes = {val:idx for idx,val in enumerate(values)}
    exp_index = 0
    swaps = 0
    # print(values, sorted_values)
    if values == sorted_values:
        return 0
    while exp_index < len(values):
        act_index = indexes[sorted_values[exp_index]]
        if act_index == exp_index:
            exp_index += 1
            continue
        exp_value, act_value = values[exp_index], values[act_index]
        # print("Swap", act_value, exp_value)
        swaps += 1
        values[act_index], values[exp_index] = exp_value, act_value
        indexes[exp_value] = act_index
        indexes[act_value] = exp_index
        exp_index += 1
    return swaps
    

def lilys_homework(values):
    asc_values = sorted(values)
    desc_values = sorted(values, reverse=True)
    lily_asc_array = lilys_with_sorted_array(values, asc_values)
    lily_desc_array = lilys_with_sorted_array(values, desc_values)
    return min(lily_asc_array, lily_desc_array)