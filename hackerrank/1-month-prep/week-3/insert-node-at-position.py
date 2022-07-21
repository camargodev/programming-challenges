class SinglyLinkedListNode:
    def __init__(self, node_data):
        self.data = node_data
        self.next = None

class SinglyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def insert_node(self, node_data):
        node = SinglyLinkedListNode(node_data)

        if not self.head:
            self.head = node
        else:
            self.tail.next = node


        self.tail = node

def print_singly_linked_list(node, sep, fptr):
    while node:
        fptr.write(str(node.data))

        node = node.next

        if node:
            fptr.write(sep)


def insert_node_at_position(head, data, position):
    index = 0
    new_list = SinglyLinkedList()
    while head is not None:
        if index == position:
            new_list.insert_node(data)
        new_list.insert_node(head.data)  
        head = head.next
        index += 1
    return new_list.head