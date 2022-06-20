from collections import deque

def decode_char(root, input_deque):
    current_node = root
    while current_node.left is not None or current_node.right is not None:
        digit = input_deque.popleft()
        if digit == 0:
            current_node = current_node.left
        else:
            current_node = current_node.right
    return current_node.data
    
def build_input_deque(string):
    input_deque = deque()
    for char in string:
        input_deque.append(int(char))
    return input_deque

def decode_huff(root, string):
    result = ""
    input_deque = build_input_deque(string)
    while input_deque:
        char = decode_char(root, input_deque)
        result += char
    print(result)