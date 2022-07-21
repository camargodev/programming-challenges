class MinHeap:
    def __init__(self):
        self.heap = [0]
        self.size = 0
        self.ROOT = 1
        self.indexes = dict()
        
    def get_min(self):
        return self.heap[self.ROOT]
 
    def insert(self, k):
        self.heap.append(k)
        self.size += 1
        self.indexes[k] = self.size
        self.sift_up(self.size)
        
    def delete(self, value_to_delete): 
        index = self.indexes[value_to_delete]
        self.heap[index] = self.heap[self.size]
        self.indexes[self.heap[index]] = index
        *self.heap, _ = self.heap
        self.size -= 1
        if self.size <= 1:
            return
        self.sift_down(index)
        
    def sift_up(self, i):
        while i//2 > 0:
            parent = self.get_parent(i)
            if self.heap[i] < self.heap[parent]:
                self.swap(i, parent)
            i = parent
 
    def sift_down(self, i):
        while self.node_exists(self.get_left_child(i)):
            min_child = self.min_child(i)
            if self.heap[i] > self.heap[min_child]:
                self.swap(i, min_child)
            i = min_child
 
    def min_child(self, i):
        left = self.get_left_child(i)
        right = self.get_right_child(i)
        if not self.node_exists(right):
            return left
        if self.heap[left] < self.heap[right]:
            return left
        return right
        
    def node_exists(self, i):
        return i <= self.size
    
    def swap(self, i, j):
        self.heap[i], self.heap[j] = self.heap[j], self.heap[i]
        self.indexes[self.heap[i]] = i
        self.indexes[self.heap[j]] = j
        
    def get_parent(self, i):
        return i//2
            
    def get_left_child(self, i):
        return i*2  
    
    def get_right_child(self, i):
        return self.get_left_child(i)+1
    
INSERT = 1
DELETE = 2
 
def process_operation(heap, operation):
    parts = operation.split()
    if len(parts) == 1:
        print(heap.get_min())
    else: 
        op, val = int(parts[0]), int(parts[1])
        if op == INSERT:
            heap.insert(val)
        else: 
            heap.delete(val)
    return heap

queries = int(input())
heap = MinHeap()
for _ in range(queries):
    heap = process_operation(heap, input())