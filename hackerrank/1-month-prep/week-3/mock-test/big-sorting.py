from functools import cmp_to_key

def compare(item1, item2):
    if len(item1) != len(item2):
        return len(item1) - len(item2)
    return int(item1) - int(item2)

def big_sorting(unsorted):
    unsorted.sort(key=cmp_to_key(compare))
    return unsorted