MAX_VALUE = 9

class element:
    def __init__(self, values):
        self.values = values
        self.max_value = max(values)
        self.is_single = len(values) == 1
        self.matches = len(set(values)) == 1
        self.changed = False
        
    def force_match(self):
        self.values = [self.max_value, self.max_value]
        self.matches = True
        self.changed = True
        
    def maximize(self):
        self.values = [MAX_VALUE, MAX_VALUE] if not self.is_single else [MAX_VALUE]
        self.max_value = MAX_VALUE
        self.matches = True
        self.changed = True
        
class palindrome:
    def __init__(self, string, size):
        self.elements = self.__build_from_string(string, size)
        
    def __build_from_string(self, string, size):
        elements = []
        for i in range(size//2):
            start = int(string[i])
            end = int(string[size-i-1])
            elements.append(element([start, end]))
        if size % 2 != 0:
            elements.append(element([int(string[size//2])]))
        return elements
    
    def count_diffs(self):
        matches_arr = [element.matches for element in self.elements]
        return sum([1 if not matches else 0 for matches in matches_arr])
    
    def __transform_in_palindrome(self, k):
        for element in self.elements:
            if element.is_single:
                continue
            if not element.matches:
                element.force_match()
                k -= 1
        return k
    
    def maximize(self, k):
        k = self.__transform_in_palindrome(k)
        index = 0
        while index < len(self.elements) and k > 0:
            if self.elements[index].max_value == MAX_VALUE:
                index += 1
                continue
            needed_moves = 1 if (self.elements[index].changed or self.elements[index].is_single) else 2
            if k >= needed_moves:
                self.elements[index].maximize()
                k -= needed_moves
            index += 1
        return self
    
    def to_string(self):
        start = ""
        end = ""
        for element in self.elements:
            value = str(element.max_value)
            start += value
            if not element.is_single:
                end = value + end
        return start + end

def highest_value_palindrome(string, size, k):
    elements = palindrome(string, size)
    if elements.count_diffs() > k:
        return "-1"
    return elements.maximize(k).to_string()
