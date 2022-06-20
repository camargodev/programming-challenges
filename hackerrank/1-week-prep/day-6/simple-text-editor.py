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
        return self._values[-1]
    
    def pop(self):
        self._size -= 1
        self._values.pop()

class TextEditor:
    def __init__(self):
        self._content = ''
        self._content_stack = Stack()
        self._content_stack.push(self._content)
    
    def append(self, text):
        self._content += text
        self._content_stack.push(self._content)
    
    def delete_end(self, size):
        self._content = self._content[:-size]
        self._content_stack.push(self._content)
    
    def get_char_at(self, index):
        return self._content[index]
    
    def undo(self):
        self._content_stack.pop()
        self._content = self._content_stack.top()
        

def process_action(payload):
    parts = payload.split()
    if len(parts) == 1:
        parts.append(None)
    return int(parts[0]), parts[1] 
    
editor = TextEditor()
for _ in range(int(input())):
    action, content = process_action(input())
    if action == 1:
        editor.append(content)
    elif action == 2:
        editor.delete_end(int(content))
    elif action == 3:
        print(editor.get_char_at(int(content)-1))
    else:
        editor.undo()