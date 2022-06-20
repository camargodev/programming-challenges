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
        self._stack_1 = Stack()
        self._stack_2 = Stack()
    
    def enqueue(self, new_value):
        if self._stack_1.is_empty() and self._stack_2.is_empty():
            self._stack_1.push(new_value)
        else:
            self._stack_2.push(new_value)
    
    def dequeue(self):
        if self._stack_1.is_empty():
            while not self._stack_2.is_empty():
                self._stack_1.push(self._stack_2.pop())
        self._stack_1.pop()
    
    def print_front(self):
        if self._stack_1.is_empty():
            while not self._stack_2.is_empty():
                self._stack_1.push(self._stack_2.pop())
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