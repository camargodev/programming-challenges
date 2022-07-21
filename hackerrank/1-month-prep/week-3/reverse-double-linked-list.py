class DoublyLinkedListNode:
    def __init__(self, node_data):
        self.data = node_data
        self.next = None
        self.prev = None

class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def insert_node(self, node_data):
        node = DoublyLinkedListNode(node_data)

        if not self.head:
            self.head = node
        else:
            self.tail.next = node
            node.prev = self.tail


        self.tail = node

def print_doubly_linked_list(node, sep, fptr):
    while node:
        fptr.write(str(node.data))

        node = node.next

        if node:
            fptr.write(sep)

def reverse(original_head):
    if original_head is None:
        return original_head
    
    original_last = original_head
    while original_last.next is not None:
        original_last = original_last.next
    
    new_list = DoublyLinkedList()
    while original_last is not None:
        new_list.insert_node(original_last.data)
        original_last = original_last.prev
    
    return new_list.head