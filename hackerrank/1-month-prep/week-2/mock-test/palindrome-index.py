def palindrome_index(word):
    begin = 0
    end = len(word) - 1
    while begin < end:
        if word[begin] != word[end]:
            if is_palindrome(word[:begin] + word[begin+1:]):
                return begin
            elif is_palindrome(word[:end] + word[end+1:]):
                return end
            else:
                return -1
        begin += 1
        end -= 1
    return -1

def is_palindrome(word):
    return word == word[::-1]