class Stack:    
    def __init__(self):
        self._values = []
        self._size = 0
        
    def is_empty(self):
        return self._size == 0
        
    def push(self, value):
        self._size += 1
        self._values.append(value)
    
    def top(self):
        return self._values[self._size-1]
    
    def pop(self):
        self._size -= 1
        self._values.pop()
 
def is_opening(char):
    return char in ['[', '{', '(']

def are_matching_brackets(opening, closing):
    return (opening, closing) in [('{','}'), ('(',')'), ('[',']')]

def is_balanced(text):
    stack = Stack()
    for char in text:
        if is_opening(char):
            stack.push(char)
            continue
        if stack.is_empty():
            return False
        opening = stack.top()
        if not are_matching_brackets(opening, char):
            return False
        stack.pop()
    return stack.is_empty()