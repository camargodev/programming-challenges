#!/bin/python3
def is_valid(string):
    str_dict = dict()
    for char in string:
        if char not in str_dict:
            str_dict[char] = 0
        str_dict[char] += 1
    counts = dict()
    
    for str_count in str_dict.keys():
        count = str_dict[str_count]
        print(str_count, count)
        if count not in counts:
            counts[count] = 0
        counts[count] += 1
    
    if len(counts.keys()) == 1:
        return 'YES'
    if len(counts.keys()) > 2:
        return 'NO'
    
    counts_arr = []
    for count in counts.keys():
        print(count, counts[count])
        if counts[count] == 1:
            counts_arr.append(count)
    
    if len(counts_arr) != 1:
        return 'NO'
        
    if counts_arr[0] == 1:
        return 'YES'
    
    len_after_remove = counts_arr[0]-1
    if (len_after_remove) not in counts:
        counts[len_after_remove] = 0
    counts[len_after_remove] += 1
    del counts[counts_arr[0]]
    
    if len(counts.keys()) == 1:
        return 'YES' 
    return 'NO'