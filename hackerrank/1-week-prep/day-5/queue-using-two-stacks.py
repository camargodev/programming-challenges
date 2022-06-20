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
        value = self._values.pop()
        return value
        
class Queue:
    def __init__(self):
        self._main_stack = Stack()
        self._helper_stack = Stack()
    
    def enqueue(self, new_value):
        if self._main_stack.is_empty() and self._helper_stack.is_empty():
            self._main_stack.push(new_value)
        else:
            self._helper_stack.push(new_value)
    
    def dequeue(self):
        self._move_to_main_stack()
        self._main_stack.pop()
    
    def print_front(self):
        self._move_to_main_stack()
        print(self._main_stack.top())
        
    def _move_to_main_stack(self):
        if not self._main_stack.is_empty():
            return
        while not self._helper_stack.is_empty():
            self._main_stack.push(self._helper_stack.pop())
        print(self._stack_1.top())

queue = Queue()
for _ in range(int(input())):
    action = input()
    if action == '2':
        queue.dequeue()
    elif action == '3':
        queue.print_front()
    else:
        _, new_value = action.split()
        queue.enqueue(new_value)