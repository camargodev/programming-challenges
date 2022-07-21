alphabet = 'abcdefghijklmnopqrstuvwxyz '
def pangrams(string):
    sorted_chars = sorted(set((string.lower())))
    alphabet_chars = sorted(set(alphabet))
    return "pangram" if sorted_chars == alphabet_chars else "not pangram"