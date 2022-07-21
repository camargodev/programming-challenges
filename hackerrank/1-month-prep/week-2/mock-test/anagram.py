def count_char(part_1, part_2, idx):
    return 0 if part_1[idx] == part_2[idx] else 1

def anagram(string):
    if len(string) % 2 != 0:
        return -1
 
    half = len(string)//2
    part_1, part_2 = string[:half], string[half:]
    chars = dict()
    for char in part_1:
        if char not in chars:
            chars[char] = 0
        chars[char] += 1
    for char in part_2:
        if char in chars and chars[char] > 0:
            chars[char] -= 1
    diffs = 0
    for char in chars.keys():
        diffs += chars[char]
    return diffs